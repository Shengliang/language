#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <string>
using namespace std;

char lookup[26];
void build_map(const string& key) {
    map<char, bool> m;
    vector<string> dic;
    vector<string> dmap;
    string s="";
    for(int i=0; i< key.length(); i++) {
        char ch = key[i];
        if (m.find(ch) == end(m)) {
            m[ch] = true;
            s+=ch;
        }
    }
    dic.push_back(s);
    int len = s.length();
    s = "";
    for(char ch='A'; ch<='Z'; ch++) {
        if (m.find(ch) == end(m) ) {
            s += ch;
        }
        if (s.length() == len) {
            dic.push_back(s);
            s = "";
        }
    }
    if (s.length() >0)  {
        dic.push_back(s);
    }
#ifdef DEBUG
    for(const auto& d: dic) {
        cout << d  << " ";
    }
    cout << endl;
#endif
    
    for(int i=0; i< len; i++) {
        s = "";  
        for(int r=0; r< dic.size(); r++) {
            if (i < dic[r].length()) {
              s += dic[r][i];              
            }
        }
        dmap.push_back(s);
    }
#ifdef DEBUG
    for(const auto& s: dmap) {
        cout << s << " ";
    }
    cout << endl;
#endif

    sort(begin(dmap), end(dmap));

#ifdef DEBUG
    for(const auto& s: dmap) {
        cout << s << " ";
    }
    cout << endl;
#endif

    int i = 0;
    for(const auto& s : dmap) {
       for(auto ch : s) {
          lookup[ch-'A'] = 'A' + i;
          i++;
       }
    }
#ifdef DEBUG
    cout << "DIC:" << endl;
    for (int i = 0; i< 26; i++) {
        char ch = 'A' + i;
        cout << ch << "->" << lookup[i] << endl;
    }
    cout << endl;
#endif
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    string key;
    int num;
    cin >> num;
    for(int i=0; i< num; i++) {
        string line, tmp;
        cin >> key;
        build_map(key);
        getline(cin, tmp); //skip 1st newline.
        getline(cin, line);
        //cout << "[" << key << "]";
        //cout << "[" << line << "]" << endl;
        for(auto ch : line) {
            if (ch>='A' && ch<='Z') {
                int i = ch - 'A'; //0 to 25
                cout << lookup[i];
            } else {
                cout << ch;
            }
        }
        cout << endl;
        
    }
    return 0;
}

