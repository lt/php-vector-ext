PHP_ARG_ENABLE(vector, whether to enable vector support,
[  --enable-vector           Enable vector support])

if test "$PHP_VECTOR" != "no"; then
  PHP_NEW_EXTENSION(vector, vector.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
