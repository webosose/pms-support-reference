# @@@LICENSE
#
#   Copyright (c) 2017-2020 LG Electronics Inc. All Rights Reserved
#
# LICENSE@@@

cmake_minimum_required(VERSION 2.8.7)
project(pms-support)


include(webOS/webOS)
webos_modules_init(1 0 0 QUALIFIER RC7)
webos_component(1 0 0)

include(FindPkgConfig)

pkg_check_modules(LS2 REQUIRED luna-service2)
include_directories(${LS2_INCLUDE_DIRS})
webos_add_compiler_flags(ALL ${LS2_CFLAGS_OTHER})

pkg_check_modules(GLIB2 REQUIRED glib-2.0)
include_directories(${GLIB2_INCLUDE_DIRS})
webos_add_compiler_flags(ALL ${GLIB2_CFLAGS_OTHER})

pkg_check_modules(PMLOGLIB REQUIRED PmLogLib)
include_directories(${PMLOGLIB_INCLUDE_DIRS})
webos_add_compiler_flags(ALL ${PMLOGLIB_CFLAGS_OTHER})

pkg_check_modules(NYXLIB REQUIRED nyx)
include_directories(${NYXLIB_INCLUDE_DIRS})
webos_add_compiler_flags(ALL ${NYXLIB_CFLAGS_OTHER})

pkg_check_modules(PBNJSON_CPP REQUIRED pbnjson_cpp)
include_directories(${PBNJSON_CPP_INCLUDE_DIRS})
webos_add_compiler_flags(ALL ${PBNJSON_CPP_CFLAGS_OTHER})

include_directories(include/private)
include_directories(include/public)
include_directories(include/private/states)

add_definitions(-DPMS_CONF_FILE_PATH="/var/PMS/pms.conf")
add_definitions(-DFSM_FILE_PATH="/var/PMS/pms.fsm")
file(GLOB SOURCE_FILES
                 src/*.cpp
                 src/*/*.cpp)

webos_build_configured_file(src/states/pms.fsm LOCALSTATEDIR PMS)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

add_library(${CMAKE_PROJECT_NAME} SHARED
                          ${SOURCE_FILES}
                          )

set(LIBS ${LS2_LDFLAGS}
         ${GLIB2_LDFLAGS}
         ${PMLOGLIB_LDFLAGS}
         ${PBNJSON_CPP_LDFLAGS}
         ${NYXLIB_LDFLAGS}
         luna-service2++
         pthread
         fsmsupport
         pmscore)

target_link_libraries(${CMAKE_PROJECT_NAME} ${LIBS})
webos_build_library(NAME ${CMAKE_PROJECT_NAME} HEADERS "include/private")
