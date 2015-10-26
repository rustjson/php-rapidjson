/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2015 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Jason Young<red.wolf.s.husband@gmail.com                     |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

extern "C" {
#include "php.h"
#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_rapidjson.h"
#include "zend_interfaces.h" //for arrayaccess
#include "Zend/zend_types.h"
}

#include "rapidjson/document.h"     // rapidjson's DOM-style API
#include "rapidjson/prettywriter.h" // for stringify JSON
#include <cstdio>
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
using namespace rapidjson;
using namespace std;



/* If you declare any globals in php_rapidjson.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(rapidjson)
*/

/* True global resources - no need for thread safety here */
static int le_rapidjson;
zend_class_entry *rapidjson_ce;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("rapidjson.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_rapidjson_globals, rapidjson_globals)
    STD_PHP_INI_ENTRY("rapidjson.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_rapidjson_globals, rapidjson_globals)
PHP_INI_END()
*/
/* }}} */


/* {{{ php_rapidjson_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_rapidjson_init_globals(zend_rapidjson_globals *rapidjson_globals)
{
	rapidjson_globals->global_value = 0;
	rapidjson_globals->global_string = NULL;
}
*/
/* }}} */

ZEND_BEGIN_ARG_INFO_EX(arginfo__construct, 0, 0, 1)
	ZEND_ARG_INFO(0, json)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo__destruct, 0, 0, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_offsetset, 0, 0, 2)
ZEND_ARG_INFO(0, offset)
ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_offsetget, 0, 0, 1)
ZEND_ARG_INFO(0, offset)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_offsetexists, 0, 0, 1)
ZEND_ARG_INFO(0, offset)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_offsetunset, 0, 0, 1)
ZEND_ARG_INFO(0, offset)
ZEND_END_ARG_INFO()

/* {{{ rapidjson_functions[] */
const zend_function_entry rapidjson_functions[] = {
	PHP_FE_END	/* Must be the last line in rapidjson_functions[] */
};
/* }}} */

int inline rapidjson_parse(zval *self, char *json) /* {{{ */ {
	zval	zdoc;
	Document *document = new Document();

	if (document->Parse(json).HasParseError()) {
		//TODO Fatal error here;	
		printf("Parse Error\n");
		return -1;
	}
	zdoc.value.ptr = document;
	zend_update_property(rapidjson_ce, self, ZEND_STRL("obj"), &zdoc);
	return 0;
}
/* }}} */

PHP_METHOD(rapidjson, __construct) /* {{{ */ {
	
	uint	len = 0;
	char	*json;
	zval 	*self;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|s", &json, &len) == FAILURE) {
		return;
	}
	
	self = getThis();
	
	if (len > 0) {
		zval	zdoc;
		Document *document = new Document();

		if (document->Parse(json).HasParseError()) {
			//TODO Fatal error here;	
			printf("Parse Error\n");
		}
		zdoc.value.ptr = document;
		zend_update_property(rapidjson_ce, self, ZEND_STRL("obj"), &zdoc);
		//rapidjson_parse(self, json);	
	}
}
/** }}} */

PHP_METHOD(rapidjson, parse) /* {{{ */ {
	
	uint	len = 0;
	char	*json;
	zval 	*self;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &json, &len) == FAILURE) {
		return;
	}
	self = getThis();	
	
	rapidjson_parse(self, json);	
}
/** }}} */

PHP_METHOD(rapidjson, __destruct) /* {{{ */ {
	printf("destructing\n");	
}
/** }}} */

PHP_METHOD(rapidjson, offsetSet) /* {{{ */ {
    // 3. Modify values in document.

    // Change i to a bigger number
   /* {
        uint64_t f20 = 1;   // compute factorial of 20
        for (uint64_t j = 1; j <= 20; j++)
            f20 *= j;
        document["i"] = f20;    // Alternate form: document["i"].SetUint64(f20)
        assert(!document["i"].IsInt()); // No longer can be cast as int or uint.
    }*/
}
/* }}} */

