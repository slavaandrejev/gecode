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

pkg.generate(
    name: 'gecodefloat'
  , filebase: 'gecodefloat'
  , description: 'Gecode float variable library'
  , version: meson.project_version()
  , libraries: gecodefloat_lib
  , requires: [
        'gecodekernel'
      , 'gecodeint'
      ]
  , subdirs: 'gecode'
  )

subdir('arithmetic')
subdir('bool')
subdir('branch')
subdir('channel')
subdir('linear')
subdir('rel')
subdir('trace')
subdir('transcendental')
subdir('trigonometric')
subdir('var')
subdir('var-imp')
subdir('view')

install_headers(
    'arithmetic.hh'
  , 'bool.hh'
  , 'branch.hh'
  , 'channel.hh'
  , 'linear.hh'
  , 'rel.hh'
  , 'transcendental.hh'
  , 'trigonometric.hh'
  , 'array.hpp'
  , 'array-traits.hpp'
  , 'branch.hpp'
  , 'channel.hpp'
  , 'exception.hpp'
  , 'limits.hpp'
  , 'nextafter.hpp'
  , 'num.hpp'
  , 'rounding.hpp'
  , 'trace.hpp'
  , 'val.hpp'
  , 'var-imp.hpp'
  , 'view.hpp'
  , subdir: 'gecode/float'
  )
