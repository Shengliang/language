function timeout_printHello(){
   console.log( "Timeout:Hello, World!");
}
function repeat_printHello(){
   console.log( "Hello, World!");
}
// Now call above function after 2 seconds
var t = setTimeout(timeout_printHello, 2000);

// Now call above function after 2 seconds
setInterval(repeat_printHello, 1000);

// Now clear the timer
clearTimeout(t);
