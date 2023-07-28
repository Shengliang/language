#!/bin/bash

source $(dirname $0)/config.sh

MYDB=ndbsmall
TableSize=25000
TableCount=250
EVENTS=30
TIME=30
ThreadCount=25
LUA=oltp_read_write

run_query "drop database if exists $MYDB"
run_query "create database $MYDB"
run_query "show databases"

${MYSYSBENCH} $LUA --threads=$ThreadCount --mysql-db=${MYDB} --tables=${TableCount} --table-size=${TableSize} --events=$EVENTS --time=${TIME} prepare
