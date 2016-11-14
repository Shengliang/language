// multiset::find
#include <iostream>
#include <set>

int main ()
{
  std::multiset<int> Q;
  std::multiset<int>::iterator it;

  // set some initial values:
  for (int i=1; i<=5; i++) Q.insert(i*10);   // 10 20 30 40 50
  for (int i=1; i<=5; i++) Q.insert(i*10);   // 10 20 30 40 50

  it=Q.find(20);
  Q.erase (Q.begin());
  Q.erase (it);
  Q.erase (Q.find(40));
  Q.erase (50);

  std::cout << "Q contains:";
  for (it=Q.begin(); it!=Q.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}
