gecodesearch_lib = library(
    'gecodesearch'
  , 'bab.cpp'
  , 'cutoff.cpp'
  , 'dfs.cpp'
  , 'engine.cpp'
  , 'exception.cpp'
  , 'lds.cpp'
  , 'nogoods.cpp'
  , 'options.cpp'
  , 'pbs.cpp'
  , 'rbs.cpp'
  , 'stop.cpp'
  , 'tracer.cpp'
  , 'cpprofiler' / 'tracer.cpp'
  , 'par' / 'pbs.cpp'
  , 'seq' / 'rbs.cpp'
  , 'seq' / 'dead.cpp'
  , 'seq' / 'pbs.cpp'
  , include_directories: [project_inc]
  , dependencies: [gecodekernel_dep]
  , install: true
  )

gecodesearch_dep = declare_dependency(
    link_with: gecodesearch_lib
  , include_directories: [project_inc]
  , dependencies: [gecodekernel_dep]
  )

pkg.generate(
    name: 'gecodesearch'
  , filebase: 'gecodesearch'
  , description: 'Gecode search engines'
  , version: meson.project_version()
  , libraries: gecodesearch_lib
  , requires: ['gecodekernel']
  , subdirs: 'gecode'
  )

subdir('cpprofiler')
subdir('par')
subdir('seq')

install_headers(
    'nogoods.hh'
  , 'relax.hh'
  , 'support.hh'
  , 'worker.hh'
  , 'bab.hpp'
  , 'base.hpp'
  , 'build.hpp'
  , 'cutoff.hpp'
  , 'dfs.hpp'
  , 'engine.hpp'
  , 'exception.hpp'
  , 'lds.hpp'
  , 'nogoods.hpp'
  , 'options.hpp'
  , 'pbs.hpp'
  , 'rbs.hpp'
  , 'sebs.hpp'
  , 'statistics.hpp'
  , 'stop.hpp'
  , 'trace-recorder.hpp'
  , 'tracer.hpp'
  , 'traits.hpp'
  , subdir: 'gecode/search'
  )
