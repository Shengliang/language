#include<bits/stdc++.h>
#include<string>
using namespace std;
class Solution {
public:
    string removeKdigits(string num, int k) {
        int sz = num.length();
        if (k >= sz)
            return "0";

        string ans(sz, '0');
        int i = 0;
        for (char c : num) {
           while (i > 0 && ans[i-1] > c && k)
               --k, --i;
            
           // can't have leading '0'
           if (i > 0 || c != '0')
               ans[i++] = c; 
       }   
       i -= k;
       if (i < ans.length()) ans.resize(i);
       return ans.empty() ? "0" : ans;
  
    }
};

int main(int argc, char*argv[]) {
	Solution s;
	std::string num = "111111111111111111111111111111111111";
	std::cout << s.removeKdigits(num, 10) << std::endl;
	return 0;
}
