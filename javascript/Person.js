// http://www.phpied.com/3-ways-to-define-a-javascript-class/

function Person(name, age) {
    this.name = name;
    this.age  = age;
    this.print = function () {
       console.log(this.name, this.age);
    };
};

var alice = new Person("Alice", 23);

var persons = [
 new Person("Alice", 23),
 new Person("Bob", 22),
 new Person("David", 23)
];

console.log("===================");
for (i = 0; i< persons.length; i++) {
  persons[i].print();
}

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

console.log("===================");
for (i = 0; i< persons.length; i++) {
  persons[i].print();
}
