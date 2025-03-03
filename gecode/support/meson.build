enable_int_vars   = get_option('enable_int_vars')
enable_float_vars = get_option('enable_float_vars')
enable_set_vars   = get_option('enable_set_vars')
enable_gist       = get_option('enable_gist')
enable_minimodel  = get_option('enable_minimodel')
enable_search     = get_option('enable_search')
enable_driver     = get_option('enable_driver')
enable_flatzinc   = get_option('enable_flatzinc')

if enable_flatzinc
    enable_search = true
    enable_int_vars = true
    enable_set_vars = true
    enable_float_vars = true
    enable_minimodel = true
    enable_gist = true
    enable_driver = true
endif

if enable_driver
    enable_gist = true
    enable_search = true
    enable_minimodel = true
endif
if enable_float_vars or enable_set_vars or enable_minimodel or enable_gist
    enable_int_vars = true
endif
if enable_gist or enable_minimodel
    enable_search = true
endif
if enable_minimodel
    enable_set_vars = true
    enable_float_vars = true
endif

conf = configuration_data()

conf.set('GECODE_BUILD_SUPPORT', true)
conf.set('GECODE_BUILD_KERNEL', true)
if enable_search
    conf.set('GECODE_BUILD_SEARCH', true)
endif
if enable_int_vars
    conf.set('GECODE_BUILD_INT', true)
endif
if enable_set_vars
    conf.set('GECODE_BUILD_SET', true)
endif
if enable_float_vars
    conf.set('GECODE_BUILD_FLOAT', true)
endif
if enable_minimodel
    conf.set('GECODE_BUILD_MINIMODEL', true)
endif
if enable_flatzinc
    conf.set('GECODE_BUILD_FLATZINC', true)
endif
if enable_driver
    conf.set('GECODE_BUILD_DRIVER', true)
endif
if enable_gist
    conf.set('GECODE_BUILD_GIST', true)
endif

conf.set('GECODE_FREELIST_SIZE_MAX32', get_option('with_freelist32_size_max'))
conf.set('GECODE_FREELIST_SIZE_MAX64', get_option('with_freelist64_size_max'))
conf.set('GECODE_HAS_THREADS', get_option('enable_thread'))

configure_ac = fs.read(project_dir / 'configure.ac', encoding: 'utf-8')

gecode_flatzinc_version_script = '''
import re
import sys

match = re.search(r'ac_gecode_flatzincversion=(.*)', sys.argv[1])

if match:
    print(match.group(1).strip())
else:
    sys.exit(1)
'''
gecode_flatzinc_version_result = run_command(
    'python3'
  , '-c', gecode_flatzinc_version_script
  , configure_ac
  , check: false)
if 0 == gecode_flatzinc_version_result.returncode()
    gecode_flatzinc_version = gecode_flatzinc_version_result.stdout().strip()
    message(f'GECODE_FLATZINC_VERSION = @gecode_flatzinc_version@ from configure.ac')
else
    error('Could not find ac_gecode_flatzincversion in configure.ac')
endif

ac_init_script = '''
import re
import sys

match = re.search(r'AC_INIT\(\s*([^,]*)\s*,\s*([^,]*)\s*,\s*([^)]*)\s*\)', sys.argv[1])

if match:
    print(f'{match.group(1)},{match.group(2)},{match.group(3)}')
else:
    sys.exit(1)
'''
ac_init_script_result = run_command(
    'python3'
  , '-c', ac_init_script
  , configure_ac
  , check: false)
if 0 == ac_init_script_result.returncode()
    ac_init = ac_init_script_result.stdout().strip().split(',')
    package_name = ac_init[0]
    package_version = ac_init[1]
    package_bugreport = ac_init[2]
    project_version = meson.project_version()
    if project_version != package_version
        error(f'Package and project version mismatch: @package_version@ != @project_version@')
    endif
    message(f'PACKAGE_NAME = "@package_name@" from configure.ac')
    message(f'PACKAGE_VERSION = @package_version@ from configure.ac')
    message(f'PACKAGE_BUGREPORT = @package_bugreport@ from configure.ac')
else
    error('Could not find or parse AC_INIT in configure.ac')
endif

