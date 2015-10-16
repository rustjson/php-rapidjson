dnl
dnl $Id$
dnl

PHP_ARG_ENABLE(rapidjson,whether to enable rapidjson support,
[  --enable-rapidjson            Enable rapidjson support])

dnl PHP_ARG_WITH(openssl-dir,OpenSSL dir for php-rapidjson,
dnl [  --with-openssl-dir[=DIR]  rapidjson: openssl install prefix], no, no)

if test "$PHP_RAPIDJSON" = "yes"; then
  dnl AC_DEFINE(HAVE_RAPIDJSON,1,[Whether you want PHP-RAPIDJSON support])
  dnl PHP_NEW_EXTENSION(rapidjson, rapidjson.cpp, $ext_shared)
    PHP_REQUIRE_CXX()
    PHP_SUBST(RAPIDJSON_SHARED_LIBADD)
    PHP_ADD_INCLUDE(rapidjson/include)
    PHP_ADD_LIBRARY(stdc++, 1, RAPIDJSON_SHARED_LIBADD)
    PHP_NEW_EXTENSION(rapidjson, rapidjson.cpp, $ext_shared)
fi
