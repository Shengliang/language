
#include "TutorialConfig.h"
#include <iostream>
using namespace std;

extern const char * mysql_git_version;
extern const char * mysql_compile_time;
int main(int argc, char*argv[]) {
   if (argc < 2) {
    std::cout << argv[0] << " Version " << Tutorial_VERSION_MAJOR << "."
              << Tutorial_VERSION_MINOR << std::endl;
    std::cout << "Usage: " << argv[0] << " number" << std::endl;
    return 1;
  }
  cout << mysql_git_version << " " << mysql_compile_time << endl;
  return 0;
}
