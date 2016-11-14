#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
// Based on hints from discussion.
// Even N => 0 Odd N => XOR of elements at position 0,2,4,..... 
void test(void) {
   int N; 
   cin >> N;
   int arr[N];
   int odd = 0;
   for(int i=0; i<N; i++) {
        cin >> arr[i];
        if((i&1)==0) odd ^= arr[i];
   }
   // is event.
   if ((N&1) == 0) {
      cout << "0" << endl;
   }
   else {
      cout << odd << endl;
   }
   return;
}
    

int main() {
    int num_test;
    cin >> num_test;
    for(int i  = 0; i< num_test; i++) {
      test();
    }
    return 0;
}

