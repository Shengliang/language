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
    //vector<int> vec = {41,42,43,4, 40, 45, 44, 443,445, 445445444, 445445446, 445445445, 444, 445, 46464, 46};
    vector<int> vec = {45, 4, 46, 44, 43, 4545, 4542, 4547, 4645, 46465, 46464};
    // 46465 46 46464 4645 4547 45 4545 4542 4 44 43 
    function<bool(int, int)> mygreater = [](int a, int b) {
	    string x = to_string(a) + to_string(b);
	    string y = to_string(b) + to_string(a);
	    return x > y;
    };
    sort(begin(vec), end(vec), mygreater);
    for(auto v : vec)
	    cout << v << " ";
    cout << endl;
    return 0;
}

