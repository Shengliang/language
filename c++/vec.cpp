#include<cstdio>
#include<iostream>
#include<vector>
#include<stdint.h>

using namespace std;

struct P {
  int64_t x = 0LL;
  int64_t y = 0LL;
  P() : x(0), y(0) { }
  P(int64_t _x, uint64_t _y) : x(_x), y(_y) { }
};

int main(void) {
 vector<P>  points(10);
 cout << points[0].x << " " << points[0].y << endl;
 points[0] =  P(1, 2);
 cout << points[0].x << " " << points[0].y << endl;
 return 0;
}
