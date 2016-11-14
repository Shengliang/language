// splicing lists
#include <iostream>
#include <list>

int main ()
{
  std::list<int> mylist1, mylist2;
  std::list<int>::iterator its;
  std::list<int>::iterator ite;

  // set some initial values:
  for (int i=1; i<=10; ++i)
     mylist1.push_back(i);      // mylist1: 1 2 3 4

  for (int i=1; i<=10; ++i)
     mylist2.push_back(i*10);   // mylist2: 10 20 30

  its = mylist2.begin();
  std::advance(its,3);

  ite = mylist2.begin();
  std::advance(ite,5);

  mylist1.splice ( mylist1.begin(), mylist1, its, ite);

  std::cout << "mylist1 contains:";
  for (const auto & e: mylist1) {
    std::cout << ' ' << e;
  }
  std::cout << '\n';

  std::cout << "mylist2 contains:";
  for (const auto & e: mylist2) {
    std::cout << ' ' << e;
  }
  std::cout << '\n';

  auto e = mylist1.end();
  its = mylist2.begin();
  std::advance(its,3);

  ite = mylist2.begin();
  std::advance(ite,5);
  mylist1.splice (e, mylist1, its, ite);

  std::cout << "mylist1 contains:";
  for (const auto & e: mylist1) {
    std::cout << ' ' << e;
  }
  std::cout << '\n';

  std::cout << "mylist2 contains:";
  for (const auto & e: mylist2) {
    std::cout << ' ' << e;
  }
  std::cout << '\n';


  return 0;
}
