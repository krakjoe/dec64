dnl $Id$
dnl config.m4 for extension dec64

PHP_ARG_ENABLE(dec64, whether to enable dec64 support,
[  --enable-dec64           Enable dec64 support])

if test "$PHP_DEC64" != "no"; then
  PHP_NEW_EXTENSION(dec64, dec64.c dec64_string.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
  shared_objects_dec64="$shared_objects_dec64 lib.o"
  PHP_SUBST(shared_objects_dec64)
  PHP_ADD_MAKEFILE_FRAGMENT()
fi
