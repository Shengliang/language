/*
 * g++ -std=c++11 c11.cpp
 */
#include<vector>
#include<iostream>
#include<string>
#define WHERE2(msg) std::cout << __FUNCTION__ << ":" << __LINE__ << ":" << msg << " " << this << " " << &other << std::endl;
#define WHERE(msg) std::cout << __FUNCTION__ << ":" << __LINE__ << ":" << msg << " " << this << std::endl;

const char * cmsg = R"delimiter(
  string_literal
  http://en.cppreference.com/w/cpp/language/string_literal
  g++ -std=c++11 c11.cpp
)delimiter";

class N {
 public:
  std::string s_;
  N() : s_("") { WHERE("(void)"); }
  N(const std::string & s) : s_(s) { WHERE("string&"); }
  ~N() { s_=""; WHERE("~N"); }

  // N& operator= (const N & other) { WHERE2("=N&"); s_ = other.s_; return *this; }
  N& operator= (const N & other) = delete;

  N(const N & other) { WHERE2("N&"); s_ = other.s_; }


  N(N && other) noexcept : s_(std::move(other.s_)) { WHERE2("N&&") }

  N& operator= (N && other) noexcept  { s_ = std::move(other.s_); WHERE2("=N&&"); return *this; }
  N& operator= (const N && other) noexcept  { s_ = std::move(other.s_); WHERE2("=N&&"); return *this; }
  N& operator= (std::string && other) noexcept  { s_ = std::move(other);  WHERE2("=string&&"); return *this; }
  N& operator= (const std::string && other) noexcept  { s_ = std::move(other);  WHERE2("=string&&"); return *this; }

  operator std::string() { WHERE("strign()"); return s_; }
  friend std::ostream& operator<<(std::ostream& out, const N & n) {
      return out << &n << " " << n.s_;
  }
};
int main(void)
{
  N n1, n2;
  std::cout << cmsg << std::endl;
  const N n3("const_n3");
  std::string me = "me";
  std::string you = "you";
  const std::string c1("c1");
  std::string s1, s2;
  s1 = me;
  s2 = you;

  std::cout << "s1: " << s1 << " " << std::hex << reinterpret_cast<uint64_t>(s1.c_str()) << std::endl;
  std::cout << "s2: " << s2 << " " << std::hex << reinterpret_cast<uint64_t>(s2.c_str()) <<  std::endl;
  std::swap(s1,s2);

  std::cout << "s1: " << s1 << " " << std::hex << reinterpret_cast<uint64_t>(s1.c_str()) << std::endl;
  std::cout << "s2: " << s2 << " " << std::hex << reinterpret_cast<uint64_t>(s2.c_str()) <<  std::endl;
  s1 = std::move(s2);
  std::cout << "s1: " << s1 << " " << std::hex << reinterpret_cast<uint64_t>(s1.c_str()) << std::endl;
  std::cout << "s2: " << s2 << " " << std::hex << reinterpret_cast<uint64_t>(s2.c_str()) <<  std::endl;
  std::cout << "c1: " << c1 << " " << std::hex << reinterpret_cast<uint64_t>(c1.c_str()) << std::endl;
  s1 = std::move(c1);
  std::cout << "c1: " << c1 << " " << std::hex << reinterpret_cast<uint64_t>(c1.c_str()) << std::endl;
  std::cout << "s1: " << s1 << " " << std::hex << reinterpret_cast<uint64_t>(s1.c_str()) << std::endl;

  std::cout << "===========================" << std::endl;
  n1 = me;
  n2 = you;
  std::cout << "===========================" << std::endl;
  std::cout << n1 << std::endl;
  std::cout << n2 << std::endl;

  n1 = std::move(n2);
  std::cout << n1 << std::endl;
  std::cout << n2 << std::endl;
  std::cout << "===========================" << std::endl;
  std::cout << n1 << std::endl;
  std::cout << n3 << std::endl;
  n1 = std::move(n3);
  std::cout << n1 << std::endl;
  std::cout << n3 << std::endl;
  std::cout << "===========================" << std::endl;

  std::vector<int> vec;
  vec.push_back(10);
  vec.push_back(20);
  for(auto & i  : vec) {
    std::cout << i << std::endl;
  }

   char s[]="Hello World!";
   int Uppercase = 0; //modified by the lambda
   auto f_isupper = [](char ch) -> bool {
     return isupper(ch);
   };
   for(auto & ch: s) {
    if (f_isupper(ch))
     Uppercase++;
   }
   std::cout<< Uppercase<<" uppercase letters in: " << s <<std::endl;

   return 0;
}
