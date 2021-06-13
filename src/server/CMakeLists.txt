cmake_minimum_required(VERSION 3.0)

project(ur3_server)

set(SERVER_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include CACHE INTERNAL ServerInclude)
include_directories(${SERVER_INCLUDE_DIRS} ${LOG_INCLUDE_DIRS})

set(LIB_SERVER ${PROJECT_NAME} CACHE INTERNAL ServerLibaray)

aux_source_directory(. SERVER_SRC_LIST)

add_library(${PROJECT_NAME} ${SERVER_SRC_LIST})

target_link_libraries(${PROJECT_NAME} ${LIB_LOG})