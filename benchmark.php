<?php

$json = file_get_contents("test.json");
echo('json.len = '.strlen($json)."\n");

////////////////////////////////////////

$times = 1000;
$start_time = microtime(true);
$start_mem =  memory_get_usage();

/*$r = new Rapidjson($json);
foreach ($r as $k => $v) {
	echo $k."\n";
}
*/

for($i = 0; $i < $times; $i++) {
    $r = new Rapidjson($json);
	$r['gsid'] = 'memeda';
	$newjson = $r->__toString();
}
var_dump($r['gsid']);
file_put_contents("rapidjson.json", $newjson);
echo('newjson.len = '.strlen($newjson)."\n");

$end_time = microtime(true);
$end_mem =  memory_get_usage();

echo "Rapidjson.time: " . ($end_time - $start_time)."\n";
echo "Rapidjson.mem: " . ($end_mem - $start_mem)."\n";


/////////////////////////////////////

$start_time = microtime(true);
$start_mem =  memory_get_usage();
$newjson = "";
for($i = 0; $i < $times; $i++) {
    $r = json_decode($json);
	$r->gsid = 'memeda';
	$newjson = json_encode($r);
}
var_dump($r->gsid);
file_put_contents("json_decode.json", $newjson);

echo('newjson.len = '.strlen($newjson)."\n");


$end_time = microtime(true);
$end_mem =  memory_get_usage();

echo "json_decode.time: " . ($end_time - $start_time)."\n";
echo "json_decode.mem: " . ($end_mem - $start_mem)."\n";


?>
