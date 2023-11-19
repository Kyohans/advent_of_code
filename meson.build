project('advent-of-code', 'c',
  version : '0.1',
  default_options : ['warning_level=3'])

incdir = include_directories('include')

exe = executable('advent_of_code', 'advent_of_code.c',
  include_directories : incdir,
  install : true)

test('basic', exe)
