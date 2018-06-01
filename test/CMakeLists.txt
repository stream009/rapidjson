find_package(Boost 1.66 REQUIRED COMPONENTS
    unit_test_framework
)

add_definitions(-DBOOST_TEST_DYN_LINK)

include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(main
    main.cpp
    value.cpp
    array.cpp
    object.cpp
)
target_link_libraries(main
    ${Boost_LIBRARIES}
    json
)
