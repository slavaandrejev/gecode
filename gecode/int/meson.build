gecodeint_lib = library(
    'gecodeint'
  , 'arithmetic.cpp'
  , 'array.cpp'
  , 'bin-packing.cpp'
  , 'bool.cpp'
  , 'branch.cpp'
  , 'channel.cpp'
  , 'circuit.cpp'
  , 'count.cpp'
  , 'cumulative.cpp'
  , 'cumulatives.cpp'
  , 'distinct.cpp'
  , 'dom.cpp'
  , 'element.cpp'
  , 'exception.cpp'
  , 'exec.cpp'
  , 'extensional-regular.cpp'
  , 'extensional-tuple-set.cpp'
  , 'gcc.cpp'
  , 'int-set.cpp'
  , 'ldsb.cpp'
  , 'linear-bool.cpp'
  , 'linear-int.cpp'
  , 'member.cpp'
  , 'no-overlap.cpp'
  , 'nvalues.cpp'
  , 'order.cpp'
  , 'precede.cpp'
  , 'rel.cpp'
  , 'relax.cpp'
  , 'sequence.cpp'
  , 'sorted.cpp'
  , 'trace.cpp'
  , 'unary.cpp'
  , 'unshare.cpp'
  , 'arithmetic' / 'mult.cpp'
  , 'bin-packing' / 'conflict-graph.cpp'
  , 'bin-packing' / 'propagate.cpp'
  , 'bool' / 'eqv.cpp'
  , 'branch' / 'action.cpp'
  , 'branch' / 'chb.cpp'
  , 'branch' / 'val-sel-commit.cpp'
  , 'branch' / 'view-sel.cpp'
  , 'branch' / 'view-values.cpp'
  , 'channel' / 'link-multi.cpp'
  , 'channel' / 'link-single.cpp'
  , 'distinct' / 'eqite.cpp'
  , 'distinct'/ 'cbs.cpp'
  , 'element' / 'pair.cpp'
  , 'exec' / 'when.cpp'
  , 'extensional' / 'dfa.cpp'
  , 'extensional' / 'tuple-set.cpp'
  , 'ldsb' / 'sym-imp.cpp'
  , 'ldsb' / 'sym-obj.cpp'
  , 'linear' / 'int-post.cpp'
  , 'linear'/ 'bool-post.cpp'
  , 'order' / 'propagate.cpp'
  , 'trace' / 'tracer.cpp'
  , 'var-imp' / 'bool.cpp'
  , 'var-imp' / 'int.cpp'
  , 'var' / 'bool.cpp'
  , 'var' / 'int.cpp'
  , include_directories: [project_inc]
  , dependencies: [gecodekernel_dep]
  , install: true
  )

gecodeint_dep = declare_dependency(
    link_with: gecodeint_lib
  , include_directories: [project_inc]
  , dependencies: [gecodekernel_dep]
  )

pkg.generate(
    name: 'gecodeint'
  , filebase: 'gecodeint'
  , description: 'Gecode finite domain library'
  , version: meson.project_version()
  , libraries: gecodeint_lib
  , requires: ['gecodekernel']
  , subdirs: 'gecode'
  )

subdir('arithmetic')
subdir('bin-packing')
subdir('bool')
subdir('branch')
subdir('channel')
subdir('circuit')
subdir('count')
subdir('cumulative')
subdir('cumulatives')
subdir('distinct')
subdir('dom')
subdir('element')
subdir('exec')
subdir('extensional')
subdir('gcc')
subdir('ldsb')
subdir('linear')
subdir('member')
subdir('no-overlap')
subdir('nvalues')
subdir('order')
subdir('precede')
subdir('rel')
subdir('sequence')
subdir('sorted')
subdir('task')
subdir('trace')
subdir('unary')
subdir('var')
subdir('var-imp')
subdir('view')
subdir('view-val-graph')

install_headers(
    'arithmetic.hh'
  , 'bin-packing.hh'
  , 'bool.hh'
  , 'branch.hh'
  , 'channel.hh'
  , 'circuit.hh'
  , 'count.hh'
  , 'cumulative.hh'
  , 'cumulatives.hh'
  , 'distinct.hh'
  , 'div.hh'
  , 'dom.hh'
  , 'element.hh'
  , 'exec.hh'
  , 'extensional.hh'
  , 'gcc.hh'
  , 'idx-view.hh'
  , 'ldsb.hh'
  , 'linear.hh'
  , 'member.hh'
  , 'no-overlap.hh'
  , 'nvalues.hh'
  , 'order.hh'
  , 'precede.hh'
  , 'rel.hh'
  , 'sequence.hh'
  , 'sorted.hh'
  , 'support-values.hh'
  , 'task.hh'
  , 'unary.hh'
  , 'val-set.hh'
  , 'view-val-graph.hh'
  , 'array.hpp'
  , 'array-traits.hpp'
  , 'branch.hpp'
  , 'channel.hpp'
  , 'div.hpp'
  , 'exception.hpp'
  , 'extensional.hpp'
  , 'idx-view.hpp'
  , 'int-set-1.hpp'
  , 'int-set-2.hpp'
  , 'ipl.hpp'
  , 'irt.hpp'
  , 'limits.hpp'
  , 'propagator.hpp'
  , 'reify.hpp'
  , 'support-values.hpp'
  , 'trace.hpp'
  , 'val-set.hpp'
  , 'var-imp.hpp'
  , 'view.hpp'
  , subdir: 'gecode/int'
  )
