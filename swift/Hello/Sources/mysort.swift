
func arr_print(names: [String]) {
  for name in names {
    print("\(name) ")
  }
  print("\n")
} 
var names =  ["Chris", "Alex", "Ewa", "Barry", "Daniella"]

func backward(_ s1: String, _ s2: String) -> Bool {
  return s1 > s2
}
var reversed = names.sorted(isOrderedBefore: backward)
arr_print(names: names)

reversed = names.sorted(isOrderedBefore: { (s1: String, s2: String) -> Bool in
    return s1 > s2
})
arr_print(names: names)

reversed = names.sorted(isOrderedBefore:  { (s1: String, s2: String) -> Bool in return s1 > s2 } )
arr_print(names: names)

// Interring Type from context
reversed = names.sorted(isOrderedBefore:  { s1, s2 in return s1 > s2 } )
arr_print(names: names)

// Implicit returns from single-expression closures
reversed = names.sorted(isOrderedBefore:  { s1, s2 in s1 > s2 } )
arr_print(names: names)

// Shorthand 
reversed = names.sorted(isOrderedBefore:  { $0 > $1 } )
arr_print(names: names)

// Operator Functions
reversed = names.sorted(isOrderedBefore: >)
arr_print(names: names)
