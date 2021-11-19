#include <bits/stdc++.h>

using namespace std;
 int scale[] = {64*64*64,64*64, 64, 1};
class BitMap {
public:
    #define MAX (25*64*64) // 102400
    vector<uint64_t> bitmap[3];
    unordered_map<int, int> mp;
    int sz;
    BitMap() {
        sz = 0;
        bitmap[0].resize(1, 0);
        bitmap[1].resize(MAX/4096,0);
        bitmap[2].resize(MAX/64,0);
    }

    void setlevel(int lvl, int a, int b) {
        bitmap[lvl][a] |= (1ULL << b);
    }

    uint64_t getlevel(int lvl, int a) {
        return bitmap[lvl][a];
    }

    uint64_t clearlevel(int lvl, int a, int b) {
        return bitmap[lvl][a] &= ~(1ULL << b);
    }

    int minKey(int lvl = 0, int i = 0){
       while(lvl <= 2) {
           uint64_t & m = bitmap[lvl][i];
           i *= 64;
           i += __builtin_ctzll(m);
	   ++lvl;
       }
       return i;
    }

    int maxKey(int lvl = 0, int i = 0){
       while(lvl <= 2) {
          uint64_t & m = bitmap[lvl][i];
          i *= 64;
          i += (63 -__builtin_clzll(m));
	  ++lvl;
       }
       return i;
    }

    int rightBit(uint64_t m, int c) {
      int nc = c + 1;
      if (nc == 64) return nc;
      uint64_t m2 = (1ULL << nc) - 1;
      m &= ~m2;
      return __builtin_ctzll(m);
    }

    int leftBit(uint64_t m, int c) {
      if(c == 0) return -1;
      if (c >= 64) return -1;
      uint64_t m2 = (1ULL << c) - 1;
      m &= m2;
      if (m == 0) return -1;
      int nc = __builtin_clzll(m);
      if (nc == 64) return -1;
      int ans = 63 - nc;
      return ans;
    }
    int leftKey(int k, int lvl=0){
       int idx = k/scale[lvl];
       int off = k/scale[lvl+1] % 64;
       int ans = -1;
       uint64_t mask = bitmap[lvl][idx];
       if (mask & (1ULL << off)) {
           if (lvl == 2) {
	      int noff = leftBit(mask, off);
	      if (noff < 64 && noff >= 0) {
	         return idx*64+noff;
	      }
	   } else {
              ans = leftKey(k, lvl+1);
	   }
       }
       if (ans != -1) {
          return ans;
       }
       int noff = leftBit(mask, off);
       if (noff < 64 && noff >= 0) {
         ans = maxKey(lvl+1, idx*64 + noff);
	 return ans;
       }
       return -1;
    }

    int rightKey(int k, int lvl=0){
       int idx = k/scale[lvl];
       int off = k/scale[lvl+1] % 64;
       int ans = -1;
       uint64_t mask = bitmap[lvl][idx];
       if (mask & (1ULL << off)) {
           if (lvl == 2) {
	      int noff = rightBit(mask, off);
	      if (noff < 64) {
	         return idx*64+noff;
	      }
	   } else {
              ans = rightKey(k, lvl+1);
	   }
       }
       if (ans != -1) {
          return ans;
       }
       int noff = rightBit(mask, off);
       if (noff < 64) {
         ans = minKey(lvl+1, idx*64 + noff);
	 return ans;
       }
       return -1;
    }

    int rightKey2(int k){
       int c0 = k/4096;
       int c1 = k/64;
       int c2 = k;
       uint64_t m0 = bitmap[0][0];
       int nc0 = c0;
       if (bitmap[0][0] & (1ULL << (c0%64))) {
          uint64_t m1 = bitmap[1][c0];
	  int nc1 = c1;
          if (bitmap[1][c0] & (1ULL << (c1%64))) {
             uint64_t m2 = bitmap[2][c1];
	     int nc2 = rightBit(bitmap[2][c1], c2%64);
	     if (nc2 < 64) {
	       return c1*64+nc2;
	     }
	  }
	  nc1 = rightBit(m1, c1%64);
	  if (nc1 < 64) {
            int ans = minKey(2, (c0*64 + nc1));
	    //cout <<  "k2: " << k << " next k? " << ans << endl;
            return ans;
	  }
       }
       nc0 = rightBit(m0, c0%64);
       if (nc0 < 64) {
         int ans = minKey(1, nc0);
	 //cout <<  "k1: " << k << " next k? " << ans << endl;
	 return ans;
       }
       return -1;
    }

