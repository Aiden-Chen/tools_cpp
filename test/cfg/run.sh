#!/bin/bash

#set environment
export LD_LIBRARY_PATH=./lib:${LD_LIBRARY_PATH}

#function run
run(){
    case $1 in
        0)
            echo "thread_pool_test"
            ./thread_pool_test
        ;;
        1)
            echo "timer_queue_test"
            ./timer_queue_test
        ;;
        2)
            echo "ini_parser_test"
            ./ini_parser_test ./cfg/test_op_file.ini
        ;;
        3)
            echo "design_patterns_test"
            ./design_patterns_test
        ;;
        *)
            echo "Don't support this command"
        ;;
    esac
}


#start
echo "starting..."

if [ $# -lt 1 ];
then
    echo "Missing parameter: ./run.sh 0~3"
    echo "0: thread_pool_test"
    echo "1: timer_queue_test"
    echo "2: ini_parser_test"
    echo "3: design_patterns_test"
    exit
fi

run $1

echo "end..."
