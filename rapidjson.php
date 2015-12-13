<?php

class PHPRapidjson implements ArrayAccess, Iterator {
	public function offsetExists($o) {
	}

	public function offsetGet($o) {

	}
	
	public function offsetSet($o, $v) {

	}
	
	public function offsetUnset($o) {

	}

	public function current() {
	}

	public function key() {
	}

	public function next() {

	}

	public function rewind() {

	}

	public function valid() {
	}
}
new PHPRapidjson();

	try {
		$a = json_decode('{"a":0}');
		var_dump($a);
	} catch(exception $e) {
		var_dump($e);
	}

$json = file_get_contents("test.json");
echo('json.len = '.strlen($json)."\n");

$times = 1000;
var_dump($json);
//$r = new Rapidjson();
$json = '{"city":"beijing", "name":"Jason", "age": 23, "ageStr":"23", "interest": ["computer", 59]}';
$r = new Rapidjson();
$r->parse($json);
$r["name"] = "OK";
var_dump($r['name']);
var_dump($r['city']);
var_dump($r['age']);
var_dump($r['ageStr']);
var_dump($r['interest']);
$r["interest"] = 'a';
var_dump($r['interest']);

$r["interest"] = null;
echo $r;

unset($r["interest"]);
echo $r;

exit;
////////////////////////////////////////

$start_time = microtime(true);
$start_mem =  memory_get_usage();

for($i = 0; $i < $times; $i++) {
    $r = new Rapidjson($json);
}

$end_time = microtime(true);
$end_mem =  memory_get_usage();

echo "Rapidjson.time: " . ($end_time - $start_time)."\n";
echo "Rapidjson.mem: " . ($end_mem - $start_mem)."\n";


/////////////////////////////////////

$start_time = microtime(true);
$start_mem =  memory_get_usage();

for($i = 0; $i < $times; $i++) {
    $r = json_decode($json);
}
$end_time = microtime(true);
$end_mem =  memory_get_usage();

echo "json_decode.time: " . ($end_time - $start_time)."\n";
echo "json_decode.mem: " . ($end_mem - $start_mem)."\n";


?>
