#include<bitset>
#include<iostream>
#include<vector>

#define f(n) { \
	std::bitset<n> s; std::cout << "sizeof(bitset<" << n << ">) = " << sizeof(s)*8 << std::endl; \
	std::vector<bool> v(n, false); for(int i=0; i< v.size(); i++) v[i] = true; std::cout << "sizeof(vector<bool>(" << n << ")) = " << sizeof(v)*8 << std::endl; \
}

class BitTree {
  uint64_t m_d[64*64]; 
public:
  BitTree() {
  }
  ~BitTree() {
  }

  void ack(uint32_t id, uint64_t mask64);
  bool test(uint32_t id);
  void set(uint32_t id);
  void reset(uint32_t id);
  void flip(uint32_t id);
   
};

void BitTree::ack(uint32_t off, uint64_t mask64) { 
     m_d[off] &= ~(mask64);
     while(mask64) {
        uint64_t leastBit = mask64 & -mask64;  //extract least significant bit on a 2s complement machine
        mask64 ^= leastBit;  // toggle the bit off
	int n = __builtin_ctzll(leastBit);
	std::cout << off*64 + n << std::endl;
     }
}

bool BitTree::test(uint32_t id) { 
     int off = id / 64;
     int shift = id % 64;
     return (m_d[off] & (1ULL << shift)) ? true : false ;
}

void BitTree::set(uint32_t id) { 
     int off = id / 64;
     int shift = id % 64;
     m_d[off] |= (1ULL << shift);
}

void BitTree::reset(uint32_t id) { 
     int off = id / 64;
     int shift = id % 64;
     m_d[off] &= ~(1ULL << shift);
}

void BitTree::flip(uint32_t id) { 
     int off = id / 64;
     int shift = id % 64;
     m_d[off] ^= (1ULL << shift);
}


int main(void) {
  f(1);
  f(2);
  f(4);
  f(8);
  f(16);
  f(32);
  f(64);
  f(128);
  f(256);
  f(512);
  f(1024);
  f(1024*2);
  f(4096);
  f(4096*2);
  f(4096*4);
  f(4096*8);
  f(4096*16);
  f(4096*32);
  f(4096*64);
  { std::vector<bool> vc(1024); std::cout << "vector<bool>(1024): " << sizeof(vc) << std::endl; } 
  { std::vector<char> vc(1024); std::cout << "vector<char>(1024): " << sizeof(vc) << std::endl; } 
  { std::vector<int> vc(1024); std::cout << "vector<int>(1024): " << sizeof(vc) << std::endl;}
  { std::vector<uint64_t> vc(1024); std::cout << "vector<uint64_t>(1024): " << sizeof(vc) << std::endl;}
  { std::vector<std::bitset<1024> > vc(1024); std::cout << "vector<bitset<1024>>(1024): " << sizeof(vc) << std::endl;}
  
  std::vector<int> vc(1024);
  for(int i = 0; i < 1024; i++) vc[i] = i;
  int * p0 = & vc.front();
  for(int i = 0; i < 16; i++) std::cout << p0[i]  <<  " ";
  std::cout << std::endl;
  vc.resize(20480);
  int * p1 = & vc.front();
  std::cout << p0 << " " << p1 << std::endl;

  for(int i = 0; i < 10; i++) { std::cout << p1[i]  <<  " "; vc[i] = 0; } 
  std::cout << std::endl;

  /* p0 is invalid.  However, some of them still point to old data. vector::resize API has security issue. */
  for (int i = 0; i < 10; i++) std::cout << p0[i]  <<  " ";
  std::cout << std::endl;

  BitTree bt;
  for(int i = 0; i < 64*64*64; i++) bt.set(i);
  bt.ack(64*64,  0xFACEULL);
  bt.ack(0,  0xFFFFFFFFFFFFFFFFULL);
  bt.ack(1,  0xFFFFFFFFFFFFFFFFULL);
  bt.ack(2,  0xFFFFFFFFFFFFFFFFULL);
  for(int i = 0; i < 64*64*64; i++) bt.reset(i);
  return 0;
}
