func ls(array: [Int]) -> (large: Int, small: Int) {
   var lar = array[0]
   var sma = array[0]
   for i in array[1..<array.count] {
      if i < sma {
         sma = i
      }else if i > lar {
         lar = i
      }
   }
   return (lar, sma)
}
let arr = [40,12,-5,78,98]
let num = ls(array: arr)
print("Largest number is: \(num.large) and smallest number is: \(num.small)")
