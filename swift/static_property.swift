// ref: http://stackoverflow.com/questions/26567480/static-properties-in-swift
class SomeClass {
    struct S {
        static var items = [String]()
    }
    class var items: [String] {
       get { return S.items }
       set { S.items = newValue }
    }
    // same as above
    static var Items: [String] {
       get { return S.items }
       set { S.items = newValue }
    }
}

SomeClass.S.items.append("1")
SomeClass.S.items.append("2")
print(SomeClass.S.items)
SomeClass.items.append("3")
SomeClass.Items.append("4")
print(SomeClass.items)
