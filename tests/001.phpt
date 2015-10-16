--TEST--
Check for rapidjson get value
--SKIPIF--
<?php if (!extension_loaded("rapidjson")) print "skip"; ?>
--FILE--
<?php
$str = '{"author":"Jason Young"}';
$obj = new Rapidjson($str);
var_dump($obj['author']);
?>
--EXPECT--
string(11) "Jason Young"
