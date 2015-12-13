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
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("rapidjson.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_rapidjson_globals, rapidjson_globals)
    STD_PHP_INI_ENTRY("rapidjson.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_rapidjson_globals, rapidjson_globals)
PHP_INI_END()
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

ZEND_BEGIN_ARG_INFO_EX(arginfo__void, 0, 0, 1)
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
	zval	zdoc = {{0}};
	Document *document = new Document();


	if (document->Parse(json).HasParseError()) {
		//TODO Fatal error here;	
		printf("Parse Error\n");
		return -1;
	}

	ZVAL_PTR(&zdoc, document);

	zend_update_property(rapidjson_ce, self, ZEND_STRL("obj"), &zdoc);
	
	zval_ptr_dtor(&zdoc);
	return 0;
}
/* }}} */

PHP_METHOD(rapidjson, __construct) /* {{{ */ {
	
	zend_string *json = NULL;
	zval 		*self = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|S", &json) == FAILURE) {
		return;
	}
	
	self = getThis();
	
	if (json != NULL && json->len > 0) {
		rapidjson_parse(self, json->val);	
	}
}
/** }}} */

PHP_METHOD(rapidjson, parse) /* {{{ */ {
	
	zend_string	*json = NULL;
	zval 		*self = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "S", &json) == FAILURE) {
		return;
	}
	self = getThis();	
	
	rapidjson_parse(self, json->val);	
}
/** }}} */

PHP_METHOD(rapidjson, __toString) /* {{{ */ {

	zval *self 	= getThis();
	zval *obj 	= NULL;

	obj = zend_read_property(rapidjson_ce, self, ZEND_STRL("obj"), 1, NULL);
	Document *document = (Document *)obj->value.ptr;
    
	StringBuffer sb;
    PrettyWriter<StringBuffer> writer(sb);
    document->Accept(writer);    // Accept() traverses the DOM and generates Handler events.
    //puts(sb.GetString());
	
	zend_string *ret = zend_string_init(sb.GetString(), strlen(sb.GetString()), 0);
	RETURN_STR(ret);
}
/* }}} */

PHP_METHOD(rapidjson, __destruct) /* {{{ */ {
	//printf("destructing\n");	
}
/** }}} */

PHP_METHOD(rapidjson, offsetSet) /* {{{ */ {
	zend_string *key = NULL;
	zval 		*value = NULL;
	zval 		*obj = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "Sz", &key, &value) == FAILURE) {
		return;
	}
	
	zval *self = getThis();

	obj = zend_read_property(rapidjson_ce, self, ZEND_STRL("obj"), 1, NULL);
	Document *document;
    document = (Document *)obj->value.ptr;
	
	if (!document->HasMember(key->val)) {
		RETURN_NULL();
		return;	
	}
	Value& val = (*document)[key->val]; 
	
	if (IS_STRING == Z_TYPE_P(value)) {
		val.SetString(StringRef(Z_STRVAL_P(value), Z_STRLEN_P(value)));
	} else if (IS_LONG == Z_TYPE_P(value)) {
		val.SetInt64(Z_LVAL_P(value));
	} else if (IS_NULL == Z_TYPE_P(value)) {
		val.SetNull();
	}
}
/* }}} */

PHP_METHOD(rapidjson, offsetGet) /* {{{ */ {

	zend_string *key = NULL;
	zval 		*value = NULL;
	zval 		*obj = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "S", &key) == FAILURE) {
		return;
	}
	
	zval *self = getThis();

	obj = zend_read_property(rapidjson_ce, self, ZEND_STRL("obj"), 1, NULL);
	Document *document;
    document = (Document *)obj->value.ptr;

	if (!document->HasMember(key->val)) {
		RETURN_NULL();
		return;	
	}
	const Value& val = (*document)[key->val]; 
	if (val.IsString()) {
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

	zend_string *key = NULL;
	zval 		*value = NULL;
	zval 		*obj = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "S", &key) == FAILURE) {
		return;
	}
	zval *self = getThis();

	obj = zend_read_property(rapidjson_ce, self, ZEND_STRL("obj"), 1, NULL);
	Document *document;
    document = (Document *)obj->value.ptr;
	
	if (!document->HasMember(key->val)) {
		RETURN_FALSE;	
	} else {
		RETURN_TRUE;
	}
}
/* }}} */

PHP_METHOD(rapidjson, offsetUnset) /* {{{ */ {
	
	zend_string *key = NULL;
	zval 		*value = NULL;
	zval 		*obj = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "S", &key) == FAILURE) {
		return;
	}
	zval *self = getThis();

	obj = zend_read_property(rapidjson_ce, self, ZEND_STRL("obj"), 1, NULL);
	Document *document;
    document = (Document *)obj->value.ptr;
	document->RemoveMember(key->val);
}
/* }}} */

