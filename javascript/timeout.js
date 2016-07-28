var waitTime = 3000;
var currTime = 0;
var waitInterval = 500;
var percentWaited = 0;

function waiting(percent) {
  process.stdout.clearLine();
  process.stdout.cursorTo(0);
  process.stdout.write(`waiting .. ${percent}`);
}

// Now call the function after waitInterval seconds
var interval = setInterval(function() {
   currTime += waitInterval;
   percentWaited = Math.floor((currTime/waitTime)*100);
   waiting(percentWaited);
}, waitInterval);

// Now call the function after waitTime.
var t = setTimeout(function(){
   clearInterval(interval);
   waiting(100);
   console.log( "done");
}, waitTime);

process.stdout.write("\n\n");
waiting(percentWaited);
