include_directories(
    "${THIRD_PARTY_DIR}/rapidjson/include")

add_library(json STATIC
    internal/allocator.cpp
    base.cpp
    value.cpp
    array.cpp
    object.cpp
    json.cpp
)
