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
echo $obj;
echo "\n";

var_dump($obj['age']);
$obj['age'] = 24;
var_dump($obj['age']);
echo $obj;
echo "\n";

?>
--EXPECT--
string(11) "Jason Young"
string(12) "Yangshengjie"
{"author":"Yangshengjie","age":23}
int(23)
int(24)
{"author":"Yangshengjie","age":24}
