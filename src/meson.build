json_src = [
  'internal/allocator.cpp',
  'base.cpp',
  'value.cpp',
  'array.cpp',
  'object.cpp',
  'parse_error.cpp',
  'pointer_error.cpp',
  'pointer.cpp',
]

cmake = import('cmake')

rapidjson_prj = cmake.subproject('rapidjson')
rapidjson_inc = '../subprojects/rapidjson/include'

json_lib = static_library('stream9_json',
  json_src,
  include_directories: [inc, rapidjson_inc],
)

json_dep = declare_dependency(
  include_directories: inc,
  link_with: json_lib
)
