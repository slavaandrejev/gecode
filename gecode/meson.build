subdir('support')
subdir('kernel')

if enable_search
    subdir('search')
endif
if enable_int_vars
    subdir('int')
endif
if enable_float_vars
    subdir('float')
endif
if enable_set_vars
    subdir('set')
endif
if enable_gist
    subdir('gist')
endif
if enable_minimodel
    subdir('minimodel')
endif
if enable_driver
    subdir('driver')
endif
if enable_flatzinc
    subdir('flatzinc')
endif
subdir('iter')

install_headers(
    'driver.hh'
  , 'flatzinc.hh'
  , 'float.hh'
  , 'gist.hh'
  , 'int.hh'
  , 'iter.hh'
  , 'kernel.hh'
  , 'minimodel.hh'
  , 'search.hh'
  , 'set.hh'
  , 'support.hh'
  , subdir: 'gecode'
  )
