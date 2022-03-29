#!/bin/bash

export TEST_USER=ssl
export TEST_PASS=rivos
export PRIMARY_IP=127.0.0.1
export PRIMARY_PORT=3306
export MYSYSBENCH="sysbench --mysql-host=${PRIMARY_IP} --mysql-port=${PRIMARY_PORT} --mysql-password=${TEST_PASS} --mysql-user=${TEST_USER} --db-driver=mysql "

function run_query {
  query=$1
  db=${2:-""}
  mysql -u ${TEST_USER} -h ${PRIMARY_IP} -P ${PRIMARY_PORT} -p${TEST_PASS} $db -e "$query"
}

function wait_for_ready {
query=${1:-"show variables like '%read_only%';"}
time=${2:-1}
for i in {1..1000}
do
	run_query "$query"
	if [ $? == 0 ]; then
		break;
	fi
	sleep $time
done
}
