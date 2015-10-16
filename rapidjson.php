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

$start_time = microtime(true);
$start_mem =  memory_get_usage(); // 36640

for($i = 0; $i < 1; $i++) {
    //new Rapidjson($json);
//    $json = file_get_contents("status.json");
    $r = new Rapidjson($json);
    //echo $r["has_unread"]."\n";
}

$end_time = microtime(true);
$end_mem =  memory_get_usage();

echo "Rapidjson: " . ($end_time - $start_time)."\n";
echo "Rapidjson: " . ($end_mem - $start_mem)."\n";

/////////////////////////////////////

$start_time = microtime(true);
$start_mem =  memory_get_usage();

for($i = 0; $i < 1; $i++) {
//    $json = file_get_contents("status.json");
    $r = json_decode($json);
}
$end_time = microtime(true);
$end_mem =  memory_get_usage();

echo "json_decode: " . ($end_time - $start_time)."\n";
echo "json_decode: " . ($end_mem - $start_mem)."\n";

//var_dump($r['a']);

?>
