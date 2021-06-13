cmake_minimum_required(VERSION 3.0)
project(UR3TcpServer VERSION 1.0.0)

set(SRCDIR ${PROJECT_SOURCE_DIR}/src)
set(DISTDIR ${PROJECT_SOURCE_DIR}/dist)
set(CONFIGDIR ${PROJECT_SOURCE_DIR}/configs)

set(EXECUTABLE_OUTPUT_PATH ${DISTDIR})

set(INCLUDE_DIRS ${INCLUDE_DIRS} ${SRCDIR}/include)

add_subdirectory(${SRCDIR}/log)
set(EXTRA_LIBS ${EXTRA_LIBS} ${LIB_LOG})
set(INCLUDE_DIRS ${INCLUDE_DIRS} ${LOG_INCLUDE_DIRS})

add_subdirectory(${SRCDIR}/server)
set(EXTRA_LIBS ${EXTRA_LIBS} ${LIB_SERVER})
set(INCLUDE_DIRS ${INCLUDE_DIRS} ${SERVER_INCLUDE_DIRS})

add_subdirectory(${SRCDIR}/config)
set(EXTRA_LIBS ${EXTRA_LIBS} ${LIB_CONFIG})
set(INCLUDE_DIRS ${INCLUDE_DIRS} ${CONFIG_INCLUDE_DIRS})

IF(WIN32)
#do something related to WIN32
set(EXTRA_LIBS ${EXTRA_LIBS} ws2_32)
ELSEIF(UNIX)
#do something related to UNIX
ELSEIF(APPLE)
#do something related to APPLE
ENDIF(WIN32)

file(COPY ${CONFIGDIR}/config.json DESTINATION ${EXECUTABLE_OUTPUT_PATH})

include_directories(${INCLUDE_DIRS})
aux_source_directory(${SRCDIR} SRCS)
add_executable(${PROJECT_NAME} ${SRCS})

target_link_libraries(${PROJECT_NAME} ${EXTRA_LIBS})
