project(json CXX)

cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

set(THIRD_PARTY_DIR "${PROJECT_SOURCE_DIR}/thirdparty")

add_subdirectory(src)

if ((CMAKE_BUILD_TYPE STREQUAL "Debug") OR BUILD_TEST)
    add_subdirectory(test)
endif()
