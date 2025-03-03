genvarimp = files(project_dir / 'misc' / 'genvarimp.perl')[0]

var_type_hpp = custom_target(
    input: [
        project_dir / 'gecode' / 'int' / 'var-imp' / 'int.vis'
      , project_dir / 'gecode' / 'int' / 'var-imp' / 'bool.vis'
      , project_dir / 'gecode' / 'set' / 'var-imp' / 'set.vis'
      , project_dir / 'gecode' / 'float' / 'var-imp' / 'float.vis'
      ]
  , output: 'var-type.hpp'
  , command: [
        perl
      , genvarimp
      , '-typehpp'
      , '@INPUT@'
      ]
  , capture: true
  , depend_files: [genvarimp]
  , install: true
  , install_dir: get_option('includedir') / 'gecode' / 'kernel'
  )

var_imp_hpp = custom_target(
    input: [
        project_dir / 'gecode' / 'int' / 'var-imp' / 'int.vis'
      , project_dir / 'gecode' / 'int' / 'var-imp' / 'bool.vis'
      , project_dir / 'gecode' / 'set' / 'var-imp' / 'set.vis'
      , project_dir / 'gecode' / 'float' / 'var-imp' / 'float.vis'
      ]
  , output: 'var-imp.hpp'
  , command: [
        perl
      , genvarimp
      , '-header'
      , '@INPUT@'
      ]
  , capture: true
  , depend_files: [genvarimp]
  , install: true
  , install_dir: get_option('includedir') / 'gecode' / 'kernel'
  )

gecodekernel_lib = library(
    'gecodekernel'
  , 'archive.cpp'
  , 'core.cpp'
  , 'exception.cpp'
  , 'gpi.cpp'
  , 'branch' / 'action.cpp'
  , 'branch' / 'afc.cpp'
  , 'branch' / 'chb.cpp'
  , 'branch' / 'function.cpp'
  , 'data' / 'array.cpp'
  , 'data' / 'rnd.cpp'
  , 'memory' / 'manager.cpp'
  , 'memory' / 'region.cpp'
  , 'trace' / 'filter.cpp'
  , 'trace' / 'general.cpp'
  , 'trace' / 'recorder.cpp'
  , 'trace' / 'tracer.cpp'
  , var_type_hpp
  , var_imp_hpp
  , include_directories: [project_inc]
  , dependencies: [gecodesupport_dep]
  , install: true
  )

gecodekernel_dep = declare_dependency(
    link_with: gecodekernel_lib
  , include_directories: [project_inc]
  , dependencies: [gecodesupport_dep]
  )

pkg.generate(
    name: 'gecodekernel'
  , filebase: 'gecodekernel'
  , description: 'Gecode kernel'
  , version: meson.project_version()
  , libraries: gecodekernel_lib
  , requires: ['gecodesupport']
  , subdirs: 'gecode'
  )

subdir('branch')
subdir('data')
subdir('memory')
subdir('propagator')
subdir('trace')

install_headers(
    'archive.hpp'
  , 'core.hpp'
  , 'exception.hpp'
  , 'gpi.hpp'
  , 'macros.hpp'
  , 'modevent.hpp'
  , 'range-list.hpp'
  , 'shared-object.hpp'
  , 'shared-space-data.hpp'
  , 'var.hpp'
  , 'var-imp.hpp'
  , 'var-type.hpp'
  , 'view.hpp'
  , subdir: 'gecode/kernel'
  )