PHP_METHOD(rapidjson, current) /* {{{ */ {

	zval *self = getThis();

	zval *obj = zend_read_property(rapidjson_ce, self, ZEND_STRL("obj"), 1, NULL);
	zval *ost = zend_read_property(rapidjson_ce, self, ZEND_STRL("ost"), 1, NULL);
	
	Document *document = (Document *)obj->value.ptr;
	
	Value::ConstMemberIterator itr = document->MemberBegin();
	itr += ost->value.lval;
	
    //static const char* typeNames[] = { "Null", "False", "True", "Object", "Array", "String", "Number" };
	if (itr->value.GetType() == 5) {

		zend_string *ret = zend_string_init(itr->value.GetString(), strlen(itr->value.GetString()), 0);
		RETURN_STR(ret);
	} else if (itr->value.GetType() == 6) {
		RETURN_LONG(itr->value.GetUint64());	
	} else if (itr->value.GetType() == 1) {
		RETURN_FALSE;
	} else if (itr->value.GetType() == 2) {
		RETURN_TRUE;
	} else if (itr->value.GetType() == 0) {
		RETURN_NULL();
	}
}
/* }}} */

PHP_METHOD(rapidjson, key) /* {{{ */ {
	zval *self = getThis();

	zval *obj = zend_read_property(rapidjson_ce, self, ZEND_STRL("obj"), 1, NULL);
	zval *ost = zend_read_property(rapidjson_ce, self, ZEND_STRL("ost"), 1, NULL);
	
	Document *document;
    document = (Document *)obj->value.ptr;
	
    
	Value::ConstMemberIterator itr = document->MemberBegin();
	itr += ost->value.lval;
	zend_string *ret = zend_string_init(itr->name.GetString(), strlen(itr->name.GetString()), 0);
	RETURN_STR(ret);
}
/* }}} */

PHP_METHOD(rapidjson, next) /* {{{ */ {
	zval *self = getThis();

	zval *ost = zend_read_property(rapidjson_ce, self, ZEND_STRL("ost"), 1, NULL);
	ost->value.lval++;	
}
/* }}} */

PHP_METHOD(rapidjson, rewind) /* {{{ */ {
	zval *self = getThis();

	zval *ost = zend_read_property(rapidjson_ce, self, ZEND_STRL("ost"), 1, NULL);
	ost->value.lval = 0;	
}
/* }}} */

PHP_METHOD(rapidjson, valid) /* {{{ */ {
	zval *self = getThis();

	zval *obj = zend_read_property(rapidjson_ce, self, ZEND_STRL("obj"), 1, NULL);
	zval *ost = zend_read_property(rapidjson_ce, self, ZEND_STRL("ost"), 1, NULL);
	
	Document *document = (Document *)obj->value.ptr;
    
	Value::ConstMemberIterator itr = document->MemberBegin();
	itr += ost->value.lval;
	if (itr != document->MemberEnd()) {
		RETURN_TRUE;	
	} else {
		RETURN_FALSE;
	}
}
/* }}} */

static zend_object *rapidjson_object_create(zend_class_entry *ce TSRMLS_DC)
{
}

static const zend_function_entry rapidjson_methods[] = /* {{{ */ {
    PHP_ME(rapidjson, __construct, arginfo__construct, ZEND_ACC_PUBLIC)
    PHP_ME(rapidjson, __destruct,  arginfo__void,  ZEND_ACC_PUBLIC)
	PHP_ME(rapidjson, __toString,  arginfo__void, ZEND_ACC_PUBLIC)
    
	PHP_ME(rapidjson, parse, arginfo__construct, ZEND_ACC_PUBLIC)

	PHP_ME(rapidjson, offsetSet,       arginfo_offsetset,       ZEND_ACC_PUBLIC)
	PHP_ME(rapidjson, offsetGet,       arginfo_offsetget,       ZEND_ACC_PUBLIC)
	PHP_ME(rapidjson, offsetExists,    arginfo_offsetexists,    ZEND_ACC_PUBLIC)
	PHP_ME(rapidjson, offsetUnset,     arginfo_offsetunset,     ZEND_ACC_PUBLIC)
	
    PHP_ME(rapidjson, current,  arginfo__void,  ZEND_ACC_PUBLIC)
    PHP_ME(rapidjson, key, 		arginfo__void,  ZEND_ACC_PUBLIC)
    PHP_ME(rapidjson, next,  	arginfo__void,  ZEND_ACC_PUBLIC)
    PHP_ME(rapidjson, rewind,  	arginfo__void,  ZEND_ACC_PUBLIC)
    PHP_ME(rapidjson, valid,  	arginfo__void,  ZEND_ACC_PUBLIC)
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
	zend_class_implements(rapidjson_ce TSRMLS_CC, 1, zend_ce_iterator);
   	
   	zend_declare_property_null(rapidjson_ce, ZEND_STRL("obj"), 	  ZEND_ACC_PROTECTED TSRMLS_CC);
   	zend_declare_property_long(rapidjson_ce, ZEND_STRL("ost"), 0, ZEND_ACC_PROTECTED TSRMLS_CC);

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
	php_info_print_table_header(2, "rapidjson version", RAPIDJSON_VERSION_STRING);
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
