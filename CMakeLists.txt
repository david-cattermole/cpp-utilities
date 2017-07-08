cmake_minimum_required(VERSION 2.6)
project(cpp-utilities)
set(CMD_NAME animCurveMatch)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE DEBUG)
# set(CMAKE_BUILD_TYPE RELEASE)

set(DEBUG_UTILS_FILES
        include/debugUtils.h
        tests/src/debugUtils.cpp)

set(FILE_SYSTEM_UTILS_FILES
        include/filesystemUtils.h
        tests/src/filesystemUtils.cpp)

set(HASH_UTILS_FILES
        include/hashUtils.h
        tests/src/hashUtils.cpp)

set(NUMBER_UTILS_FILES
        include/numberUtils.h
        tests/src/numberUtils.cpp)

set(OS_MEMORY_UTILS_FILES
        include/osMemoryUtils.h
        tests/src/osMemoryUtils.cpp)

set(STRING_UTILS_FILES
        include/stringUtils.h
        tests/src/stringUtils.cpp)

include_directories(
        include
)

add_executable(debugUtils ${DEBUG_UTILS_FILES})
add_executable(filesystemUtils ${FILE_SYSTEM_UTILS_FILES})
add_executable(hashUtils ${HASH_UTILS_FILES})
add_executable(numberUtils ${NUMBER_UTILS_FILES})
add_executable(osMemoryUtils ${OS_MEMORY_UTILS_FILES})
add_executable(stringUtils ${STRING_UTILS_FILES})
