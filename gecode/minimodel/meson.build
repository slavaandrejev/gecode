gecodeminimodel_lib = library(
    'gecodeminimodel'
  , 'bool-expr.cpp'
  , 'dom.cpp'
  , 'exception.cpp'
  , 'float-arith.cpp'
  , 'float-expr.cpp'
  , 'float-rel.cpp'
  , 'int-arith.cpp'
  , 'int-expr.cpp'
  , 'int-rel.cpp'
  , 'ipl.cpp'
  , 'optimize.cpp'
  , 'reg.cpp'
  , 'set-expr.cpp'
  , 'set-rel.cpp'
  , include_directories: [project_inc]
  , dependencies: [
        gecodeint_dep
      , gecodefloat_dep
      , gecodeset_dep
      ]
  , install: true
  )

gecodeminimodel_dep = declare_dependency(
    link_with: gecodeminimodel_lib
  , include_directories: [project_inc]
  , dependencies: [
        gecodeint_dep
      , gecodefloat_dep
      , gecodeset_dep
      ]
  )

pkg.generate(
    name: 'gecodeminimodel'
  , filebase: 'gecodeminimodel'
  , description: 'Gecode modeling support library for the enabled variable types'
  , version: meson.project_version()
  , libraries: gecodeminimodel_lib
  , requires: [
        'gecodeint'
      , 'gecodefloat'
      , 'gecodeset'
      ]
  , subdirs: 'gecode'
  )

install_headers(
    'aliases.hpp'
  , 'bool-expr.hpp'
  , 'channel.hpp'
  , 'exception.hpp'
  , 'float-expr.hpp'
  , 'float-rel.hpp'
  , 'int-expr.hpp'
  , 'int-rel.hpp'
  , 'ipl.hpp'
  , 'ldsb.hpp'
  , 'matrix.hpp'
  , 'optimize.hpp'
  , 'reg.hpp'
  , 'set-expr.hpp'
  , 'set-rel.hpp'
  , subdir: 'gecode/minimodel'
  )
