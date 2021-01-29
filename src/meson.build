project_src = files(
  'internal/allocator.cpp',
  'base.cpp',
  'value.cpp',
  'array.cpp',
  'object.cpp',
  'parse_error.cpp',
  'pointer_error.cpp',
  'pointer.cpp',
)

private_inc = include_directories('../thirdparty/rapidjson/include', is_system: true)

project_libs += static_library('stream9_rapidjson',
  project_src,
  include_directories: [public_inc, private_inc],
)
