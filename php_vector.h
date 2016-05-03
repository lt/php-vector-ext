#ifndef PHP_VECTOR_H
#define PHP_VECTOR_H

extern zend_module_entry vector_module_entry;
#define phpext_vector_ptr &vector_module_entry

#define PHP_VECTOR_VERSION "0.0.1"

#ifdef PHP_WIN32
#	define PHP_VECTOR_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_VECTOR_API __attribute__ ((visibility("default")))
#else
#	define PHP_VECTOR_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

#if defined(ZTS) && defined(COMPILE_DL_VECTOR)
ZEND_TSRMLS_CACHE_EXTERN()
#endif

#endif	/* PHP_VECTOR_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
