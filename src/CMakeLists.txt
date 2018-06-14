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
target_include_directories(json
    PUBLIC
        "${PROJECT_SOURCE_DIR}/include"
    PRIVATE
        "${THIRD_PARTY_DIR}/rapidjson/include"
)
set_target_properties(json PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib"
)
