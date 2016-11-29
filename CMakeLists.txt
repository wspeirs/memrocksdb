cmake_minimum_required(VERSION 2.8)
project(memrocksdb)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_VERBOSE_MAKEFILE ON)
endif()

#################################################### Path Settings #####################################################
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib-static)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#################################################### Dependencies ######################################################
#find_package(Threads  REQUIRED)

################################################## Compiler Settings ###################################################
set(GENERAL_WARNING_FLAGS          "-Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-variadic-macros")
set(GENERAL_DEBUG_FLAGS            "-g")
set(GENERAL_RELEASE_FLAGS          "-mtune=native -DNDEBUG -O3 -fomit-frame-pointer")
set(GENERAL_COMPILER_FLAGS         "-pipe")

set(CMAKE_CXX_FLAGS                "-std=c++11 ${GENERAL_WARNING_FLAGS} ${GENERAL_COMPILER_FLAGS} -Wshadow -Weffc++ -fnon-call-exceptions")
set(CMAKE_CXX_FLAGS_DEBUG          "${GENERAL_DEBUG_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE        "${GENERAL_RELEASE_FLAGS}")
set(CMAKE_C_FLAGS                  "-std=c11 ${GENERAL_WARNING_FLAGS} ${GENERAL_COMPILER_FLAGS}")
set(CMAKE_C_FLAGS_DEBUG            "${GENERAL_DEBUG_FLAGS}")
set(CMAKE_C_FLAGS_RELEASE          "${GENERAL_RELEASE_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS         "")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG   "")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "-s")

################################################## Executable Settings/Build ###########################################
set(MEMROCKSDB_SOURCE_DIR  "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(MEMROCKSDB_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

file(GLOB_RECURSE MEMROCKSDB_FILES_CXX "${MEMROCKSDB_SOURCE_DIR}/*.cpp")

add_executable(memrocksdb ${MEMROCKSDB_FILES_CXX})
target_include_directories(memrocksdb PUBLIC "${MEMROCKSDB_INCLUDE_DIR}")

######################################################## Output Folders ################################################
set_target_properties(
        memrocksdb
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
)


