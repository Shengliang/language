#include<cstdio>
#include<iostream>
#include<vector>
#include<stdint.h>

using namespace std;
uint64_t mask = (((uint64_t)-1ULL));

struct P {
  int64_t x = 0LL;
  int64_t y = 0LL;
  P() : x(0), y(0) { }
  P(int64_t _x, uint64_t _y) : x(_x), y(_y) { }
};

int main(void) {
 vector<P>  vec;
 cout << (vec.begin() == vec.end()) << " " << vec.size() << endl;
 vector<P>  points(10);
 cout << points[0].x << " " << points[0].y << endl;
 points[0] =  P(1, 2);
 cout << points[0].x << " " << points[0].y << endl;
 cout << hex << mask << endl;
 std::vector<P>::iterator it = points.begin();
 if (it != points.end()) {
 cout << it->x << " " << it->y << " " << sizeof(it) << " " << sizeof(unsigned long) <<  endl;
    unsigned long lx = *((unsigned long*) &it);
    const std::vector<P>::iterator& iit = *((const std::vector<P>::iterator*) &lx);
    cout << hex << lx << " " << iit->x << " " << iit->y << endl;

 }


 return 0;
}
