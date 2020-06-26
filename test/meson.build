test_src = [
  'main.cpp',
  'value.cpp',
  'array.cpp',
  'object.cpp',
  'error.cpp',
  'pointer.cpp',
]

boost_dep = dependency('boost', modules: ['unit_test_framework'])

test_exe = executable('json_test',
  test_src,
  include_directories: inc,
  cpp_args: '-DBOOST_TEST_DYN_LINK',
  dependencies: [json_dep, boost_dep]
)

run_target('run_test',
  command: test_exe
)