has_visibility_hidden = cpp.has_argument('-fvisibility=hidden')
has_cx_limited_range = cpp.has_argument('-fcx-limited-range')
has_no_signaling_nans = cpp.has_argument('-fno-signaling-nans')
has_no_rounding_math = cpp.has_argument('-fno-rounding-math')
has_finite_math_only = cpp.has_argument('-ffinite-math-only')
has_no_math_errno = cpp.has_argument('-fno-math-errno')
has_no_strict_aliasing = cpp.has_argument('-fno-strict-aliasing')
has_builtin_ffsll = cpp.has_function('__builtin_ffsll')
has_builtin_popcountll = cpp.has_function('__builtin_popcountll')
has_gnu_hash_map = cpp.has_header('ext/hash_map')
has_unistd_h = cpp.has_header('unistd.h')
has_unordered_map = cpp.has_header('unordered_map')
has_pthread_h = cpp.has_header('pthread.h')
has_getpagesize = cpp.has_function('getpagesize', prefix: '#include <unistd.h>')
has_inttypes_h = cpp.has_header('inttypes.h')
has_memory_h = cpp.has_header('memory.h')
has_stdint_h = cpp.has_header('stdint.h')
has_stdlib_h = cpp.has_header('stdlib.h')
has_strings_h = cpp.has_header('strings.h')
has_string_h = cpp.has_header('string.h')
has_sys_param_h = cpp.has_header('sys/param.h')
has_sys_stat_h = cpp.has_header('sys/stat.h')
has_sys_types_h = cpp.has_header('sys/types.h')
has_stddef_h = cpp.has_header('stddef.h')

if has_visibility_hidden
    add_project_arguments('-fvisibility=hidden', language: ['cpp'])
endif
if has_cx_limited_range
    add_project_arguments('-fcx-limited-range', language: ['cpp'])
endif
if has_no_signaling_nans
    add_project_arguments('-fno-signaling-nans', language: ['cpp'])
endif
if has_no_rounding_math
    add_project_arguments('-fno-rounding-math', language: ['cpp'])
endif
if has_finite_math_only
    add_project_arguments(
        '-ffinite-math-only'
      , '-Wno-nan-infinity-disabled'
      , language: ['c', 'cpp'])
endif
if has_no_math_errno
    add_project_arguments('-fno-math-errno', language: ['cpp'])
endif
if has_no_strict_aliasing
    add_project_arguments('-fno-strict-aliasing', language: ['cpp'])
endif

if get_option('enable_allocator')
    conf.set('GECODE_ALLOCATOR', true)
endif
if get_option('enable_audit')
    conf.set('GECODE_AUDIT', true)
endif
conf.set('GECODE_DLL_USERPREFIX', get_option('with_lib_prefix'))
conf.set('GECODE_DLL_USERSUFFIX', get_option('with_lib_suffix'))
conf.set('GECODE_FLATZINC_VERSION', f'"@gecode_flatzinc_version@"')
conf.set('GECODE_GCC_HAS_CLASS_VISIBILITY', has_visibility_hidden)
conf.set('GECODE_HAS_BUILTIN_FFSLL', has_builtin_ffsll)
conf.set('GECODE_HAS_BUILTIN_POPCOUNTLL', has_builtin_popcountll)
if get_option('enable_cbs')
    conf.set('GECODE_HAS_CBS', false)
endif
if get_option('enable_cpprofiler')
    conf.set('GECODE_HAS_CPPROFILER', true)
endif
if enable_float_vars
    conf.set('GECODE_HAS_FLOAT_VARS', true)
endif
if enable_gist
    conf.set('GECODE_HAS_QT', qt6_dep.found())
    conf.set('GECODE_HAS_GIST', true)
endif
if enable_int_vars
    conf.set('GECODE_HAS_INT_VARS', true)
endif
conf.set('GECODE_HAS_MPFR', mpfr_dep.found())
if get_option('enable_leak_debug')
    has_mcheck = cpp.has_header('mcheck.h')
    if has_mcheck
        conf.set('GECODE_HAS_MTRACE', true)
    endif
endif
if enable_set_vars
    conf.set('GECODE_HAS_SET_VARS', true)
endif
if has_unistd_h
    conf.set('HAVE_UNISTD_H', 1)
