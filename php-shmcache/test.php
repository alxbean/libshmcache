<?php

$key = 'key_0001';
$value = array('name' => 'yuqing', 'score' => 90.5, 'city' => 'beijing', 'gender' => 'male');
$value = json_encode($value, JSON_PRETTY_PRINT);

$cache = new ShmCache('../conf/libshmcache.conf', ShmCache::SERIALIZER_NONE);
$cache->set($key, $value, 300);
for ($i=0; $i<1024; $i++) {
    //$cache->set($key, $value, 300);
    $v = $cache->get($key);
}
$key1 = 'key_00002';
var_dump($cache->incr($key1, -1, 300));
var_dump($cache->get($key));
var_dump($cache->delete($key));

//var_dump($cache->stats());
echo json_encode($cache->stats(), JSON_PRETTY_PRINT);
