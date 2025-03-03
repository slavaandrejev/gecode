gecodefloat_dependencies = [
    boost_dep
  , gecodekernel_dep
  , gecodeint_dep
  ]
if mpfr_dep.found()
    gecodefloat_dependencies += mpfr_dep
endif

gecodefloat_lib = library(
    'gecodefloat'
  , 'arithmetic.cpp'
  , 'array.cpp'
  , 'bool.cpp'
  , 'branch.cpp'
  , 'channel.cpp'
  , 'dom.cpp'
  , 'exception.cpp'
  , 'exec.cpp'
  , 'linear.cpp'
  , 'rel.cpp'
  , 'relax.cpp'
  , 'rounding.cpp'
  , 'trace.cpp'
  , 'transcendental.cpp'
  , 'trigonometric.cpp'
  , 'var-imp' / 'float.cpp'
  , 'branch' / 'action.cpp'
  , 'branch' / 'chb.cpp'
  , 'branch' / 'val-sel-commit.cpp'
  , 'branch' / 'view-sel.cpp'
  , 'linear' / 'post.cpp'
  , 'trace' / 'tracer.cpp'
  , 'var' / 'float.cpp'
  , include_directories: [project_inc]
  , dependencies: gecodefloat_dependencies
  , install: true
  )

gecodefloat_dep = declare_dependency(
    link_with: gecodefloat_lib
  , include_directories: [project_inc]
  , dependencies: gecodefloat_dependencies
  )
