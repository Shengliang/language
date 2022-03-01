#!/bin/bash

source $(dirname $0)/config.sh

MYDB=sbtest
TableSize=1000000
TableCount=25
EVENTS=0
TIME=300
ThreadCount=25
LUA=oltp_read_write


${MYSYSBENCH} $LUA --threads=$ThreadCount --mysql-db=${MYDB} --tables=${TableCount} --table-size=${TableSize} --events=$EVENTS --time=${TIME} --db-ps-mode=disable --report-interval=1 run
