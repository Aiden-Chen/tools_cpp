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
#       build thread pool test case end
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
#       build thread pool test case end
################################################


################################################
#       build ini parser test begin
################################################
set(ini_parser_name ini_parser_test)
set(ini_parser_src_dir
        ./ini_parser_test.cpp)

message(${tool_lib})
add_executable( ${ini_parser_name} ${ini_parser_src_dir})
target_link_libraries( ${ini_parser_name} ${tool_lib} pthread)
install(TARGETS ${ini_parser_name} RUNTIME DESTINATION .)
################################################
#       build ini parser test end
################################################



################################################
#       build design patterns test begin
################################################
set(design_patterns_test_name design_patterns_test)
set(design_patterns_test_src_dir
        ./design_pattern_test.cpp)
#message("***********************************")
message(${DESIGN_PATTERN_LIBRARY})
add_executable( ${design_patterns_test_name} ${design_patterns_test_src_dir})
target_link_libraries( ${design_patterns_test_name} ${DESIGN_PATTERN_LIBRARY} pthread)
install(TARGETS ${design_patterns_test_name} RUNTIME DESTINATION .)
################################################
#       build design patterns test end
################################################


install(PROGRAMS   cfg/run.sh  DESTINATION .)
install(PROGRAMS   cfg/test_op_file.ini  DESTINATION ./cfg)