    /*
     * lvl2   k/64 k%64
     * lvl1   (k/64)/64 (k/64)%64
     * lvl0   (k/64)/64/64 ((k/64/64)%64
     */
    void add(int k, int cnt=1) {
       int c = mp[k]; 
       mp[k]+=cnt;
       sz+=cnt;
       if (c != 0) return;
       int lvl = 2;
       while(lvl >= 0) {
          setlevel(lvl--, k/64, k%64);
          k /= 64;
       }
    }

    void remove(int k, int cnt=1) {
        mp[k]-=cnt;
        sz -= cnt;
        if (mp[k] != 0) return;
        int lvl = 2;
        while(lvl >= 0) {
          auto m = clearlevel(lvl--, k/64, k%64);
          if (m) break;
          k /= 64;
        }
    }

    int& operator[](int k) {
        return mp[k];
    }
};


ostream& operator<<(ostream& out, BitMap& bitmap) {
   out << "bitmap range: [" << bitmap.minKey() << "," << bitmap.maxKey() << "]" << endl;
   for(auto& e: bitmap.mp) {
      out << e.first << "," << e.second << " ";
   }
   return out;
}

class Solution {
public:
    int minPairSum(vector<int>& A) {

        /*
        sort(begin(A), end(A));
        int n = A.size();
        int i = 0;
        int j = n-1;
        int ans = 0;
        while(i < j) {
            int x = A[i++]+A[j--];
            ans = max(x, ans);
        }
        return ans;*/

       BitMap mp;
       for(auto x:A) {
           mp.add(x);
       }

        int ans = 0;
        int i = mp.minKey();
        int j = mp.maxKey();

         while(i < j){
           cout << "min:" << i << " max:" << j << endl;
           ans = max(ans, i+j);
           int x = min(mp[i], mp[j]);
           mp.remove(i, x);
           mp.remove(j, x);
           i = mp.minKey();
           j = mp.minKey();
        }
        if (mp[i] > 1) {
            ans = max(ans, i+i);
        }
        return ans;
    }
};


int main(void) {
{
   BitMap mp;
   for(int i = 0; i <= 65; ++i) {
      cout << "i:" << i << " " << mp.leftBit(0xAAAAAAAAAAAAAAAAULL, i)  << endl;
   } cout << endl;
}
#if 0
       cout << __builtin_ctzll(0LL) << endl;
       cout << __builtin_clzll(0LL) << endl;
   Solution sln;
   vector<int> A = {1,2,3,4,5,6,7,8,9};
   BitMap mp;
   cout << mp << endl;
   for(auto x: A) {
       mp.add(x);
       cout << mp << endl;
   }
   cout << mp << endl;
   mp.remove(3);
   mp.remove(2);
   mp.remove(8);
   cout << mp << endl;
   mp.remove(9);
   cout << mp << endl;
   mp.remove(1);
   cout << mp << endl;
   for(int i  = 0; i < 10; ++i) cout << i << " right:" << mp.rightKey(i) << endl;
   mp.add(3);
   cout << mp << endl;
   mp.add(2);
   cout << mp << endl;
   mp.add(1);
   cout << mp << endl;
   mp.add(8);
   cout << mp << endl;
   for(int i  = 0; i < 10; ++i) cout << i << " right:" << mp.rightKey(i) << endl;
   //return 0;
  // cout << sln.minPairSum(A) << endl;
  //
#endif
#if 1
   if (1) {

       BitMap mp;
       int n = 100000;
       for(int i = 0; i < n; ++i) mp.add(i);
       int m = (int)sqrt(n);
       for(int p = 2; p <= m; p++) {
           if (mp[p] == 0)
               continue;
           for(int i = p*p; i < n; i+=p) {
               mp.remove(i);
           }
       }
       int i = mp.minKey();
       int j = mp.maxKey();
       cout << i << " ";
       while(i < j){
	 i = mp.rightKey(i,0);
         cout << i << " ";
       } cout << endl;

#if 1
       i = mp.minKey();
       cout << j << " ";
       while(i < j){
	 j = mp.leftKey(j,0);
         cout << j << " ";
       } cout << endl;

#endif

       j = mp.maxKey();
#if 0
       cout << j << " ";
       while(i < j){
         mp.remove(j); j = mp.maxKey();
         cout << j << " ";
       } cout << endl;
#else
       cout << i << " ";
       while(i < j){
         mp.remove(i); i = mp.minKey();
         cout << i << " ";
       } cout << endl;
#endif
   }
#endif
   return 0;
}
