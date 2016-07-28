// Ref: Lynda.com node-js-essential-training

function grab(flag) {
  var idx = process.argv.indexOf(flag);
  return (idx===-1) ? null : process.argv[idx+1];
}

var greeting = grab('--greeting');
var user = grab('--user');

var questions=[
 "What is your name?",
 "What is your programming language?",
];
var ans=[];

function ask(i) {
   process.stdout.write(`\n${questions[i]}`);
   process.stdout.write(": ");
}

process.stdin.on('data', function(data) {
  ans.push(data.toString().trim());
  if (ans.length < questions.length) {
     ask(ans.length);
  }else {
     process.exit();
  }
});


process.on('exit', function() {
  process.stdout.write("\n------------");
  for (i = 0; i< ans.length; i++) {
     process.stdout.write(`\n${questions[i]}: ${ans[i]}`);
  }
  process.stdout.write("\n------------\n");
 
});

if (!user || !greeting) {
  process.stdout.write("stdout write\n");
  console.log(process.argv[0] + " --greeting msg --user user"); 
}
else {
  process.stdout.write(`Welcome ${user}, ${greeting} `); 
  ask(0);
}
