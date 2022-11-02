#!/bin/bash
QPS_WEIGHT=${1:-50}
SLEEP_WINDOW_IN_MS=${2:-15}

source $(dirname $0)/config.sh

echo QPS_WEIGHT: ${QPS_WEIGHT}
MYDB=sbtest2
TableSize=10000
TableCount=10
EVENTS=0
TIME=60
ThreadCount=10
LUA=oltp_read_write
# LUA=/Users/bytedance/sysbench/src/lua/oltp_read_write.lua
# 50% drop


${MYSYSBENCH} $LUA --sleep_window_in_ms=${SLEEP_WINDOW_IN_MS} --qps_weight=${QPS_WEIGHT}  --threads=$ThreadCount --mysql-db=${MYDB} --tables=${TableCount} --table-size=${TableSize} --events=$EVENTS --time=${TIME} --db-ps-mode=disable --report-interval=1 run
