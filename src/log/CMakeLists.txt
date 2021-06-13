cmake_minimum_required(VERSION 3.0)

project(log)

set(LOG_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include CACHE INTERNAL LogInclude)
include_directories(${LOG_INCLUDE_DIRS})

set(LIB_LOG ${PROJECT_NAME} CACHE INTERNAL LogLibaray)

aux_source_directory(. LOG_SRC_LIST)

add_library(${PROJECT_NAME} ${LOG_SRC_LIST})

target_link_libraries(${PROJECT_NAME} pthread)