endif
version_with_dashes = meson.project_version().replace('.', '-')
conf.set('GECODE_LIBRARY_VERSION', f'"@version_with_dashes@"')
if get_option('enable_peakheap')
    conf.set('GECODE_PEAKHEAP', true)
    conf.set('GECODE_PEAKHEAP_MALLOC_H', true)
    conf.set('GECODE_MSIZE', 'malloc_usable_size')
endif
lib_type = get_option('default_library')
if lib_type == 'static'
    conf.set('GECODE_STATIC_LIBS', true)
endif
numeric_version_script = '''
import re
match = re.match(r'(\d+)\.(\d+)\.(\d+)', '@0@')
print(int(match.group(1)) * 100000 + int(match.group(2)) * 100 + int(match.group(3)), end = '')
'''
numeric_version_result = run_command(
    'python3'
  , '-c', numeric_version_script.format(meson.project_version())
  , check: false)
if 0 == numeric_version_result.returncode()
    numeric_version = numeric_version_result.stdout().strip()
    message('Numeric version = ' + numeric_version)
else
    error('Could not compute numeric version')
endif

conf.set('GECODE_VERSION_NUMBER', numeric_version)
if has_getpagesize
    conf.set('HAVE_GETPAGESIZE', 1)
endif
if has_inttypes_h
    conf.set('HAVE_INTTYPES_H', 1)
endif
if has_memory_h
    conf.set('HAVE_MEMORY_H', 1)
endif

func_mmap_fixed_mapped = cpp.compiles('''
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
/* malloc might have been renamed as rpl_malloc. */
#undef malloc

/* Thanks to Mike Haertel and Jim Avera for this test.
   Here is a matrix of mmap possibilities:
	mmap private not fixed
	mmap private fixed at somewhere currently unmapped
	mmap private fixed at somewhere already mapped
	mmap shared not fixed
	mmap shared fixed at somewhere currently unmapped
	mmap shared fixed at somewhere already mapped
   For private mappings, we should verify that changes cannot be read()
   back from the file, nor mmap's back from the file at a different
   address.  (There have been systems where private was not correctly
   implemented like the infamous i386 svr4.0, and systems where the
   VM page cache was not coherent with the file system buffer cache
   like early versions of FreeBSD and possibly contemporary NetBSD.)
   For shared mappings, we should conversely verify that changes get
   propagated back to all the places they're supposed to be.

   Grep wants private fixed already mapped.
   The main things grep needs to know about mmap are:
   * does it exist and is it safe to write into the mmap'd area
   * how to use it (BSD variants)  */

#include <fcntl.h>
#include <sys/mman.h>

#if !defined STDC_HEADERS && !defined HAVE_STDLIB_H
char *malloc ();
#endif

/* This mess was copied from the GNU getpagesize.h.  */
#ifndef HAVE_GETPAGESIZE
# ifdef _SC_PAGESIZE
#  define getpagesize() sysconf(_SC_PAGESIZE)
# else /* no _SC_PAGESIZE */
#  ifdef HAVE_SYS_PARAM_H
#   include <sys/param.h>
#   ifdef EXEC_PAGESIZE
#    define getpagesize() EXEC_PAGESIZE
#   else /* no EXEC_PAGESIZE */
#    ifdef NBPG
#     define getpagesize() NBPG * CLSIZE
#     ifndef CLSIZE
#      define CLSIZE 1
#     endif /* no CLSIZE */
#    else /* no NBPG */
#     ifdef NBPC
#      define getpagesize() NBPC
#     else /* no NBPC */
#      ifdef PAGESIZE
#       define getpagesize() PAGESIZE
#      endif /* PAGESIZE */
#     endif /* no NBPC */
#    endif /* no NBPG */
#   endif /* no EXEC_PAGESIZE */
#  else /* no HAVE_SYS_PARAM_H */
#   define getpagesize() 8192	/* punt totally */
#  endif /* no HAVE_SYS_PARAM_H */
# endif /* no _SC_PAGESIZE */

#endif /* no HAVE_GETPAGESIZE */

int
main ()
{
  char *data, *data2, *data3;
  const char *cdata2;
  int i, pagesize;
  int fd, fd2;

  pagesize = getpagesize ();

  /* First, make a file with some known garbage in it. */
  data = (char *) malloc (pagesize);
  if (!data)
    return 1;
  for (i = 0; i < pagesize; ++i)
    *(data + i) = rand ();
  umask (0);
  fd = creat ("conftest.mmap", 0600);
  if (fd < 0)
    return 2;
  if (write (fd, data, pagesize) != pagesize)
    return 3;
  close (fd);

  /* Next, check that the tail of a page is zero-filled.  File must have
     non-zero length, otherwise we risk SIGBUS for entire page.  */
  fd2 = open ("conftest.txt", O_RDWR | O_CREAT | O_TRUNC, 0600);
  if (fd2 < 0)
    return 4;
  cdata2 = "";
  if (write (fd2, cdata2, 1) != 1)
    return 5;
  data2 = (char *) mmap (0, pagesize, PROT_READ | PROT_WRITE, MAP_SHARED, fd2, 0L);
  if (data2 == MAP_FAILED)
    return 6;
  for (i = 0; i < pagesize; ++i)
    if (*(data2 + i))
      return 7;
  close (fd2);
  if (munmap (data2, pagesize))
    return 8;

  /* Next, try to mmap the file at a fixed address which already has
     something else allocated at it.  If we can, also make sure that
     we see the same garbage.  */
  fd = open ("conftest.mmap", O_RDWR);
  if (fd < 0)
    return 9;
  if (data2 != mmap (data2, pagesize, PROT_READ | PROT_WRITE,
                     MAP_PRIVATE | MAP_FIXED, fd, 0L))
    return 10;
  for (i = 0; i < pagesize; ++i)
    if (*(data + i) != *(data2 + i))
      return 11;

  /* Finally, make sure that changes to the mapped area do not
     percolate back to the file as seen by read().  (This is a bug on
     some variants of i386 svr4.0.)  */
  for (i = 0; i < pagesize; ++i)
    *(data2 + i) = *(data2 + i) + 1;
  data3 = (char *) malloc (pagesize);
  if (!data3)
    return 12;
  if (read (fd, data3, pagesize) != pagesize)
    return 13;
  for (i = 0; i < pagesize; ++i)
    if (*(data + i) != *(data3 + i))
      return 14;
  close (fd);
  return 0;
}
''')
if func_mmap_fixed_mapped
    conf.set('HAVE_MMAP', 1)
