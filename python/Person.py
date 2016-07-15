
class Person:
    def __init__(self,name,age):
        self.name=name
        self.age=age

    def __lt__(self,other):
        return (self.age == other.age) and (self.name < other.name) or (self.age < other.age)


persons=[ Person("Alice", 31),  Person("Bob", 12), Person("David", 31) ]
results=sorted(persons);
for p in persons:
  print p.age, " ", p.name
for p in results:
  print p.age, " ", p.name
