if Process.arguments.count != 3 {
  print("Usage: hello [name1] [name2]")
} else {
  let name1 = Process.arguments[1]
  let name2 = Process.arguments[2]
  print(sayHello(to: name1, and: name2))
}
