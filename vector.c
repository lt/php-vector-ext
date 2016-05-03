#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "zend_exceptions.h"
#include "php_vector.h"

#define INIT_VECTOR_OBJ(zval, ce) \
	ZVAL_OBJ(zval, vector_create_object(ce));

#define IS_VECTOR(zval) \
	(Z_TYPE_P(zval) == IS_OBJECT && ( \
		Z_OBJCE_P(zval) == vector2_ce || \
		Z_OBJCE_P(zval) == vector3_ce || \
		Z_OBJCE_P(zval) == vector4_ce) \
	)

zend_class_entry *vector2_ce;
zend_class_entry *vector3_ce;
zend_class_entry *vector4_ce;

PHP_METHOD(Vector2, __construct)
{
	double x, y;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "dd", &x, &y) == FAILURE) {
		return;
	}

	return_value = getThis();

	zend_update_property_double(vector2_ce, return_value, "x", 1, x);
	zend_update_property_double(vector2_ce, return_value, "y", 1, y);
}

PHP_METHOD(Vector3, __construct)
{
	double x, y, z;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "ddd", &x, &y, &z) == FAILURE) {
		return;
	}

	return_value = getThis();

	zend_update_property_double(vector3_ce, return_value, "x", 1, x);
	zend_update_property_double(vector3_ce, return_value, "y", 1, y);
	zend_update_property_double(vector3_ce, return_value, "z", 1, z);
}

PHP_METHOD(Vector4, __construct)
{
	double x, y, z, w;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "dddd", &x, &y, &z, &w) == FAILURE) {
		return;
	}

	return_value = getThis();

	zend_update_property_double(vector4_ce, return_value, "x", 1, x);
	zend_update_property_double(vector4_ce, return_value, "y", 1, y);
	zend_update_property_double(vector4_ce, return_value, "z", 1, z);
	zend_update_property_double(vector4_ce, return_value, "w", 1, w);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_vector2_construct, 0, 0, 2)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_vector3_construct, 0, 0, 3)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_vector4_construct, 0, 0, 4)
ZEND_END_ARG_INFO()

