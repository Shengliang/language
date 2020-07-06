#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<functional>

using namespace std;

struct Person {
   string name;
   int  age;
   bool operator<(const Person& other) const {
       if (this->age == other.age)
          return this->name < other.name;
       else
          return this->age < other.age;
   }
};


int main(void) {
    Person arr[] = { 
     {"Alice", 14},
     {"Bob", 13},
     {"David", 14},
     {"Ella", 6}
    };
    int num = sizeof(arr)/sizeof(arr[0]);
    sort(begin(arr), end(arr));
    for(int i=0; i<num; i++) {
       Person *p = &arr[i];
       cout << p->age << " " << p->name << endl;
    }
    vector<int> vec = {41,42,43,4, 40, 45, 44, 443,445, 445445444, 445445446, 445445445, 444, 445};
    function<bool(int, int)> mygreater = [](int a, int b) {
	    string sa = to_string(a);
	    string sb = to_string(b);
	    int la = sa.length();
	    int lb = sb.length();
	    int len = max(la, lb);
	    for(int i = 0; i < len; i++) {
		    if (sa[i%la] != sb[i%lb]) {
			return (sa[i%la] > sb[i%lb]);
		    }
	    }
	    return false;
    };
    sort(begin(vec), end(vec), mygreater);
    for(auto v : vec)
	    cout << v << " " << endl;
    return 0;
}

