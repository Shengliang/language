#!/bin/bash

source $(dirname $0)/config.sh

MYDB=sbtest
TableSize=1000000
TableCount=10
EVENTS=0
TIME=300
ThreadCount=10
LUA=oltp_read_only


${MYSYSBENCH} $LUA --threads=$ThreadCount --mysql-db=${MYDB} --tables=${TableCount} --table-size=${TableSize} --events=$EVENTS --time=${TIME} --range_selects=off --db-ps-mode=disable --report-interval=1 run
