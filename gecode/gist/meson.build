qt_files = qt6.preprocess(
    moc_headers: [
        'mainwindow.hh'
      , 'nodestats.hh'
      , 'preferences.hh'
      , 'qtgist.hh'
      , 'textoutput.hh'
      , 'treecanvas.hh'
      ]
  )

gecodegist_lib = library(
    'gecodegist'
  , 'drawingcursor.cpp'
  , 'gecodelogo.cpp'
  , 'gist.cpp'
  , 'mainwindow.cpp'
  , 'node.cpp'
  , 'nodestats.cpp'
  , 'nodewidget.cpp'
  , 'preferences.cpp'
  , 'qtgist.cpp'
  , 'spacenode.cpp'
  , 'stopbrancher.cpp'
  , 'textoutput.cpp'
  , 'treecanvas.cpp'
  , 'visualnode.cpp'
  , qt_files
  , include_directories: [
        project_inc
      ]
  , dependencies: [
        qt6_dep
      , gecodesearch_dep
      , gecodeint_dep
      ]
  )

gecodegist_dep = declare_dependency(
    link_with: gecodegist_lib
  , include_directories: [project_inc]
  , dependencies: [
        qt6_dep
      , gecodesearch_dep
      , gecodeint_dep
      ]
  )
