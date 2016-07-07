<?php
function writeMsg() {
    echo "Hello world!\n";
}

writeMsg(); // call the function

function sum($x, $y=0) {
    $z = $x + $y;
    return $z;
}

echo "5 + 10 = " . sum(5, 10) . "<br>\n";
echo "7 + 13 = " . sum(7, 13) . "<br>\n";
echo "2 + 4 = " . sum(2, 4) . "<br>\n";
echo "2 + 0 = " . sum(2) . "<br>\n";
?>

