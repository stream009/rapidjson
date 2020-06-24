add_compile_options(-Wall -Wextra -pedantic -Wconversion -Wsign-conversion)

include_directories(${PROJECT_SOURCE_DIR}/thirdparty/rapidjson/include)

add_library(json STATIC
    internal/allocator.cpp
    base.cpp
    value.cpp
    array.cpp
    object.cpp
    parse_error.cpp
    pointer_error.cpp
    pointer.cpp
)
target_include_directories(json
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)
set_target_properties(json PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib"
)

install(TARGETS json EXPORT JsonTargets)
