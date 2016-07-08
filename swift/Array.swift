
var arr = [Int]()

arr.append(1)
arr.append(2)
arr += [3]

for n in arr {
  print(n)
}

var intsA = [Int](repeating:42, count:2)
var intsB = [Int](repeating:7, count:3)

var intsC = intsA + intsB
var nilC = [Int]()

print(intsC.count)
print(intsC.isEmpty)
print(nilC.isEmpty)
for item in intsC {
   print(item)
}

let items = ["A", "B", "C", "D"]
for i in (0..<items.count) {
   print("\(i): \(items[i])")
}
for i in stride(from:0, to:items.count, by:2) {
   print("\(i): \(items[i])")
}
for i in (0..<items.count) where i % 2 == 0 {
   print("\(i): \(items[i])")
}
for i in (0..<items.count).reversed() {
   print("\(i): \(items[i])")
}
for (i, item) in items.enumerated() {
   print("\(i): \(item)")
}
