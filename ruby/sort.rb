# Has three strings of different lengths.
values = ["short", "minuscule", "tiny"]

# Sort from shortest to longest.
result = values.sort {|left, right| left.length <=> right.length}
puts result

# http://juixe.com/techknow/index.php/2007/01/22/ruby-class-tutorial/
class Person
  def initialize(name, age)
  @name = name
  @age = age
  end
  attr_accessor :name, :age
  def <=>(other)
     (self.age == other.age) && (self.name <=> other.name) || (self.age <=> other.age)
  end
end

arr = [
  Person.new("Alice", 12),
  Person.new("David", 11),
  Person.new("Bob",   11)
];

# Sort from shortest to longest.
print "=================\n"
arr.each { |a| print a.age, " ", a.name, "\n" }
print "=================\n"
result = arr.sort {|left, right| left <=> right }
result.each { |a| print a.age, " ", a.name, "\n" }
