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
