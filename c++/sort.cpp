#include<iostream>
#include<algorithm>
#include<vector>
#include<string>

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
    return 0;
}

