################################################################################
##
## Copyright (c) 2018-2020 Aiden Inc. All rights reserved.
## email: 18896628215@163.com
## Created by Aiden Chen on 7/17/2020
##
################################################################################

################################################
#       build thread pool test case begin
################################################
set(thread_pool_name thread_pool_test)
set(thread_pool_src_dir
        ./thread_pool_test.cpp)

add_executable( ${thread_pool_name} ${thread_pool_src_dir})
target_link_libraries( ${thread_pool_name} ${tool_lib} pthread)
install(TARGETS ${thread_pool_name} RUNTIME DESTINATION .)
################################################
#       build thread pool test case begin
################################################


################################################
#       build thread pool test case begin
################################################
set(timer_queue_name timer_queue_test)
set(timer_queue_src_dir
        ./timer_queue_test.cpp)

add_executable( ${timer_queue_name} ${timer_queue_src_dir})
target_link_libraries( ${timer_queue_name} ${tool_lib} pthread)
install(TARGETS ${timer_queue_name} RUNTIME DESTINATION .)
################################################
#       build thread pool test case begin
################################################



install(PROGRAMS   cfg/run.sh  DESTINATION .)