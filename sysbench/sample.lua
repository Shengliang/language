--
--[[
# Reference https://www.percona.com/blog/2019/04/25/creating-custom-sysbench-scripts/
# The test will performance the following tests.
# - connects to a relica group (write or read notes).
# - show variables like 'read_only'
# - run read workload if it is a read_only replica.
# - run write workload if it is a read_write replica.
#
#  --threads=N                     number of threads to use [1]
#  --events=N                      limit for total number of events [0]
#  --time=N                        limit for total execution time in seconds [10]

Prepare 1: create database and add test users.
# mysql -u root -P 3306 --socket=mysql.soc -e "source user.sql"
CREATE USER 'test'@'127.0.0.1' IDENTIFIED BY 'p1234';
CREATE USER 'test'@'::1' IDENTIFIED BY 'p1234';
GRANT ALL ON *.* TO 'test'@'127.0.0.1';
FLUSH PRIVILEGES;

Prepare 2: load sample databases.
mysql -u $USER -h $PRIMARY_IP -P $PRIMARY_PORT -p$PASS  -e "source sampledb/imdb-create-tables.sql; source sampledb/mysqlsampledatabase.sql ;"

LUA=sample.lua
ThreadCount=6
EVENTS=30
TIME=30

USER=test
PASS=p1234
PRIMARY_IP=127.0.0.1
PRIMARY_PORT=3306
DBIS=127.0.0.1,127.0.0.1,127.0.0.1
PORTS=3306,3307,3308
DB=IMDb

mysql -u $USER -h $PRIMARY_IP -P $PRIMARY_PORT -p$PASS  -e "source imdb/imdb-create-tables.sql; source sampledb/mysqlsampledatabase.sql ;"
mysql -u $USER -h $PRIMARY_IP -P $PRIMARY_PORT -p$PASS  $DB -e "show tables;"
mysql -u $USER -h $PRIMARY_IP -P $PRIMARY_PORT -p$PASS  classicmodels -e "show tables;"

sysbench $LUA --threads=$ThreadCount --mysql-host=$DBIS --mysql-password=$PASS --mysql-user=$USER --mysql-db=$DB --db-driver=mysql --mysql-port=$PORTS  --events=$EVENTS --time=10  --report-interval=1 run
]]

thread_state_done = false

if sysbench.cmdline.command == nil then
   error("Command is required. Supported commands: run")
end

sysbench.cmdline.options = {
  point_selects = {"Number of point SELECT queries to run", 5},
  skip_trx = {"Do not use BEGIN/COMMIT; Use global auto_commit value", false}
}

-- Array of COUNT(*) queries
local select_counts = {
  "SELECT COUNT(*) FROM IMDb.Names_"
}

-- Array of SELECT statements that have 1 integer parameter
local select_points = {
  "SELECT * FROM IMDb.Titles WHERE title_id = %d"
}

-- Array of SELECT statements that have 1 string parameter
local select_string = {
  "SELECT * FROM IMDb.Titles WHERE title_id LIKE '%s%%'"
}


-- INSERT statements
local inserts = {
   "INSERT INTO IMDb.Names_ (name_id, name_) VALUES ('%s', '%s')"
}


function execute_selects()

  -- Execute each simple, no parameters, SELECT
  for i, o in ipairs(select_counts) do
    con:query(o)
  end

  -- Loop for however many queries the
  -- user wants to execute in this category
  for i = 1, sysbench.opt.point_selects do

    -- select random query from list
    local randQuery = select_points[math.random(#select_points)]

    -- generate random id and execute
    local id = sysbench.rand.pareto(1, 3000000)
    con:query(string.format(randQuery, id))
  end

  -- generate random string and execute
  for i, o in ipairs(select_string) do
    local str = sysbench.rand.string(string.rep("@", sysbench.rand.special(2, 15)))
    con:query(string.format(o, str))
  end
end


function create_random_email()

  local username = sysbench.rand.string(string.rep("@",sysbench.rand.uniform(5,10)))

  local domain = sysbench.rand.string(string.rep("@",sysbench.rand.uniform(5,10)))

  return username .. "@" .. domain .. ".com"

end



function execute_inserts()
  -- generate fake email/info
  local email = create_random_email()
  local name = sysbench.rand.string(string.rep("@", sysbench.rand.special(2, 15)))
  -- lua array is 1 based (not 0-based in C/C++)
  print("insert:", inserts[1], email, name)
  con:query(string.format(inserts[1], email, name))
end

-- Called by sysbench one time to initialize this script
function thread_init(thread_id)
  -- Create globals to be used elsewhere in the script
  -- drv - initialize the sysbench mysql driver
  drv = sysbench.sql.driver()

  -- con - represents the connection to MySQL
  con = drv:connect()
  print("thread_init:", thread_id)
  thread_state_done = false
end



-- Called by sysbench when script is done executing
function thread_done(thread_id)
  thread_state_done = true
  print("thread_done:", thread_id)
  -- Disconnect/close connection to MySQL
  con:disconnect()
end



-- Called by sysbench for each execution
function event(thread_id)
  if thread_state_done then
      print("skip event thread_id:", thread_id, " thread_done:", thread_state_done)
     return
  end

  print("run event thread_id:", thread_id, " thread_done:", thread_state_done)
  -- If user requested to disable transactions,
  -- do not execute BEGIN statement
  if not sysbench.opt.skip_trx then
    con:query("BEGIN")
  end

  -- Run our custom statements
  local name, val = con:query_row("show variables like 'read_only'")
  print(name, val)
  if val == "ON" then
    execute_selects()
  else
    print(name, val)
    execute_inserts()
  end

  -- Like above, if transactions are disabled,
  -- do not execute COMMIT
  if not sysbench.opt.skip_trx then
    con:query("COMMIT")
  end

end
