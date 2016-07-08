class sample {
   lazy var no = number() // `var` declaration is required.
}

class number {
   var name = "Swift"
}

var firstsample = sample()
print(firstsample.no.name)
