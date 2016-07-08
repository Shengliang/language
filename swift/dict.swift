
var map:[String:Int] = ["One":1, "Two":2, "Three":3]

// Add entry "Four"
map.updateValue(4, forKey: "Four")

// Add entry "Five"
map["Five"] = 5

// remove entry "Two"
map["Two"] = nil

for (key, value) in map {
   print("\(key) - \(value)")
}

print(map.isEmpty, map.count, map.keys.count)
for (key) in map.keys {
   print("\(key)")
}

for (value) in map.values {
   print("\(value)")
}
