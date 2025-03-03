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
