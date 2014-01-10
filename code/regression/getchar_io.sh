#!/bin/bash

NACHOS_DIR=../build/

cd $NACHOS_DIR
TEST_STRING="0123456789"

OUTPUT=$(echo $TEST_STRING | ./nachos-step2 -x getchar | grep $TEST_STRING)

if [ -n "$OUTPUT" ]; then
    exit 0
else
    exit -1
fi