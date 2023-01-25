#include<iostream>
#include<vector>
#include<stdint.h>
#include <algorithm>
using namespace std;
// g++ --std=c++11 mask64.cpp
using partition_id_t = uint16_t;
std::vector<partition_id_t>  GetPartitionIds(const std::vector<uint64_t> & partition_mask) {
      int sz = partition_mask.size();
      std::vector<partition_id_t> partition_ids;
      for (int j = 0;  j < sz; ++j) {
          uint64_t mask = partition_mask[j];
          if (mask == 0) continue;
          while (mask != 0) {
              uint16_t partition_id = j*64 + __builtin_ctzll(mask);
              mask ^= (1ULL << partition_id);
              partition_ids.push_back(partition_id);
          }
      }
      return partition_ids;
 }

std::vector<uint64_t>  GetPartitionMask(const std::vector<partition_id_t> & partition_ids) {
      int n = partition_ids.size();
      if (n == 0) return {};
      int max_id = 1 + *max_element(begin(partition_ids), end(partition_ids));
      int sz = max_id/64;
      if (max_id%64) sz+=1;
      std::vector<uint64_t> partition_mask(sz, 0);
      for (int i = 0;  i < n; ++i) {
          partition_id_t id = partition_ids[i];
          int r = id / 64;
          int c = id % 64;
          partition_mask[r] |= (1ULL << c);;
      }
      return partition_mask;
 }
int main(void) {
   vector<uint64_t> mask(2);
   mask[0] = 0xface0000ULL;
   mask[1] = 0xbeefULL;
   auto ids = GetPartitionIds(mask);
   auto m =  GetPartitionMask(ids);
   for(auto x:m) {
     cout << hex << x << endl;
   }
   mask[0] = 0x0LL;
   mask[1] = 0x0;
   ids = GetPartitionIds(mask);
   m =  GetPartitionMask(ids);
   for(auto x:m) {
     cout << hex << x << endl;
   }
   mask[0] = 0x1LL;
   mask[1] = 0x0;
   ids = GetPartitionIds(mask);
   m =  GetPartitionMask(ids);
   for(auto x:m) {
     cout << hex << x << endl;
   }
   return 0;
}
