cmake_minimum_required(VERSION 3.10)

project(json LANGUAGES CXX VERSION 1.2.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BUILD_TEST      "build test suite" OFF)

if(NOT CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
    set(BUILD_TEST OFF)
endif()

add_subdirectory(include)
add_subdirectory(src)

if (BUILD_TEST)
    add_subdirectory(test)
endif()

set(MODULE_DIR lib/cmake/Json)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/cmake/JsonVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

install(EXPORT JsonTargets NAMESPACE Json:: DESTINATION ${MODULE_DIR})

install(FILES
    cmake/JsonConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/cmake/JsonVersion.cmake
    DESTINATION ${MODULE_DIR}
)
