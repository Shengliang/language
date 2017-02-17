#include <iostream>
#include <unordered_map>
#include <map>
#include <string>
#include <functional>

using namespace std;

typedef pair<string,string> Name;

size_t name_hash( const Name & name )
{
    return hash<string>()(name.first) ^ hash<string>()(name.second);
}

class A {
	public:
	int a;
		A(int x=0):a(x) {cout << "new A" << this << " " << a << endl; }
		~A() { cout << __FUNCTION__ << ":" << this << " " << a << endl; }
		A(const A& x) : a(x.a) { 
		   cout << "new A: " << __FUNCTION__ << " " << this << " " << a << endl; }
};

ostream & operator<<(ostream & out, const A&a) {
	return out << a.a;
}

int main(int argc, char* argv[])
{
    unordered_map<Name,A,function<decltype(name_hash)>> ids(100, name_hash );
    auto && mark  = Name("Mark", "Nelson");
    auto && andrew = Name("Andrew","Binstock");

    cout << "Init mark" << endl;
    ids[mark] = 40561;

    cout << "Init andrew" << endl;
    ids[andrew] = 40562;

    cout << "Print ids:" << endl;
    for ( auto& e : ids) 
        cout << e.first.first << " " << e.first.second
		<< " : " << e.second << endl;

    {
	    cout << "process andrew" << endl;
	    // const auto x = ids[andrew];
	    const auto& x = ids[andrew];
	    cout << "&x is " << &x << endl;

	    ids.erase(andrew);
    }

    cout << "Print ids:" << endl;
    for ( auto& e : ids) 
        cout << e.first.first << " " << e.first.second
		<< " : " << e.second << endl;
    return 0;
}
