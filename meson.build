project('stream9_json', 'cpp',
  default_options: ['cpp_std=c++17', 'warning_level=3'] )

add_project_arguments(['-Wconversion', '-Wsign-conversion'], language: 'cpp')

inc = include_directories('include')

subdir('src')

if get_option('build_test')
  subdir('test')
endif
