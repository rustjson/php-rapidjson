--TEST--
Check for rapidjson set value
--SKIPIF--
<?php if (!extension_loaded("rapidjson")) print "skip"; ?>
--FILE--
<?php

$str = '{"boy": true, "name":"hello", "city": "beijing", "int":0, "arr":[1,3], "obj":{"ab":"cd"}, "null": null}';
$obj = new Rapidjson();
$obj->parse($str);

foreach ($obj as $key => $val) {
	echo "key = $key, val = ";
	var_dump($val);
}
?>
--EXPECT--
key = boy, val = bool(true)
key = name, val = string(5) "hello"
key = city, val = string(7) "beijing"
key = int, val = int(0)
key = arr, val = NULL
key = obj, val = NULL
key = null, val = NULL
