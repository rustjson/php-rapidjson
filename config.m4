dnl $Id$
dnl config.m4 for extension php-rapidjson

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(php-rapidjson, for php-rapidjson support,
dnl Make sure that the comment is aligned:
dnl [  --with-php-rapidjson             Include php-rapidjson support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(php-rapidjson, whether to enable php-rapidjson support,
dnl Make sure that the comment is aligned:
[  --enable-php-rapidjson           Enable php-rapidjson support])

if test "$PHP_PHP-RAPIDJSON" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-php-rapidjson -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/php-rapidjson.h"  # you most likely want to change this
  dnl if test -r $PHP_PHP-RAPIDJSON/$SEARCH_FOR; then # path given as parameter
  dnl   PHP-RAPIDJSON_DIR=$PHP_PHP-RAPIDJSON
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for php-rapidjson files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       PHP-RAPIDJSON_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$PHP-RAPIDJSON_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the php-rapidjson distribution])
  dnl fi

  dnl # --with-php-rapidjson -> add include path
  dnl PHP_ADD_INCLUDE($PHP-RAPIDJSON_DIR/include)

  dnl # --with-php-rapidjson -> check for lib and symbol presence
  dnl LIBNAME=php-rapidjson # you may want to change this
  dnl LIBSYMBOL=php-rapidjson # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $PHP-RAPIDJSON_DIR/$PHP_LIBDIR, PHP-RAPIDJSON_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_PHP-RAPIDJSONLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong php-rapidjson lib version or lib not found])
  dnl ],[
  dnl   -L$PHP-RAPIDJSON_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(PHP-RAPIDJSON_SHARED_LIBADD)

  PHP_NEW_EXTENSION(php-rapidjson, php-rapidjson.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
