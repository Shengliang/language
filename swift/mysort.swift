
func arr_print(names: [String]) {
  for name in names {
    print("\(name) ")
  }
  print("\n")
} 

func backward(_ s1: String, _ s2: String) -> Bool {
  return s1 > s2
}

func sort_test() {
  let names =  ["Chris", "Alex", "Ewa", "Barry", "Daniella"]
  arr_print(names: names)
  var reversed = names.sorted(isOrderedBefore: backward)
  arr_print(names: reversed)
  reversed = names.sorted(isOrderedBefore: { (s1: String, s2: String) -> Bool in
      return s1 > s2
  })
  arr_print(names: reversed)
  
  reversed = names.sorted(isOrderedBefore:  { (s1: String, s2: String) -> Bool in return s1 > s2 } )
  arr_print(names: reversed)
  
  // Interring Type from context
  reversed = names.sorted(isOrderedBefore:  { s1, s2 in return s1 > s2 } )
  arr_print(names: reversed)
  
  // Implicit returns from single-expression closures
  reversed = names.sorted(isOrderedBefore:  { s1, s2 in s1 > s2 } )
  arr_print(names: reversed)
  
  // Shorthand 
  reversed = names.sorted(isOrderedBefore:  { $0 > $1 } )
  arr_print(names: reversed)
  
  // Operator Functions
  reversed = names.sorted(isOrderedBefore: >)
  arr_print(names: reversed)
}
