--TEST--
Check for rapidjson set value
--SKIPIF--
<?php if (!extension_loaded("rapidjson")) print "skip"; ?>
--FILE--
<?php
$str = '{"author":"Jason Young", "age":23}';
$obj = new Rapidjson();
$obj->parse($str);

var_dump($obj['author']);
$obj['author'] = "Yangshengjie";
var_dump($obj['author']);

var_dump($obj['age']);
$obj['age'] = "23";
var_dump($obj['age']);

?>
--EXPECT--
string(11) "Jason Young"
string(12) "Yangshengjie"
int(23)
string(2) "23"

