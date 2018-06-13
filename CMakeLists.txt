project(json CXX)

cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
endif()

set(THIRD_PARTY_DIR "${PROJECT_SOURCE_DIR}/thirdparty")

add_subdirectory(src)

if ((CMAKE_BUILD_TYPE STREQUAL "Debug") OR BUILD_TEST)
    add_subdirectory(test)
endif()
