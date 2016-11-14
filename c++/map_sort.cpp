// http://stackoverflow.com/questions/15588428/how-to-declare-custom-sort-function-on-stdmap-declaration
#include<map>
#include<vector>
#include<string>
#include<iostream>

using namespace std;

bool comp(int x , int y)
{
    return  __builtin_popcount(x) <  __builtin_popcount(y);
}
typedef bool (*comp_func)(int x, int y);

int main(){
    map<int, vector<string>, comp_func> bitcnt_map(comp);
    bitcnt_map[7].push_back("seven");
    bitcnt_map[7].push_back("Seven");
    bitcnt_map[8].push_back("eight");
    bitcnt_map[8].push_back("Eight");
    cout << bitcnt_map.begin()->first << endl;
    for(const auto& e : bitcnt_map) {
       cout << e.first << ":";
       for(const auto& s : e.second) {
           cout << s << " ";
       }
       cout <<endl;
    }

    map<int, int> myMap;
    myMap[7] = 11;
    myMap[8] = 12;
    cout << myMap.begin()->first << endl;
    return 0;
}
