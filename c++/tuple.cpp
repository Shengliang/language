#include<tuple>
#include<iostream>
#include<string>
#include<map>
using namespace std;

ostream& operator<<(ostream &out, const tuple<int, char, string> & t)
{
   out << get<0>(t) << ",";
   out << get<1>(t) << ",";
   out << get<2>(t) << " ";
   return out;
}
ostream& operator<<(ostream &out, const tuple<int&, char&, string&> & t)
{
   out << get<0>(t) << ",";
   out << get<1>(t) << ",";
   out << get<2>(t) << " ";
   return out;
}

typedef tuple<int&, char&, string&> T3Ref;
typedef tuple<int, char, string> T3;
int main(void)
{
   map<T3Ref, int> dic;
   T3 t1;
   T3 t2;
   t1 = make_tuple(1,'a', "AAA");
   t2 = make_tuple(2,'b', "BBB");

   int &a = get<0>(t1);
   char & ch = get<1>(t1);
   string& str = get<2>(t1);

   int &b = get<0>(t2);
   char & chb = get<1>(t2);
   string& strb = get<2>(t2);

   T3Ref t11(a,ch,str);
   T3Ref t22(b,chb,strb);
   T3Ref t33(a,chb,strb);

   dic[t11] = 1;
   a = 3;
   dic[t11] = 11; 
   str = "AAa";
   dic[t22] = 22;
   dic[t33] = 33;
   
   cout << t1 << t11 << endl;
   cout << t2 << t22 << endl;
   
   cout << "map:" << endl;
   for(auto & e : dic) {
      cout << e.first << " " << e.second << endl;
   }
   a = 11;
   cout << "map:" << endl;
   for(auto & e : dic) {
      cout << e.first << " " << e.second << endl;
   }
   return 0;
}