static zend_function_entry vector2_class_functions[] = {
	PHP_ME(Vector2, __construct, arginfo_vector2_construct, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

static zend_function_entry vector3_class_functions[] = {
	PHP_ME(Vector3, __construct, arginfo_vector3_construct, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

static zend_function_entry vector4_class_functions[] = {
	PHP_ME(Vector4, __construct, arginfo_vector4_construct, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
static zend_object_handlers vector_object_handlers;

static zend_object *vector_create_object(zend_class_entry *ce) /* {{{ */
{
	zend_object *object;

	object = zend_objects_new(ce);
	object->handlers = &vector_object_handlers;
	object_properties_init(object, ce);

	return object;
}
/* }}} */

static int vector_add(zval *result, zval *vec1, zval *vec2) /* {{{ */
{
	zval *d1, *d2;
	zval rv;
	zend_class_entry *ce = Z_OBJCE_P(vec1);

	INIT_VECTOR_OBJ(result, ce);

	if (ce == vector4_ce) {
		d1 = zend_read_property(ce, vec1, "w", 1, 0, &rv);
		d2 = zend_read_property(ce, vec2, "w", 1, 0, &rv);
		zend_update_property_double(ce, result, "w", 1, Z_DVAL_P(d1) + Z_DVAL_P(d2));
	}

	if (ce == vector4_ce || ce == vector3_ce) {
		d1 = zend_read_property(ce, vec1, "z", 1, 0, &rv);
		d2 = zend_read_property(ce, vec2, "z", 1, 0, &rv);
		zend_update_property_double(ce, result, "z", 1, Z_DVAL_P(d1) + Z_DVAL_P(d2));
	}

	d1 = zend_read_property(ce, vec1, "y", 1, 0, &rv);
	d2 = zend_read_property(ce, vec2, "y", 1, 0, &rv);
	zend_update_property_double(ce, result, "y", 1, Z_DVAL_P(d1) + Z_DVAL_P(d2));

	d1 = zend_read_property(ce, vec1, "x", 1, 0, &rv);
	d2 = zend_read_property(ce, vec2, "x", 1, 0, &rv);
	zend_update_property_double(ce, result, "x", 1, Z_DVAL_P(d1) + Z_DVAL_P(d2));

	return SUCCESS;
}
/* }}} */

static int vector_sub(zval *result, zval *vec1, zval *vec2) /* {{{ */
{
	zval *d1, *d2;
	zval rv;
	zend_class_entry *ce = Z_OBJCE_P(vec1);

	INIT_VECTOR_OBJ(result, ce);

	if (ce == vector4_ce) {
		d1 = zend_read_property(ce, vec1, "w", 1, 0, &rv);
		d2 = zend_read_property(ce, vec2, "w", 1, 0, &rv);
		zend_update_property_double(ce, result, "w", 1, Z_DVAL_P(d1) - Z_DVAL_P(d2));
	}

	if (ce == vector4_ce || ce == vector3_ce) {
		d1 = zend_read_property(ce, vec1, "z", 1, 0, &rv);
		d2 = zend_read_property(ce, vec2, "z", 1, 0, &rv);
		zend_update_property_double(ce, result, "z", 1, Z_DVAL_P(d1) - Z_DVAL_P(d2));
	}

	d1 = zend_read_property(ce, vec1, "y", 1, 0, &rv);
	d2 = zend_read_property(ce, vec2, "y", 1, 0, &rv);
	zend_update_property_double(ce, result, "y", 1, Z_DVAL_P(d1) - Z_DVAL_P(d2));

	d1 = zend_read_property(ce, vec1, "x", 1, 0, &rv);
	d2 = zend_read_property(ce, vec2, "x", 1, 0, &rv);
	zend_update_property_double(ce, result, "x", 1, Z_DVAL_P(d1) - Z_DVAL_P(d2));

	return SUCCESS;
}
/* }}} */

static int vector_mul(zval *result, zval *vec, double value) /* {{{ */
{
	zval *d1;
	zval rv;
	zend_class_entry *ce = Z_OBJCE_P(vec);

	INIT_VECTOR_OBJ(result, ce);

	if (ce == vector4_ce) {
		d1 = zend_read_property(ce, vec, "w", 1, 0, &rv);
		zend_update_property_double(ce, result, "w", 1, Z_DVAL_P(d1) * value);
	}

	if (ce == vector4_ce || ce == vector3_ce) {
		d1 = zend_read_property(ce, vec, "z", 1, 0, &rv);
		zend_update_property_double(ce, result, "z", 1, Z_DVAL_P(d1) * value);
	}

	d1 = zend_read_property(ce, vec, "y", 1, 0, &rv);
	zend_update_property_double(ce, result, "y", 1, Z_DVAL_P(d1) * value);

	d1 = zend_read_property(ce, vec, "x", 1, 0, &rv);
	zend_update_property_double(ce, result, "x", 1, Z_DVAL_P(d1) * value);

	return SUCCESS;
}
/* }}} */

static int vector_div(zval *result, zval *vec, double value) /* {{{ */
{
	zval *d1;
	zval rv;
	zend_class_entry *ce = Z_OBJCE_P(vec);

	INIT_VECTOR_OBJ(result, ce);

	if (ce == vector4_ce) {
		d1 = zend_read_property(ce, vec, "w", 1, 0, &rv);
		zend_update_property_double(ce, result, "w", 1, Z_DVAL_P(d1) / value);
	}

	if (ce == vector4_ce || ce == vector3_ce) {
		d1 = zend_read_property(ce, vec, "z", 1, 0, &rv);
		zend_update_property_double(ce, result, "z", 1, Z_DVAL_P(d1) / value);
	}

	d1 = zend_read_property(ce, vec, "y", 1, 0, &rv);
	zend_update_property_double(ce, result, "y", 1, Z_DVAL_P(d1) / value);

	d1 = zend_read_property(ce, vec, "x", 1, 0, &rv);
	zend_update_property_double(ce, result, "x", 1, Z_DVAL_P(d1) / value);

	return SUCCESS;
}
/* }}} */

static int vector_vector_op(zend_uchar opcode, zval *result, zval *vec1, zval *vec2) /* {{{ */
{
	if (Z_OBJCE_P(vec1) != Z_OBJCE_P(vec2)) {
		zend_throw_exception(NULL, "Vectors must be of the same type", 0);
		return FAILURE;
	}
	
	switch(opcode) {
		case ZEND_ADD:
			return vector_add(result, vec1, vec2);
		case ZEND_SUB:
			return vector_sub(result, vec1, vec2);
	}

	zend_throw_exception(NULL, "Unsupported vector operation", 0);
	return FAILURE;
}
/* }}} */

static int vector_double_op(zend_uchar opcode, zval *result, zval *vec, double value) /* {{{ */
{
	switch(opcode) {
		case ZEND_MUL:
			return vector_mul(result, vec, value);
		case ZEND_DIV:
			return vector_div(result, vec, value);
	}

	zend_throw_exception(NULL, "Unsupported vector operation", 0);
	return FAILURE;
}
/* }}} */

static int vector_do_operation(zend_uchar opcode, zval *result, zval *op1, zval *op2) /* {{{ */
{
	zval op1_copy, op2_copy;
	int retval;

	if (result == op1) {
		ZVAL_COPY_VALUE(&op1_copy, op1);
		op1 = &op1_copy;
	}

	if (result == op2) {
		ZVAL_COPY_VALUE(&op2_copy, op2);
		op2 = &op2_copy;
	}

	if (IS_VECTOR(op1)) {
		if (IS_VECTOR(op2)) {
			retval = vector_vector_op(opcode, result, op1, op2);
		}
		else {
			retval = vector_double_op(opcode, result, op1, zval_get_double(op2));
		}
	}
	else {
		// one of op1 or op2 has to be a vector object...
		retval = vector_double_op(opcode, result, op2, zval_get_double(op1));
	}

	if (retval == SUCCESS) {
		if (op1 == &op1_copy) {
			zval_dtor(op1);
		}
		if (op2 == &op2_copy) {
			zval_dtor(op2);
		}
	}

	return retval;
}
/* }}} */

static int vector_compare(zval *result, zval *op1, zval *op2) /* {{{ */
{
	ZVAL_LONG(result, 1);
	return SUCCESS;
}
/* }}} */

static void vector_write_property(zval *object, zval *member, zval *value, void **cache_slot) /* {{{ */
{
	zval tmp;

	if (zend_hash_exists(&Z_OBJCE_P(object)->properties_info, Z_STR_P(member))) {
		ZVAL_DOUBLE(&tmp, zval_get_double(value));
		zend_get_std_object_handlers()->write_property(object, member, &tmp, cache_slot);
	}
}
/* }}} */

PHP_MINIT_FUNCTION(vector) /* {{{ */
{
	zend_class_entry tmp_ce;

	INIT_CLASS_ENTRY(tmp_ce, "Vector2", vector2_class_functions);
	vector2_ce = zend_register_internal_class(&tmp_ce);
	vector2_ce->create_object = vector_create_object;
	zend_declare_property_double(vector2_ce, "x", 1, 0.0, ZEND_ACC_PUBLIC);
	zend_declare_property_double(vector2_ce, "y", 1, 0.0, ZEND_ACC_PUBLIC);

	INIT_CLASS_ENTRY(tmp_ce, "Vector3", vector3_class_functions);
	vector3_ce = zend_register_internal_class(&tmp_ce);
	vector3_ce->create_object = vector_create_object;
	zend_declare_property_double(vector3_ce, "x", 1, 0.0, ZEND_ACC_PUBLIC);
	zend_declare_property_double(vector3_ce, "y", 1, 0.0, ZEND_ACC_PUBLIC);
	zend_declare_property_double(vector3_ce, "z", 1, 0.0, ZEND_ACC_PUBLIC);

	INIT_CLASS_ENTRY(tmp_ce, "Vector4", vector4_class_functions);
	vector4_ce = zend_register_internal_class(&tmp_ce);
	vector4_ce->create_object = vector_create_object;
	zend_declare_property_double(vector4_ce, "x", 1, 0.0, ZEND_ACC_PUBLIC);
	zend_declare_property_double(vector4_ce, "y", 1, 0.0, ZEND_ACC_PUBLIC);
	zend_declare_property_double(vector4_ce, "z", 1, 0.0, ZEND_ACC_PUBLIC);
	zend_declare_property_double(vector4_ce, "w", 1, 0.0, ZEND_ACC_PUBLIC);

	memcpy(&vector_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
//	vector_object_handlers.get_debug_info = vector_get_debug_info;
	vector_object_handlers.do_operation = vector_do_operation;
	vector_object_handlers.compare = vector_compare;
	vector_object_handlers.write_property = vector_write_property;

	return SUCCESS;
}
/* }}} */

PHP_RINIT_FUNCTION(vector) /* {{{ */
{
#if defined(COMPILE_DL_VECTOR) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

PHP_MINFO_FUNCTION(vector) /* {{{ */
{
	php_info_print_table_start();
	php_info_print_table_header(2, "Vector support", "enabled");
	php_info_print_table_end();
}
/* }}} */

zend_module_entry vector_module_entry = { /* {{{ */
	STANDARD_MODULE_HEADER,
	"vector",
	NULL,
	PHP_MINIT(vector),
	NULL,
	PHP_RINIT(vector),
	NULL,
	PHP_MINFO(vector),
	PHP_VECTOR_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_VECTOR
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(vector)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
