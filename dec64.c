/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2016 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_dec64.h"

#include "dec64.h"
#include "dec64_string.h"

/* {{{ */
typedef dec64 (*dec64_binary_f) (dec64, dec64);
typedef dec64 (*dec64_unary_f) (dec64);
/* }}} */

/* {{{ */
dec64 php_dec64_in(zend_string *string) {
	dec64_string_state state = dec64_string_begin();

	dec64 v = dec64_from_string(state, ZSTR_VAL(string));

	dec64_string_end(state);

	return v;
} /* }}} */

/* {{{ */
zend_string* php_dec64_out(dec64 number) {
	zend_string *out = zend_string_alloc(32, 0);
	dec64_string_state state = dec64_string_begin();

	ZSTR_LEN(out) = dec64_to_string(state, number, ZSTR_VAL(out));

	dec64_string_end(state);

	return out;
} /* }}} */

/* {{{ */
zend_string* php_dec64_unary(dec64_unary_f unary, zend_string *u) {
	return php_dec64_out(
				unary(
					php_dec64_in(u)));
} /* }}} */

/* {{{ */
zend_string* php_dec64_binary(dec64_binary_f binary, zend_string *l, zend_string *r) {
	return php_dec64_out(
				binary(
					php_dec64_in(l), php_dec64_in(r)));
} /* }}} */

/* {{{ proto string dec64_multiply(string l, string r) */
PHP_FUNCTION(dec64_multiply) 
{
	zend_string *l = NULL, 
				*r = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "SS", &l, &r) != SUCCESS) {
		return;
	}

	RETURN_STR(php_dec64_binary(dec64_multiply, l, r));
} /* }}} */

/* {{{ proto string dec64_ceiling(string u) */
PHP_FUNCTION(dec64_ceiling) 
{
	zend_string *u = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "S", &u) != SUCCESS) {
		return;
	}

	RETURN_STR(php_dec64_unary(dec64_ceiling, u));
} /* }}} */

/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(dec64)
{
#if defined(COMPILE_DL_DEC64) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(dec64)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "dec64 support", "enabled");
	php_info_print_table_end();
}
/* }}} */

/* {{{ */
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(php_dec64_binary_info, 0, 2, IS_STRING, NULL, 0)
	ZEND_ARG_TYPE_INFO(0, l, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, r, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(php_dec64_unary_info, 0, 1, IS_STRING, NULL, 0)
	ZEND_ARG_TYPE_INFO(0, u, IS_STRING, 0)
ZEND_END_ARG_INFO()
/* }}} */

/* {{{ dec64_functions[]
 */
const zend_function_entry dec64_functions[] = {
	PHP_FE(dec64_multiply,	     php_dec64_binary_info)
	PHP_FE(dec64_ceiling,        php_dec64_unary_info)
	PHP_FE_END
};
/* }}} */

/* {{{ dec64_module_entry
 */
zend_module_entry dec64_module_entry = {
	STANDARD_MODULE_HEADER,
	"dec64",
	dec64_functions,
	NULL,
	NULL,
	PHP_RINIT(dec64),
	NULL,
	PHP_MINFO(dec64),
	PHP_DEC64_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_DEC64
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(dec64)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
