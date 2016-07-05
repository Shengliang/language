

// unordered_multimap::equal_range
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>

typedef std::unordered_multimap<std::string,std::string> stringmap;

int main ()
{
  stringmap myumm = {
     {"orange","FL"},
     {"strawberry","LA"},
     {"strawberry","OK"},
     {"pumpkin","NH"}
  };

  std::cout << "Entries with strawberry:";
  auto range = myumm.equal_range("strawberry");
  for_each (
    range.first,
    range.second,
    [](stringmap::value_type& x){std::cout << " " << x.second;}
  );
  std::cout << std::endl;
  return 0;
}
