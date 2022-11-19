
// string constructor
#include <iostream>
#include <map>
#include <string>

struct A {
  char ch; // 1
  char *d[0];
};

struct P {
  const char *name;
  uint64_t *addr;
};

#define E(addr)                                                                \
  { (uint64_t *)addr, #addr }

void firstfunction();
void second_function();
int main();
void third_function();

void first_function() {
  A a;
  A b;
  std::multimap<uint64_t *, const char *> mp = {E(a.d),
                                                E(&a.d),
                                                E(b.d),
                                                E(&b.d),
                                                E(&a.ch),
                                                E(&b.ch),
                                                E(third_function),
                                                E(main),
                                                E(second_function),
                                                E(&second_function),
                                                E(first_function)};
  std::cout << "sizeof(A):" << sizeof(A) << std::endl;
  for (auto it = mp.rbegin(); it != mp.rend(); it++) {
    auto &e = *it;
    std::cout << e.first << "\t\t" << e.second << std::endl;
  }
}
void second_function() { first_function(); }

int main() {
  third_function();
  return 0;
}

void third_function() { second_function(); }
/*
sizeof(A):8
0x7ffe4ce8bb20		a.d
0x7ffe4ce8bb20		&a.d
0x7ffe4ce8bb18		b.d
0x7ffe4ce8bb18		&b.d
0x7ffe4ce8bb18		&a.ch
0x7ffe4ce8bb10		&b.ch
0x400fd3		third_function
0x400fc3		main
0x400fb7		second_function
0x400fb7		&second_function
0x400ba2		first_function
 */
