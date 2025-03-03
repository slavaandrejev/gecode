gecodedriver_lib = library(
    'gecodedriver'
  , 'options.cpp'
  , 'script.cpp'
  , include_directories: [project_inc]
  , dependencies: [
        gecodegist_dep
      , gecodeminimodel_dep
      , gecodeset_dep
      , gecodesearch_dep
      ]
  , install: true
  )

gecodedriver_dep = declare_dependency(
    link_with: gecodedriver_lib
  , include_directories: [project_inc]
  , dependencies: [
        gecodegist_dep
      , gecodeminimodel_dep
      , gecodeset_dep
      , gecodesearch_dep
      ]
  )

pkg.generate(
    name: 'gecodedriver'
  , filebase: 'gecodedriver'
  , description: 'Gecode script commandline driver library'
  , version: meson.project_version()
  , libraries: gecodedriver_lib
  , requires: [
        'gecodegist'
      , 'gecodeminimodel'
      , 'gecodeset'
      , 'gecodesearch'
      ]
  , subdirs: 'gecode'
  )
