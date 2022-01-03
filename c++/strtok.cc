#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>
#include <iostream>
using namespace std;
vector<string> split(const string& s, const string& delimiters = "/")
{
  char str[s.length()+1];
  strncpy(str, s.c_str(), s.length()+1);

  char* token;
  char* rest = str;
  vector<string> ans;
  cout << str << endl;
  while ((token = strtok_r(rest, delimiters.c_str(), &rest)))
    ans.push_back(string(token));
  return ans;

}
int main()
{
  /* Split based on ',', '|', or spacce */
  char str[] = " 1,2, 3, 4 ,5,6  |  ,,, ,   7 ,   ,   8|9,";
  char* token;
  char* rest = str;
  printf("%p[%s]\n", str, str);
  while ((token = strtok_r(rest, ", |", &rest)))
    printf("%p[%s]\n", token, token);
  printf("%p[%s]\n", str, str);

  {
    string s  = " 1,2, 3, 4 ,5,6  |  ,,, ,   7 ,   ,   8|9,";
    auto ans = split(s, ", |");
    for(auto & s: ans) cout << s << endl;
  }
  {
    string s  = "/a/b/c/d/e//f1.txt";
    auto ans = split(s, "/");
    for(auto & s: ans) cout << "[" << s << "]" << endl;
  }
  return (0);
}


