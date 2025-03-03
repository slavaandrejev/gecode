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

pkg.generate(
    name: 'gecodeflatzinc'
  , filebase: 'gecodeflatzinc'
  , description: 'FlatZinc interpreter'
  , version: meson.project_version()
  , libraries: gecodeflatzinc_lib
  , requires: [
        'gecodesearch'
      , 'gecodeint'
      , 'gecodeset'
      , 'gecodefloat'
      , 'gecodeminimodel'
      , 'gecodegist'
      , 'gecodedriver'
      ]
  , subdirs: 'gecode'
  )

install_headers(
    'ast.hh'
  , 'branch.hh'
  , 'complete.hh'
  , 'conexpr.hh'
  , 'lastval.hh'
  , 'option.hh'
  , 'parser.hh'
  , 'plugin.hh'
  , 'registry.hh'
  , 'symboltable.hh'
  , 'varspec.hh'
  , 'branch.hpp'
  , 'parser.tab.hpp'
  , subdir: 'gecode/flatzinc'
  )
