
// shared_ptr::operator= example
#include <iostream>
#include <memory>

class C128 {
  unsigned char buffer[128];
};

int main () {
  C128 * p128 = new (C128);
  int *p1 = new (int);
  int *p2 = new int(10);
  std::shared_ptr<C128> c128(p128);
  std::shared_ptr<int> foo(p1);
  std::shared_ptr<int> bar(p2);

  auto print = [&foo,&bar]{
  std::cout << " &foo: " << &foo
            << " *foo " << *foo
            << " " << foo.use_count()
            << " " << foo.get() << std::endl;
  std::cout << " &bar: " << &bar
            << " *bar: " << *bar
            << " " << bar.use_count()
            << " " << bar.get() << std::endl;
  };

  std::cout << "p128: " << p128 << std::endl;
  std::cout << "p1: " << p1 << std::endl;
  std::cout << "p2: " << p2 << std::endl;
  std::cout << (uint64_t) p1 - (uint64_t) p128 << std::endl;
  std::cout << (uint64_t) p2 - (uint64_t) p1 << std::endl;

  std::cout << "c128: " << c128 << std::endl;
  print();
  std::cout << reinterpret_cast<uint64_t>(foo.get())
            - reinterpret_cast<uint64_t>(c128.get()) << std::endl;

  foo = bar;                          // copy
  print();

  bar = std::make_shared<int> (20);   // move
  print();

  std::unique_ptr<int> unique (new int(30));
  foo = std::move(unique);            // move from unique_ptr
  print();


  return 0;
}
