// concat buffer
var buffer1 = new Buffer('TutorialsPoint ');
var buffer2 = new Buffer('Simply Easy Learning');
var buffer3 = Buffer.concat([buffer1,buffer2]);
console.log("buffer3 content: " + buffer3.toString());

// compare buffer
var buffer1 = new Buffer('ABC');
var buffer2 = new Buffer('ABCD');
var result = buffer1.compare(buffer2);

if(result < 0) {
   console.log(buffer1 +" comes before " + buffer2);
}else if(result == 0){
   console.log(buffer1 +" is same as " + buffer2);
}else {
   console.log(buffer1 +" comes after " + buffer2);
}

// copy a buffer
var buffer1 = new Buffer('ABC');
var buffer2 = new Buffer(3);
buffer1.copy(buffer2);
console.log("buffer2 content: " + buffer2.toString());


// slicing a buffer
var buffer1 = new Buffer('TutorialsPoint');
var buffer2 = buffer1.slice(0,9);
console.log("buffer2 content: " + buffer2.toString());

// length of the buffer
var buffer = new Buffer('TutorialsPoint');
console.log("buffer length: " + buffer.length);
