gecodeset_lib = library(
    'gecodeset'
  , 'array.cpp'
  , 'bool.cpp'
  , 'branch.cpp'
  , 'cardinality.cpp'
  , 'channel.cpp'
  , 'convex.cpp'
  , 'distinct.cpp'
  , 'dom.cpp'
  , 'element.cpp'
  , 'exception.cpp'
  , 'exec.cpp'
  , 'int.cpp'
  , 'ldsb.cpp'
  , 'precede.cpp'
  , 'rel-op-const-cvc.cpp'
  , 'rel-op-const-cvv.cpp'
  , 'rel-op-const-vcc.cpp'
  , 'rel-op-const-vcv.cpp'
  , 'rel-op-const-vvc.cpp'
  , 'rel-op-singleton.cpp'
  , 'rel-op-ternary.cpp'
  , 'rel-op.cpp'
  , 'rel.cpp'
  , 'relax.cpp'
  , 'sequence.cpp'
  , 'trace.cpp'
  , 'trace/tracer.cpp'
  , 'branch' / 'action.cpp'
  , 'branch' / 'chb.cpp'
  , 'branch' / 'ngl.cpp'
  , 'branch' / 'val-sel-commit.cpp'
  , 'branch' / 'view-sel.cpp'
  , 'convex' / 'conv.cpp'
  , 'convex' / 'hull.cpp'
  , 'distinct' / 'atmostOne.cpp'
  , 'ldsb' / 'sym-imp.cpp'
  , 'rel-op' / 'post-compl-cvc.cpp'
  , 'rel-op' / 'post-compl-cvv.cpp'
  , 'rel-op' / 'post-compl-vvc.cpp'
  , 'rel-op' / 'post-compl.cpp'
  , 'rel-op' / 'post-nocompl-cvc.cpp'
  , 'rel-op' / 'post-nocompl-cvv.cpp'
  , 'rel-op' / 'post-nocompl-vvc.cpp'
  , 'rel-op' / 'post-nocompl.cpp'
  , 'sequence' / 'seq-u.cpp'
  , 'sequence' / 'seq.cpp'
  , 'var-imp' / 'integerset.cpp'
  , 'var-imp' / 'set.cpp'
  , 'var' / 'set.cpp'
  , include_directories: [project_inc]
  , dependencies: [
        gecodeint_dep
      , gecodekernel_dep
      ]
  , install: true
  )

gecodeset_dep = declare_dependency(
    link_with: gecodeset_lib
  , include_directories: [project_inc]
  , dependencies: [
        gecodeint_dep
      , gecodekernel_dep
      ]
  )

pkg.generate(
    name: 'gecodeset'
  , filebase: 'gecodeset'
  , description: 'Gecode finite set library'
  , version: meson.project_version()
  , libraries: gecodeset_lib
  , requires: [
        'gecodeint'
      , 'gecodekernel'
      ]
  , subdirs: 'gecode'
  )


subdir('branch')
subdir('channel')
subdir('convex')
subdir('distinct')
subdir('element')
subdir('int')
subdir('ldsb')
subdir('precede')
subdir('rel')
subdir('rel-op')
subdir('sequence')
subdir('trace')
subdir('var')
subdir('var-imp')
subdir('view')

install_headers(
    'branch.hh'
  , 'channel.hh'
  , 'convex.hh'
  , 'distinct.hh'
  , 'element.hh'
  , 'int.hh'
  , 'ldsb.hh'
  , 'precede.hh'
  , 'rel.hh'
  , 'rel-op.hh'
  , 'sequence.hh'
  , 'array.hpp'
  , 'array-traits.hpp'
  , 'branch.hpp'
  , 'exception.hpp'
  , 'int.hpp'
  , 'limits.hpp'
  , 'trace.hpp'
  , 'var-imp.hpp'
  , 'view.hpp'
  , subdir: 'gecode/set'
  )
