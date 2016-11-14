#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

int main() {
   double d, c; int tip, tax;
   cin >> d >> tip >> tax;
   c = d;
   c += d*tip/100;
   c += d*tax/100;
   cout << "The total meal cost is " << fixed << setprecision(0) << c << " dollars." << endl;
   return 0;
}
