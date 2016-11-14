#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;


void f(string & s) {

  int len =s.length();
  int c=1; 
  string a = s.substr (0,1);

  for(int i=1; i<len;) {
      bool fd=false;
      int l=min(a.length(), size_t(len-i));
 
      for(; l>=1; l--) {
          string t = s.substr(i,l);
          auto found = a.find(t);
          //cout << "try: " << t << endl;
          if (found!=std::string::npos)  {

              i+=l;
              a+=t;
              //cout << "found " << t << " " << i << " " << l << endl;
              fd = true;
              break;
          }

      }
      if (fd==false) {
          string t=s.substr(i,1);
          a+=t;
          c++;    
          i++;
      }

  }
  cout << c << endl;
}
int main(){
    int n;
    cin >> n;

    for(int a0 = 0; a0 < n; a0++){
        string s;
        cin >> s;
        f(s);
    }
    return 0;
}

