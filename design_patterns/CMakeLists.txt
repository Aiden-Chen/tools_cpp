################################################################################
##
## Copyright (c) 2018-2020 Aiden Inc. All rights reserved.
## email: 18896628215@163.com
## Created by Aiden Chen on 7/17/2020
##
################################################################################

################################################
#       build  design pattern library begin
################################################
set(design_pattern_name design_pattern)
set(design_pattern_src_dir
        factory_pattern/
        singleton_pattern/
        builder_pattern/
        prototype_pattern/)

include_directories(${design_pattern_src_dir})

foreach(build_src  ${design_pattern_src_dir})
    aux_source_directory(${build_src} design_pattern_list)
endforeach()

add_library(${design_pattern_name} SHARED ${design_pattern_list})
install(TARGETS ${design_pattern_name} LIBRARY DESTINATION ./lib)

# 将动态库变量存放放到CMakeCache.txt中，实现变量共享
set(DESIGN_PATTERN_LIBRARY "${design_pattern_name}" CACHE INTERNAL "design pattern Library location" )
# 变量共享
#set_property(GLOBAL PROPERTY DESIGN_PATTERN_LIBRARY "$design_pattern_name" )
#get_property(DESIGN_PATTERN_LIBRARY GLOBAL PROPERTY "DESIGN_PATTERN_LIBRARY" )
#MESSAGE(STATUS "DESIGN_PATTERN_LIBRARY :${DESIGN_PATTERN_LIBRARY}")
################################################
#       build  design pattern library end
################################################