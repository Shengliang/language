// http://book.mixu.net/node/ch6.html
var Person = function (name, age) { 
    this.name = name; 
    this.age = age; 
    this.privData = ['p', 'r', 'i', 'v'];
    this.print = function () {
       console.log(this.name, this.age, this.sharedData, this.privData);
    };
};
Person.prototype.sharedData = ['s', 'h', 'a', 'r', 'e']; // setting a non-primitive property

var Alice = new Person("Alice", 23);
var Bob = new Person("Bob", 22);
var David = new Person("David", 23);

Alice.sharedData.push('d');

// concat two array in javascript.
Alice.privData.push.apply(Alice.privData, ['i', 'a', 't', 'e']);

var persons = [ Alice, Bob, David ]

persons.sort(function(a,b) {
   if (a.age == b.age) {
       if ( a.name < b.name )
         return -1;
       else if (a.name > b.name)
         return 1;
       else 
         return 0; 
   } else {
     return a.age - b.age;
   }
});

for (i = 0; i< persons.length; i++) {
  persons[i].print();
}
