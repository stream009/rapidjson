find_package(Boost 1.66 REQUIRED COMPONENTS
    unit_test_framework
)

add_compile_options(-Wall -Wextra -pedantic -Wconversion -Wsign-conversion)

add_definitions(-DBOOST_TEST_DYN_LINK)

add_executable(test_json
    main.cpp
    json.cpp
    value.cpp
    array.cpp
    object.cpp
    error.cpp
    pointer.cpp
)
target_link_libraries(test_json
    ${Boost_LIBRARIES}
    json
)
