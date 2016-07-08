if Process.arguments.count != 3 {
  print("Usage: hello [name1] [name2]")
} else {
  print("Arguments:");
  for arg in Process.arguments {
    print("\(arg)")
  }

  let name1 = Process.arguments[1]
  let name2 = Process.arguments[2]
  print("\n");
  print(sayHello(to: name1, and: name2))

}
