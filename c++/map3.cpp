

//
// This program uses a function object to define
// a hash function for use in unordered_map.
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

struct hash_name {
    size_t operator()(const Name &name ) const
    {
        return hash<string>()(name.first) ^ hash<string>()(name.second);
    }
};

int main(int argc, char* argv[])
{
    unordered_map<Name,int,hash_name> ids;
    ids[Name("Mark", "Nelson")] = 40561;
    ids[Name("Andrew","Binstock")] = 40562;
    for ( auto ii = ids.begin() ; ii != ids.end() ; ii++ )
        cout << ii->first.first
             << " "
             << ii->first.second
             << " : "
             << ii->second
             << endl;
    return 0;
}
