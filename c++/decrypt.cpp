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

int main() {
    // cipher message
    vector<string> cmsg;

    // map word count to a list word lengths with the same word count.
    map<int, vector<int>> wdcnt2len_map;
    
    // Map word len to a list of dictionary words with the same length.
    map<int, vector<string>,  comp_func> wdlen_map(comp);

    // Map word len to a list of message words with the same length.
    map<int, vector<string>, comp_func> cmsg_wdlen_map(comp);

    ifstream fin;
    string dic_filename = "dictionary.lst";
    fin.open (dic_filename, ifstream::in);
    if (!fin.good()) {
      cout << "Cannot open " << dic_filename << endl;
      return 0;
    }
    string wd;
    while (fin >> wd) {
      auto wlen = wd.length();
      wdlen_map[wlen].push_back(wd);
    }
    fin.close();

    while (cin >> wd) {
        cmsg.push_back(wd);
        cmsg_wdlen_map[wd.length()].push_back(wd);
    }
    for(const auto& e : wdlen_map) {
       const auto& vec = e.second;
       wdcnt2len_map[vec.size()].push_back(e.first);
    }

    map<char, char> key_map; 
    for(const auto& e : cmsg_wdlen_map) {
       const auto& vec = e.second;
       for(const auto& wd : vec) {

          const auto & dic_wds = wdlen_map[e.first];
          for(const auto & dic_wd : dic_wds) {
              unordered_map<char, int> ha;
              ha[wd[0]] = 0; 
              string sa = wd;
              if (key_map.find(wd[0]) != end(key_map)) {
                sa[0] = key_map[wd[0]];
              } else {
                sa[0] = dic_wd[0];
              }
              for(int i=1; i< e.first; i++) {

                 if (ha.find(wd[i]) != end(ha)) {
                    sa[i] = sa[ ha[wd[i]] ]; 
                 } else {
                    ha[wd[i]] = i;
                    if (key_map.find(wd[i]) != end(key_map)) {
                       sa[i] = key_map[wd[i]];
                    } else {
                       sa[i] = dic_wd[i];
                    }
                 } 
              }
              if ( sa == dic_wd ) {
                   for(int i = 0; i< e.first; i++) {
                      key_map[wd[i]] = dic_wd[i];
                   }
                   // cout << key_map.size() << " " << wd << " --> " << dic_wd << endl;
                   break;
              }
          } 
       }
    }
    // cout << endl;
    int i = 0;
    for(const auto& m: cmsg) {
        for(auto ch : m) {
          if (key_map.find(ch) != end(key_map)) {
            cout << key_map[ch];
          } else {
            cout << ".";
          }
        }
        if (++i != cmsg.size()) {
            cout << " ";
        }
    }
    cout << endl;
    return 0;
}
