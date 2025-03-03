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
  , install: true
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

pkg.generate(
    name: 'gecodegist'
  , filebase: 'gecodegist'
  , description: 'Gecode Interactive Search Tool'
  , version: meson.project_version()
  , libraries: gecodegist_lib
  , requires: [
        'gecodesearch'
      , 'gecodeint'
      ]
  , subdirs: 'gecode'
  )

install_headers(
    'drawingcursor.hh'
  , 'gecodelogo.hh'
  , 'layoutcursor.hh'
  , 'mainwindow.hh'
  , 'node.hh'
  , 'nodecursor.hh'
  , 'nodestats.hh'
  , 'nodevisitor.hh'
  , 'nodewidget.hh'
  , 'preferences.hh'
  , 'qtgist.hh'
  , 'spacenode.hh'
  , 'stopbrancher.hh'
  , 'textoutput.hh'
  , 'treecanvas.hh'
  , 'visualnode.hh'
  , 'drawingcursor.hpp'
  , 'gist.hpp'
  , 'layoutcursor.hpp'
  , 'node.hpp'
  , 'nodecursor.hpp'
  , 'nodevisitor.hpp'
  , 'spacenode.hpp'
  , 'visualnode.hpp'
  , 'zoomToFitIcon.hpp'
  , subdir: 'gecode/gist'
  )
