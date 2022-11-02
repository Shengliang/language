#!/bin/bash

QPS_WEIGHT=${1:-50}
SLEEP_WINDOW_IN_MS=${2:-15}

source $(dirname $0)/config.sh

MYDB=sbtest2
TableSize=10000
TableCount=10
EVENTS=0
TIME=60
ThreadCount=10
LUA=oltp_write_only


${MYSYSBENCH} $LUA --sleep_window_in_ms=${SLEEP_WINDOW_IN_MS} --qps_weight=${QPS_WEIGHT} --threads=$ThreadCount --mysql-db=${MYDB} --tables=${TableCount} --table-size=${TableSize} --events=$EVENTS --time=${TIME} --range_selects=off --db-ps-mode=disable --report-interval=1 run
