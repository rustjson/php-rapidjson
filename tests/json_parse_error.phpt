--TEST--
Check that an exception is thrown when JSON string cannot be parsed.
--SKIPIF--
<?php if (!extension_loaded("rapidjson")) print "skip"; ?>
--FILE--
<?php

$str = 'invalid json';
$obj = new Rapidjson();
try {
    $obj->parse($str);
} catch (Exception $exception) {
    var_dump($exception->getMessage());
}

?>
--EXPECT--
string(16) "JSON Parse Error"
