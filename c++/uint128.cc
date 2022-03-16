#include <stdio.h>
#include <cstdint>
#include <cinttypes>
#include <iostream> // For hex, internal, [optional] showbase.
#include <type_traits> // For integral_constant, is_same.
#include <string>      // For string.
#include <sstream>     // For stringstream.
#include <iomanip>     // For setfill, setw.
#include <climits>     // For CHAR_BIT.

/*
 * g++ --std=c++14 -fconcepts-ts uint128.cc
 * g++ --std=c++11 uint128.cc
 */

using namespace std;
using U128 = __uint128_t;
using U64 = uint64_t;
using U32 = uint32_t;
using U16 = uint16_t;
using U8 = uint8_t;

namespace detail {
    constexpr int HEX_DIGIT_BITS = 4;
    template<typename T> struct is_char
      : std::integral_constant<bool,
                               std::is_same<T, char>::value ||
                               std::is_same<T, signed char>::value ||
                               std::is_same<T, unsigned char>::value> {};
}

template<typename T>
std::string hex_out_s(T val) {
    using namespace detail;

    std::stringstream out;
    out << std::hex
        << std::internal
        << std::setfill('0')
        << std::setw(sizeof(T) * CHAR_BIT / HEX_DIGIT_BITS)
        << (is_char<T>::value ? static_cast<U16>(val) : val);

    return out.str();
}

std::string hex_out_s(U128 val) {
   std::stringstream out;
   U64* d = (U64*)&val;
   int n = sizeof(U128)/sizeof(d[0]);
   for(int i = n-1; i >= 0; --i) {
     out << hex_out_s(d[i]);
   }
   return out.str();
}

#if __cplusplus >= 201402L
// -fconcepts-ts
void print(auto* d) {
   int n = sizeof(U128)/sizeof(d[0]);
   for(int i = n-1; i >= 0; --i) {
     cout << hex_out_s(d[i]) << " ";
   }
}
void mycopy(auto * dst, auto * src) {
  int n = sizeof(U128)/sizeof(src[0]);
  for(int i = 0; i < n; ++i) {
    dst[i] = src[i];
  }
  print(src);
  print(dst);
}

#else
template<typename T>
void print(T* d) {
   int n = sizeof(U128)/sizeof(d[0]);
   for(int i = n-1; i >= 0; --i) {
     cout << hex_out_s(d[i]) << " ";
   }
}

template<typename T>
void mycopy(T * dst, T * src) {
  int n = sizeof(U128)/sizeof(src[0]);
  for(int i = 0; i < n; ++i) {
    dst[i] = src[i];
  }
  print(src);
  print(dst);
}
#endif


int main(void) {
  U128 d128 = 1;
  U128 arr[128];
  cout << "C++:" << __cplusplus << endl;
  print(&d128);
  cout << endl;
  for (int i = 0; i < 128; ++i) {
    mycopy((U64*)(&arr[i]), (U64*)(&d128));
    mycopy((U32*)(&arr[i]), (U32*)(&d128));
    mycopy((U16*)(&arr[i]), (U16*)(&d128));
    mycopy((U8*)(&arr[i]), (U8*)(&d128));
    cout << endl;
    d128 <<= 1;
  }
  return 0;
}

