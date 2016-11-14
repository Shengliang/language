#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>  
#include <unordered_map>
#include <map>
#include <string>

using namespace std;

bool comp(int x, int y) {
   return x > y;
}
typedef bool (*comp_func)(int x, int y);
bool mysort (string a, string b) { return a.length() > b.length(); }

    // map word count to a list word lengths with the same word count.
    map<int, vector<int>> wdcnt2len_map;
    
    // Map word len to a list of dictionary words with the same length.
    map<int, vector<string>,  comp_func> wdlen_map(comp);

    // Map word len to a list of message words with the same length.
    map<int, vector<string>, comp_func> msg_wdlen_map(comp);
    map<int, vector<string>, comp_func> cmsg_wdlen_map(comp);
    
    unordered_map<string, bool> dic;
    vector<string> dicvec;
    vector<string> msg;
    vector<string> msgsort;

int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    ifstream fin;
    string dic_filename = "dictionary.lst";
    fin.open (dic_filename, ifstream::in);
    if (!fin.good()) {
      cout << "Cannot open " << dic_filename << endl;
      return 0;
    }
    string wd;
    while (fin >> wd) {
      dic[wd] = true;
      dicvec.push_back(wd);
      auto wlen = wd.length();
      wdlen_map[wlen].push_back(wd);
    }
    fin.close();

    string out_file = "c.txt";
    fin.open (out_file, ifstream::in);
    while (fin >> wd) {
       cmsg_wdlen_map[wd.length()].push_back(wd); 
    }
    fin.close();

    while (cin >> wd) {
        msg.push_back(wd);
        msgsort.push_back(wd);
        msg_wdlen_map[wd.length()].push_back(wd);
    }
    sort (begin(msgsort), end(msgsort),  mysort);
    sort (begin(dicvec), end(dicvec),  mysort);
    for(const auto& e : wdlen_map) {
       const auto& vec = e.second;
       wdcnt2len_map[vec.size()].push_back(e.first);
    }

    for(const auto& m: msgsort) {
        cout << m << " ";
    }
    cout << endl;
    for(const auto& e : wdcnt2len_map) {
       cout << e.first << ":";
       const auto& vec = e.second;
       for(const auto& len : vec) {
          cout << len << " ";
       }
       cout << endl;
    }
    cout << endl;
    for(const auto& e : wdlen_map) {
       cout << e.first << ":";
       const auto& vec = e.second;
       for(const auto& wd : vec) {
          cout << wd << " ";
       }
       cout << endl;
    }
    cout << endl;
    cout << "Found mapping..." << endl;
    for(const auto& e : cmsg_wdlen_map) {
       const auto& vec = e.second;
       for(const auto& wd : vec) {
          const auto & dic_wds = wdlen_map[e.first];
          for(const auto & dic_wd : dic_wds) {
              string a = wd;
              string b = dic_wd;
              a[0] = 'a';
              b[0] = 'a';
              for(int i=1; i< e.first; i++) {
                 if (wd[i] == wd[i-1]) {
                    a[i] = a[i-1]; 
                 } else {
                    a[i] = 'a' + i;
                 } 
                 if (dic_wd[i] == dic_wd[i-1]) {
                    b[i] = b[i-1]; 
                 } else {
                    b[i] = 'a' + i;
                 } 
              }
              if ( a == b ) {
                   cout << a << " " << b << " " << wd << " --> " << dic_wd << endl;
                   break;
              }
          } 
       }
       cout << endl;
    }
    cout << endl;
    for(const auto& e : cmsg_wdlen_map) {
       cout << e.first << ":";
       const auto& vec = e.second;
       for(const auto& wd : vec) {
          cout << wd << " ";
       }
       cout << endl;
    }
    cout << endl;
    return 0;
}
