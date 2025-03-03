project(
    'gecode'
  , ['cpp']
  , version : '6.3.0'
  , meson_version: '>= 1.2.0'
  , default_options: {
        'cpp_std': 'gnu++23'
      }
  )

cpp = meson.get_compiler('cpp')

project_inc = include_directories('.')

project_dir = meson.project_source_root()
project_name = meson.project_name()

if get_option('buildtype') == ('debug')
    add_project_arguments('-DDEBUG', language: ['cpp'])
endif
if get_option('buildtype') == 'release' or get_option('buildtype') == 'debugoptimized'
    add_project_arguments('-DNDEBUG', language: ['cpp'])
endif

perl = find_program('perl')

fs  = import('fs')
pkg = import('pkgconfig')
qt6 = import('qt6')

boost_dep  = dependency('boost')
mpfr_dep   = dependency('mpfr', required: false)
thread_dep = dependency('threads', required: get_option('enable_thread'))
qt6_dep    = dependency('qt6', modules: ['Core', 'Widgets', 'Gui', 'PrintSupport'], required: get_option('enable_gist'))

subdir('gecode')
