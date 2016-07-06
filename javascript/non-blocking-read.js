var fs = require("fs");
console.log("===========================");
fs.readFile(__filename, function (err, data) {
    if (err) return console.error(err);
    console.log(data.toString());
});
console.log("Program Ended");
console.log("===========================");
