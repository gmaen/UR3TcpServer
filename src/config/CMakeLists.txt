cmake_minimum_required(VERSION 3.0)

project(ur3_config)

set(CONFIG_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include CACHE INTERNAL ConfigInclude)

set(LIB_CONFIG ${PROJECT_NAME} CACHE INTERNAL ConfigLibaray)

aux_source_directory(. CONFIG_SRC_LIST)

add_library(${PROJECT_NAME} ${CONFIG_SRC_LIST})
target_include_directories(${PROJECT_NAME} PUBLIC ${CONFIG_INCLUDE_DIRS})