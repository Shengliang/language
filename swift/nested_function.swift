// Constants and variable references defined inside the functions 
// are captured and stored in closures.
func calcDecrement(forDecrement total: Int) -> () -> Int {
   var overallDecrement = 100
   func decrementer() -> Int {
      overallDecrement -= total
      return overallDecrement
   }
   return decrementer
}
let decrem = calcDecrement(forDecrement: 30)
let y = calcDecrement(forDecrement: 2)
for var i in (0..<3) {
  print(decrem())
  print(y())
}
