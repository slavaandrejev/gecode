gecodeflatzinc_lib = library(
    'gecodeflatzinc'
  , 'branch.cpp'
  , 'flatzinc.cpp'
  , 'lexer.yy.cpp'
  , 'parser.tab.cpp'
  , 'registry.cpp'
  , include_directories: [project_inc]
  , dependencies: [
        gecodesearch_dep
      , gecodeint_dep
      , gecodeset_dep
      , gecodefloat_dep
      , gecodeminimodel_dep
      , gecodegist_dep
      , gecodedriver_dep
      ]
  , install: true
  )

gecodeflatzinc_dep = declare_dependency(
    link_with: gecodeflatzinc_lib
  , include_directories: [project_inc]
  , dependencies: [
        gecodesearch_dep
      , gecodeint_dep
      , gecodeset_dep
      , gecodefloat_dep
      , gecodeminimodel_dep
      , gecodegist_dep
      , gecodedriver_dep
      ]
  )
