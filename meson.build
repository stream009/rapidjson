project('stream9_json', 'cpp',
  default_options: ['cpp_std=c++17', 'warning_level=3'] )

add_project_arguments(['-Wconversion', '-Wsign-conversion'], language: 'cpp')

public_inc = include_directories('include')
private_inc = []

private_deps = []

project_libs = []

subdir('src')

project_dep = declare_dependency(
  include_directories: public_inc,
  link_with: project_libs,
)

meson.override_dependency(meson.project_name(), project_dep)
