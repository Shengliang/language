<?php
function myprint($age) {
  echo "\n-----------------\n";
  foreach($age as $k => $v) {
     echo "Key=" . $k . ", Value=" . $v;
     echo "<br>\n";
  }
}
$age = array("Peter"=>"35", "Ben"=>"37", "Joe"=>"43");
asort($age);
myprint($age);
ksort($age);
myprint($age);
?>

