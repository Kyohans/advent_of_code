project('advent-of-code', 'c',
  version : '0.5',
  default_options : ['warning_level=3'])
project_description = 'Advent of Code in C by Kyohans'

incdir = include_directories('include')
subdir('src')
subdir('src/2023')

args = [
  '-Wno-unused',
]
add_project_arguments(args, language : 'c')

exe = executable(
  'advent_of_code', 
  sources : ['advent_of_code.c', sources],
  include_directories : incdir,
  install : true
)

test('basic', exe)
