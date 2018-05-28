find_package(Boost 1.66 REQUIRED COMPONENTS
    unit_test_framework
)

add_definitions(-DBOOST_TEST_DYN_LINK)

include_directories("${CMAKE_SOURCE_DIR}/include")

add_executable(test_main
    main.cpp
    value.cpp
)
target_link_libraries(test_main
    ${Boost_LIBRARIES}
    json
)
