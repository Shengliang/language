/*
 * Reference: Elements of Programming Interviews
 */
#include<stdio.h>
#include<cstdlib>
#include<iostream>
#include <vector>

// 5.2
#define GetBit(x, i)  (((x) >> i) & 1)
typedef unsigned long long uint64;
uint64 swap_bits(uint64 x, int i, int j) {
   if (GetBit(x, i) != GetBit(x, j)) {
       x ^= ((1LL << i) | (1LL << j));
   }
   return x;
}

// 5.14 x/y = 2^k + (x - 2^k * y) / y
uint64 divide_x_y(uint64 x, uint64 y) {
   if (x < y) {
      return 0;
   }
   int power = 0;
   while ((1LL << power)*y <= x)
      ++power;
   uint64 part = 1LL << (power - 1);
   return part + divide_x_y(x - part * y, y);
}

// 6.2: Design a deterministic scheme by which reads and writes
// to an uninitialized array can be made in O(1) time.
// You may use O(n) additional storage; reads to uninitialed entry 
// should return false.
template <typename ValueType, size_t N>
class Array {
  private:
    ValueType A[N];
    int P[N], S[N], t;
    const bool isValid(size_t i) const {
       return (0 <= P[i] && P[i] < t && S[P[i]] == i);
    }
  public:
     Array() : t(0) { }
     bool read(size_t i, ValueType &v) {
         if (isValid(i)) {
            v = A[i];
            return true;
         }
         return false;
     }
     void write(size_t i, const ValueType &v) {
         if (!isValid(i)) {
             S[t] = i;
             P[i] = t++;
         }  
         A[i] = v;
     }
     void print() {
       std::cout << "P:";
       for(int i = 0; i < N; i++) {
          std::cout << P[i] << " ";
       }
       std::cout << std::endl;
       std::cout << "S:";
       for(int i = 0; i < N; i++) {
          std::cout << S[i] << " ";
       }
       std::cout << std::endl;
       std::cout << "A:";
       for(int i = 0; i < N; i++) {
          std::cout << A[i] << " ";
       }
       std::cout << std::endl;
     }
};

// 6.6: Design and implement an algorithm that takes as input array A of
// n elements, and returns the beginning and ending indices of a logest
// increasing subarray of A.

template <typename T>
std::pair<int, int> find_longest_increasing_subarray(const std::vector<T>& A) {
  std::pair<int, int> ans(0,0);
  int max_len = 1;

  int i = 0; 
  while (i < A.size()) {
     // check backwardly and skip if A[j] >= A[j+1]
     bool is_skippable = false;
     for (int j = i + max_len - 1;  j >= i; --j) {
        if (A[j] >= A[j + 1]) {
           i = j + 1;
           is_skippable = true;
           break;
        }
     }
     // check forwardly if it is not skippable
     if (is_skippable == false) {
        i += max_len - 1;
        while (i + 1 < A.size() && A[i] < A[i+1]) {
          ++i; ++max_len;
        }
        ans = {i - max_len + 1, i};
     }
  }
   
  return ans;
}

int main(void) {
   uint64 x = 0xface0000cafe0000LL;
   uint64 y = swap_bits(x, 3, 59); 
   uint64 z = swap_bits(y, 3, 59); 

   printf("%llX\n%llX\n%llX\n",  x, y, z);
   std::cout << std::hex << x << std::endl; 
   std::cout << std::hex << y << std::endl; 
   std::cout << std::hex << z << std::endl; 

   std::cout << divide_x_y(4097, 2) << std::endl;

   // 6.2: O(1) initialize an array.
   Array<int, 8> arr;
   arr.write(7, 70);   
   arr.write(4, 400);   
   arr.write(5, 500);   
   arr.write(2, 200);   
   arr.write(1, 100);   
   arr.write(0, 20);   
   arr.write(3, 30);   
   arr.write(6, 60);   
   std::cout << std::endl;
   for (int i = 0; i < 8; i++) {
       int v = 0;
       if (arr.read(i, v))
         std::cout << v << " ";
   }
   std::cout << std::endl;
   for (int i = 0; i < 8; i++) {
       arr.write(i, i);   
   }
   for (int i = 0; i < 8; i++) {
       int v = 0;
       if (arr.read(i, v))
         std::cout << v << " ";
   }
   std::cout << std::endl;
   arr.print();

   //                    0  1  2  3  4  5  6  7  8  9 10
   std::vector<int> A = {1, 2, 3, 4, 1, 2, 3, 4, 7, 1, 2};
   auto ans = find_longest_increasing_subarray<int>(A);
   std::cout << ans.first << " " << ans.second << std::endl;
   return 0;
}
