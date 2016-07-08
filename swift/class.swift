class SampleClass: Equatable {
   let myProperty: String
   init(s: String) {
      myProperty = s
   }
}
func ==(lhs: SampleClass, rhs: SampleClass) -> Bool {
   return lhs.myProperty == rhs.myProperty
}

let spClass1 = SampleClass(s: "Hello")
let spClass2 = SampleClass(s: "Hello")

print(spClass1 === spClass2) // false
print("\(spClass1)")

print(spClass1 !== spClass2) // true
print("\(spClass2)")