PHP_METHOD(rapidjson, offsetGet) /* {{{ */ {

	zval *offset = NULL;
	zval *value = NULL;
	zval *obj = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &offset) == FAILURE) {
		return;
	}
	
	zval *self = getThis();

	obj = zend_read_property(rapidjson_ce, self, ZEND_STRL("obj"), 1, NULL);
	Document *document;
    document = (Document *)obj->value.ptr;
	//if (!document->HasMember(offset->value.str->val)) {
	
	//StringBuffer buf;
	//Writer<StringBuffer> writer(buf);
	//document->Accept(writer);
	//printf("%s\n", buf.GetString());

	if (!document->HasMember("name")) {
		RETURN_NULL();
		return;	
	}
	const Value& val = (*document)[offset->value.str->val]; 
	if ((val).IsString()) {
		zend_string *ret = zend_string_init((val).GetString(), strlen((val).GetString()), 0);
		RETURN_STR(ret);
	}
	if (val.IsInt() || val.IsUint() || val.IsInt64() || val.IsUint64()) {
		RETURN_LONG(val.GetUint64());	
	}
	if (val.IsDouble()) {
		RETURN_DOUBLE(val.GetDouble());
	}
	if (val.IsBool()) {
		RETURN_BOOL(val.GetBool());	
	}
	if (val.IsObject()) {
		zval zdoc;
		//zdoc.value.ptr = val;
		//RETURN_ZVAL(
	}
}
/* }}} */

PHP_METHOD(rapidjson, offsetExists) /* {{{ */ {
}
/* }}} */

PHP_METHOD(rapidjson, offsetUnset) /* {{{ */ {
}
/* }}} */

static zend_object *rapidjson_object_create(zend_class_entry *ce TSRMLS_DC)
{
}

static const zend_function_entry rapidjson_methods[] = /* {{{ */ {
    PHP_ME(rapidjson, __construct, arginfo__construct, ZEND_ACC_PUBLIC)
    PHP_ME(rapidjson, __destruct,  arginfo__destruct,  ZEND_ACC_PUBLIC)
    PHP_ME(rapidjson, parse, arginfo__construct, ZEND_ACC_PUBLIC)

	PHP_ME(rapidjson, offsetSet,       arginfo_offsetset,       ZEND_ACC_PUBLIC)
	PHP_ME(rapidjson, offsetGet,       arginfo_offsetget,       ZEND_ACC_PUBLIC)
	PHP_ME(rapidjson, offsetExists,    arginfo_offsetexists,    ZEND_ACC_PUBLIC)
	PHP_ME(rapidjson, offsetUnset,     arginfo_offsetunset,     ZEND_ACC_PUBLIC)
	PHP_FE_END
};
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(rapidjson)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	zend_class_entry ce;
   	INIT_CLASS_ENTRY(ce, "Rapidjson", rapidjson_methods);
	
	//ce.create_object = rapidjson_object_create;
    
	rapidjson_ce = zend_register_internal_class(&ce TSRMLS_CC);
	zend_class_implements(rapidjson_ce TSRMLS_CC, 1, zend_ce_arrayaccess);
   	
   	zend_declare_property_null(rapidjson_ce, ZEND_STRL("obj"), 	ZEND_ACC_PROTECTED TSRMLS_CC);

	return SUCCESS;	
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(rapidjson)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(rapidjson)
{
#if defined(COMPILE_DL_RAPIDJSON) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(rapidjson)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(rapidjson)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "rapidjson support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ rapidjson_module_entry
 */
zend_module_entry rapidjson_module_entry = {
	STANDARD_MODULE_HEADER,
	"rapidjson",
	rapidjson_functions,
	PHP_MINIT(rapidjson),
	PHP_MSHUTDOWN(rapidjson),
	PHP_RINIT(rapidjson),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(rapidjson),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(rapidjson),
	PHP_RAPIDJSON_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_RAPIDJSON
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE();
#endif
ZEND_GET_MODULE(rapidjson)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
