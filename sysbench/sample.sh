# Reference https://www.percona.com/blog/2019/04/25/creating-custom-sysbench-scripts/

# Prepare Step:
# mysql -u root -P 3306 --socket=mysql.soc -e "source user.sql"

# CREATE USER 'test'@'127.0.0.1' IDENTIFIED BY 'p1234';
# CREATE USER 'test'@'::1' IDENTIFIED BY 'p1234';
# GRANT ALL ON *.* TO 'test'@'127.0.0.1';
# FLUSH PRIVILEGES;

# The test will performance the following tests.
# - connects to a relica group (write or read notes).
# - show variables like 'read_only'
# - run read workload if it is a read_only replica.
# - run write workload if it is a read_write replica.
#
#  --threads=N                     number of threads to use [1]
#  --events=N                      limit for total number of events [0]
#  --time=N                        limit for total execution time in seconds [10]

LUA=sample.lua
ThreadCount=6
EVENTS=30
TIME=30

USER=ssl
PASS=rivos
PRIMARY_IP=127.0.0.1
PRIMARY_PORT=3306
DBIS=127.0.0.1,127.0.0.1,127.0.0.1
PORTS=3306,3306,3306
DB=IMDb

mysql -u $USER -h $PRIMARY_IP -P $PRIMARY_PORT -p$PASS  -e "source sampledb/imdb-create-tables.sql; source sampledb/mysqlsampledatabase.sql ;"
mysql -u $USER -h $PRIMARY_IP -P $PRIMARY_PORT -p$PASS  $DB -e "show tables;"
mysql -u $USER -h $PRIMARY_IP -P $PRIMARY_PORT -p$PASS  classicmodels -e "show tables;"

sysbench $LUA --threads=$ThreadCount --mysql-host=$DBIS --mysql-password=$PASS --mysql-user=$USER --mysql-db=$DB --db-driver=mysql --mysql-port=$PORTS  --events=$EVENTS --time=10  --report-interval=1 run
