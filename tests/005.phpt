--TEST--
Check for rapidjson object suppoet
--SKIPIF--
<?php if (!extension_loaded("rapidjson")) print "skip"; ?>
--FILE--
<?php

$str = '{"subobj":{"name":"george"}}';
$obj = new Rapidjson();
$obj->parse($str);

var_dump($obj);
var_dump($obj['subobj']);
var_dump($obj['subobj']['name']);
?>
--EXPECT--
object(Rapidjson)#1 (2) {
  ["obj":protected]=>
  UNKNOWN:0
  ["ost":protected]=>
  int(0)
}
object(Rapidjson)#2 (2) {
  ["obj":protected]=>
  UNKNOWN:0
  ["ost":protected]=>
  int(0)
}
string(6) "george"

