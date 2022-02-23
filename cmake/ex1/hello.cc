
#include <iostream>
using namespace std;

extern const char * mysql_git_version;
extern const char * mysql_compile_time;
int main(void) {
  cout << mysql_git_version << " " << mysql_compile_time << endl;
  return 0;
}
