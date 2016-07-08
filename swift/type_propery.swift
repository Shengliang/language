struct Structname {
   static var storedTypeProperty = "Stored Type Property"
   static var computedTypeProperty: String {
	// return storedTypeProperty.characters.reversed()
	return storedTypeProperty.uppercased()
   }
   var x: Int
}

class Classname {
   static var storedTypeProperty = "Stored Type Property"
   class var computedTypeProperty: String {
	return storedTypeProperty.lowercased()
   }
   var x: Int
   init(x: Int) { self.x = x }
}

class Classname2 {
   static var storedTypeProperty = "Stored Type Property"
   static var computedTypeProperty: String {
	return storedTypeProperty.lowercased()
   }
   var x: Int
   init(x: Int) { self.x = x }
}

var s = Structname(x:3)
var c = Classname(x:3)
print(s.x)
print(c.x)

print(Structname.storedTypeProperty)
print(Structname.computedTypeProperty)
print(Classname.storedTypeProperty)
print(Classname.computedTypeProperty)
print(Classname2.storedTypeProperty)
print(Classname2.computedTypeProperty)

