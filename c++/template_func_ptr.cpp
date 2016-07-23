#include<iostream>
#include<algorithm>
#include<string>
using namespace std;
// http://stackoverflow.com/questions/14848924/how-to-define-typedef-of-function-pointer-which-has-template-arguments

template<typename A, typename R>
using CallbackType = R (*)(const A&);

template<typename A, typename R>
struct Callback {
   typedef R (*Func)(const A&);
};

int foo_i(const int& a) {
    return a-1;
}

string foo_s(const string& s) {
    string r = s;
    transform(begin(r), end(r), begin(r), ::tolower);
    return r;
}

int main(int argc, char* argv[]) {

    int a = 1;
    string s = "ABC";

    CallbackType<int, int>   fi = foo_i;
    cout << foo_i(a) << endl;

    CallbackType<string, string>   fs = foo_s;
    cout << foo_s(s) << endl;

    Callback<int, int>::Func si = foo_i;
    cout << si(a) << endl;
    
    Callback<string, string>::Func ss = foo_s;
    cout << ss(s) << endl;
   
    return 0;
}

