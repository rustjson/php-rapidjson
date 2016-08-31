# php-rapidjson

[![Build Status](https://travis-ci.org/RustJason/php-rapidjson.png?branch=master)](https://travis-ci.org/RustJason/php-rapidjson)

PHP Extension of rapidjson (not finished yet)

# Requirement

 PHP7

# Install

```sh
git clone --recursive https://github.com/RustJason/php-rapidjson
cd php-rapidjson

phpize

./configure --with-php-config=/usr/local/php/php-7.0.0/bin/php-config

make && make test

```

# Usage

```php

$json = '{"name": "Jason", "age": 23, "arr":["c", "e"], "obj":{"subobj"}}';

$obj = new Rapidjson($json);

//traversal
foreach($obj as $k => $v) {
	echo "key = $k";
	var_dump($v);
}

//modify and reencode
$obj['name'] = 'Young';
var_dump($obj['name']);
echo $obj;


//ongoing 
//Array support and obj support

```


#Result of benchmark(gcc -O3) [Script](https://github.com/RustJason/php-rapidjson/blob/master/benchmark.php):
```bash
json.len = 206082
string(6) "memeda"
newjson.len = 202313
Rapidjson.time: 2.2114210128784
Rapidjson.mem: 204912
string(6) "memeda"
newjson.len = 218756
json_decode.time: 15.593321800232
json_decode.mem: 1543856
```


