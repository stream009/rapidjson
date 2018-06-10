include_directories(
    "${PROJECT_SOURCE_DIR}/include"
    "${THIRD_PARTY_DIR}/rapidjson/include"
)

add_library(json STATIC
    internal/allocator.cpp
    base.cpp
    value.cpp
    array.cpp
    object.cpp
    json.cpp
    parse_error.cpp
    pointer_error.cpp
)
set_target_properties(json PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib"
)
