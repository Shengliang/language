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

using namespace std;

typedef pair<string,string> Name;

int main(int argc, char* argv[])
{
    unordered_map<Name,int,function<size_t ( const Name & name )>>
    ids(100, []( const Name & name )
             {
                 return hash<string>()(name.first)
                     ^ hash<string>()(name.second);
                 /*
                 cout << hash<string>()("0") << " "
                      << name.first << " "
                      << name.first << endl;
                 return hash<string>()("0");
                 */
             } );
    ids[Name("Mark", "Nelson")] = 40561;
    ids[Name("Andrew","Binstock")] = 40562;
    ids[Name("1","1")] = 1;
    ids[Name("1","1")] = 11;
    ids[Name("2","2")] = 2;
    ids[Name("3","3")] = 3;
    for ( auto ii = ids.begin() ; ii != ids.end() ; ii++ )
        cout << ii->first.first
             << " "
             << ii->first.second
             << " : "
             << ii->second
             << endl;
    auto search = ids.find(Name("1", "1"));
    if (search != ids.end()) {
      cout << "Found "
           << search->first.first << " "
           << search->first.second << " "
           << search->second << endl;
    }
    else {
      cout << "Not found\n";
    }
    cout << ids.count(Name("1", "1")) << endl;
    return 0;
}
