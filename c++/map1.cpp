

#include <map>
#include <iostream>

using namespace std;

int main()
{
    multimap<int,int> m;

    m.insert( make_pair(1,1) );    
    m.insert( make_pair(0,2) );    
    m.insert( make_pair(1,5) );    
    m.insert( make_pair(4,5) );    
    m.insert( make_pair(1,3) );

    int key = 1;

    multimap<int,int>::const_iterator it  = m.lower_bound(key);
    multimap<int,int>::const_iterator it2 = m.upper_bound(key);

    while (it !=it2 )
    {
        cout << it->first << " " << it->second << endl;
        ++it;
    }

    return 0;
}
