project('stream9_rapidjson_test', 'cpp',
  default_options: ['cpp_std=c++17', 'warning_level=3'], license: 'GPL3' )

add_project_arguments(['-Wconversion', '-Wsign-conversion'], language: 'cpp')

project_deps = [
  dependency('boost', modules: ['unit_test_framework']),
  dependency('stream9_rapidjson'),
]

project_inc = []

subdir('src')

test_exe = executable(
  meson.project_name(),
  test_src,
  include_directories: project_inc,
  dependencies: project_deps,
)

run_target('run',
  command: [test_exe, '--color_output=no'],
)
