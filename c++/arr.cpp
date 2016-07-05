
#include <array>
#include <iostream>
int main()
{
  std::array<int, 4> nums {1, 3, 5, 7};
  constexpr size_t last_index = nums.size() - 1;
  std::cout << "nums contains [0-" << last_index << "] elements.\n";
  int fs = 17;
  int fsize = fs & ~0xF;
  if (fs&0xF) fsize += 0x10;
  std::cout << fsize << std::endl;
}
