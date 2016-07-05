//
// This program uses a simple user-defined function
// to provide a hash function for use in unordered_map.
// The function is passed in as a lambda expression to
// the unordered_map constructor.
//
// Compile this example with Visual Studio 2010
// or g++ 4.5 using -std=c++0x
//
#include <iostream>
#include <unordered_map>
#include <string>
#include <functional>
#include <algorithm>

using namespace std;

typedef pair<string,string> Name;
typedef unordered_multimap<Name,int,function<size_t ( const Name & name )>> mymap;

int main(int argc, char* argv[])
{
    mymap ids(100, []( const Name & name )
             {
                 return   hash<string>()(name.first)
                        ^ hash<string>()(name.second);
             } );
    ids.emplace(Name("Mark", "Nelson"), 40561);
    ids.emplace(Name("Andrew","Binstock"), 40562);
    ids.emplace(Name("1","1"), 1);
    ids.emplace(Name("1","1"), 11);
    ids.emplace(Name("2","2"), 2);
    for ( auto ii = ids.begin() ; ii != ids.end() ; ii++ )
        cout << ii->first.first
             << " "
             << ii->first.second
             << " : "
             << ii->second
             << endl;
    cout << ids.count(Name("1", "1")) << endl;
    auto range = ids.equal_range(Name("1", "1"));
    for_each (range.first, range.second,
       [](mymap::value_type & x) {
         cout << " k(" << x.first.first << ","
              << x.first.second << ") = "
               << " " << x.second << endl;
       }
    );
    return 0;
}
