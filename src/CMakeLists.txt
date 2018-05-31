include_directories(
    "${CMAKE_SOURCE_DIR}/include"
    "${THIRD_PARTY_DIR}/rapidjson/include"
)

add_library(json STATIC
    internal/allocator.cpp
    base.cpp
    value.cpp
    array.cpp
    object.cpp
    json.cpp
)
