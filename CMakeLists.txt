################################################################################
##
## Copyright (c) 2018-2020 Aiden Inc. All rights reserved.
## email: 16621182636@163.com
## Created by Aiden Chen on 7/17/2020
##
################################################################################

#if(NOT DEFINED CMAKE_INSTALL_PREFIX)
#    set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/../release" CACHE PATH "Installation Directory")
#endif()

if (("Debug" STREQUAL ${CMAKE_BUILD_TYPE}) AND (NOT DEFINE ${CMAKE_INSTALL_PREFIX}))
    set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/../debug" CACHE PATH "Installation Directory")
elseif(("Release" STREQUAL ${CMAKE_BUILD_TYPE}) AND (NOT DEFINE ${CMAKE_INSTALL_PREFIX}))
    set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/../release" CACHE PATH "Installation Directory")
endif()

message(STATUS "CMAKE_INSTALL_PREFIX = ${CMAKE_INSTALL_PREFIX}")


# depends of this project
cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 14)

# set project name
set(proj_name tool)

project(${proj_name})
set(tool_lib ${proj_name})

################################################
#         Define option begin
################################################

# Enable log for default
option(OPT_LOG_ENABLE "option for log debug" OFF)
if (OPT_LOG_ENABLE)
    add_definitions(-DOPT_LOG_ENABLE)
endif()

# Enable log for default
option(OPT_SAMPLE_ENABLE "option for unit test" ON)
if (OPT_SAMPLE_ENABLE)
    add_definitions(-DOPT_SAMPLE_ENABLE)
endif()

option(OPT_DESIGN_PATERNS_ENABLE "option for design patterns" ON)
if (OPT_DESIGN_PATERNS_ENABLE)
    add_definitions(-DOPT_DESIGN_PATERNS_ENABLE)
endif()
################################################
#         Define option end
################################################

################################################
#         build library tool begin
################################################
# set src directories to build library tool
set(tool_src_dir
        utils/src
        utils/src/threadpool
        utils/src/op_file)

# set include directories to build library tool
set(tool_inc_dir
        utils/include
        utils/include/threadpool
        utils/include/op_file)

# build FPGA Simulator
include_directories(${tool_inc_dir})

foreach(build_src  ${tool_src_dir})
    aux_source_directory(${build_src} tool_build_list)
endforeach()


add_library(${tool_lib} SHARED ${tool_build_list})

if(OPT_DESIGN_PATERNS_ENABLE)
    add_subdirectory(design_patterns)
endif()

add_subdirectory(test)

################################################
#       build library tool end
################################################


################################################
#       build inference test case begin
################################################
install(TARGETS ${tool_lib} LIBRARY DESTINATION ./lib)
################################################
#       build inference test case begin
################################################

