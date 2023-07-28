#!/bin/bash

QPS_WEIGHT=${1:-50}
SLEEP_WINDOW_IN_MS=${2:-10}

source $(dirname $0)/config.sh

MYDB=ndbsmall
TableSize=25000
TableCount=250
EVENTS=0
TIME=60
ThreadCount=50
LUA=oltp_read_only


#${MYSYSBENCH} $LUA --sleep_window_in_ms=${SLEEP_WINDOW_IN_MS} --qps_weight=${QPS_WEIGHT} --threads=$ThreadCount --mysql-db=${MYDB} --tables=${TableCount} --table-size=${TableSize} --events=$EVENTS --time=${TIME} --range_selects=off --db-ps-mode=disable --report-interval=1 run
${MYSYSBENCH} $LUA --threads=$ThreadCount --mysql-db=${MYDB} --tables=${TableCount} --table-size=${TableSize} --events=$EVENTS --time=${TIME} --range_selects=off --db-ps-mode=disable --report-interval=1 run
