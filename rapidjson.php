<?php
$br = (php_sapi_name() == "cli")? "":"<br>";

if(!extension_loaded('rapidjson')) {
	dl('rapidjson.' . PHP_SHLIB_SUFFIX);
}
$module = 'rapidjson';
$functions = get_extension_funcs($module);
echo "Functions available in the test extension:$br\n";
foreach($functions as $func) {
    echo $func."$br\n";
}

/*class obj implements ArrayAccess {
}
$o = new obj();
*/
$json = file_get_contents("status.json");
var_dump(strlen($json));

$times = 1000;

////////////////////////////////////////
$r = new Rapidjson($json);
foreach(json_decode($json, true) as $k => $v) {
    var_dump($k);
    var_dump($r[$k]);
}
exit;


$start_time = microtime(true);
$start_mem =  memory_get_usage(); // 36640

for($i = 0; $i < $times; $i++) {
    $r = new Rapidjson($json);
}

$end_time = microtime(true);
$end_mem =  memory_get_usage();

echo "Rapidjson: " . ($end_time - $start_time)."\n";
echo "Rapidjson: " . ($end_mem - $start_mem)."\n";


/////////////////////////////////////

$start_time = microtime(true);
$start_mem =  memory_get_usage();

for($i = 0; $i < $times; $i++) {
    $r = json_decode($json);
}
$end_time = microtime(true);
$end_mem =  memory_get_usage();

echo "json_decode: " . ($end_time - $start_time)."\n";
echo "json_decode: " . ($end_mem - $start_mem)."\n";


?>
