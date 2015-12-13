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



$json = '{"boy": true, "name":"hello", "city": "beijing", "int":0, "arr":[1,3], "obj":{"ab":"cd"}}';

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
//echo $r;

unset($r["interest"]);
//echo $r;

foreach ($r as $k => $v) {
	echo 'key = '. $k .', val = ';var_dump($v);
}

//exit;