endif
if has_stdint_h
    conf.set('HAVE_STDINT_H', 1)
endif
if has_stdlib_h
    conf.set('HAVE_STDLIB_H', 1)
endif
if has_strings_h
    conf.set('HAVE_STRINGS_H', 1)
endif
if has_string_h
    conf.set('HAVE_STRING_H', 1)
endif
if has_sys_param_h
    conf.set('HAVE_SYS_PARAM_H', 1)
endif
if has_sys_stat_h
    conf.set('HAVE_SYS_STAT_H', 1)
endif
if has_sys_types_h
    conf.set('HAVE_SYS_TYPES_H', 1)
endif
conf.set('PACKAGE_BUGREPORT', f'"@package_bugreport@"')
conf.set('PACKAGE_NAME', f'"@package_name@"')
conf.set('PACKAGE_STRING', f'"@package_name@ @package_version@"')
package_tarname = package_name.to_lower()
conf.set('PACKAGE_TARNAME', f'"@package_tarname@"')
conf.set('PACKAGE_URL', '""')
conf.set('PACKAGE_VERSION', f'"@package_version@"')
conf.set('GECODE_VERSION', f'"@package_version@"')
conf.set('SIZEOF_INT', cpp.sizeof('int'))
if has_stddef_h
    conf.set('STDC_HEADERS', 1)
endif

configure_file(
    input: 'config.hpp.in'
  , output: 'config.hpp'
  , configuration: conf,
  )

gecodesupport_lib_dependencies = []
if get_option('enable_thread')
    gecodesupport_lib_dependencies += thread_dep
endif

gecodesupport_lib = library(
    'gecodesupport'
  , 'exception.cpp'
  , 'allocator.cpp'
  , 'heap.cpp'
  , 'thread' / 'thread.cpp'
  , 'hw-rnd.cpp'
  , include_directories: [project_inc]
  , dependencies: gecodesupport_lib_dependencies
  , install: true
  )

gecodesupport_dep = declare_dependency(
    link_with: gecodesupport_lib
  , include_directories: [project_inc]
  , dependencies: gecodesupport_lib_dependencies
  )
