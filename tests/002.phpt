--TEST--
Check for rapidjson __construct parse
--SKIPIF--
<?php if (!extension_loaded("rapidjson")) print "skip"; ?>
--FILE--
<?php
$str = '{"author":"Jason Young"}';
$obj = new Rapidjson($str);
var_dump($obj['author']);
echo $obj;
?>
--EXPECT--
string(11) "Jason Young"
{
    "author": "Jason Young"
}
