#include "bits/stdc++.h"
using namespace std;
void print(vector<int>& arr, int n) {
   for(int i =  0; i < n; ++i) {
     cout << arr[i] << " ";
   }
   cout << endl;
}


// Returns the correct position of pivot element
int Partition(vector<int>& arr, int l, int r) {
    int lst = arr[r];
    cout << "Partition:[" << l << "," << r << "] pivot:" << arr[r] << endl;
    int i = l; //search index i: search for elements < lst
    int d = l; //start destination for all smaller elements.
    while (i < r) {
        if (arr[i] < lst) {
   	    print(arr, arr.size());
	    cout << d <<":" << arr[d] << " <-> " << i <<":"<<arr[i] << endl;
            swap(arr[d], arr[i]);
            d++;
        }
        i++;
    }
    print(arr, arr.size());
    cout << d <<":" << arr[d] << " <-> " << i <<":"<<arr[i] << endl;
    swap(arr[d], arr[r]);
    print(arr, arr.size());
    return d;
}



int randomPartition(vector<int>& arr, int l, int r)
{
    int n = r - l + 1;
    int pivot = rand() % n;
    swap(arr[l + pivot], arr[r]);
    return Partition(arr, l, r);
}


int find_max(vector<int>& arr, int l, int r) {
   int v = INT_MIN;
   for(int i = l; i <= r; ++i) {
      if (arr[i] > v) {
	   v = arr[i];
      }
   }
   return v;
}

int quickselect(vector<int>& arr, int l, int r, int k) {

    int partitionIndex = randomPartition(arr, l, r);
    //int partitionIndex = Partition(arr, l, r);
    if (partitionIndex == k) {
	    if (k == l) {
    	      return k-1;
	    }
	    return find_max(arr, l, k-1);
    }
    // [ l,...,k,.p.,r ]
    if (partitionIndex > k)
        return quickselect(arr, l, partitionIndex - 1, k);
    // [ l,..p.,k,...,r ]
    else
        return quickselect(arr, partitionIndex + 1, r, k);
}



double findMedian(vector<int>& arr, int n) {

    int k = n/2;
    int x  = quickselect(arr, 0, n - 1, k);
    // 0 1 2 3 4  5/2
    //     ^
    if (n % 2 == 1) {
        return arr[k];
    }
    // 0 1 2 3  4/2
    //     ^
    else { 
        double ans = (x + arr[k])/2.0;
        cout << x << " " << arr[k] << " median:" << ans << endl;
        return ans;
    }
}


double findMedian2(vector<int>& v, int n) {
    int k = n/2;
    nth_element(begin(v), begin(v)+k, end(v));
    if (n&1) return v[k];
    int x = *max_element(begin(v), begin(v)+k);
    return (x+v[k])/2.0;
}

double findMedian3(vector<int>& arr, int n) {
   sort(begin(arr), end(arr));
   if (n&1) {
	   return arr[n/2];
   } else {
	   return (arr[n/2] + arr[n/2-1])/2.0;
   }
}

// Driver program to test above methods
int main()
{
    for(int n = 9; n < 100; ++n) {
       cout << "n : " << n << endl;
       vector<int> arr(n);
       iota(begin(arr), end(arr), 0);
       random_shuffle(begin(arr), end(arr));
       vector<int> v = arr;
       double ans1 = findMedian(arr, n);
       double ans2 = findMedian2(v, n);
       double ans3 = findMedian3(v, n);
       cout << "Median = " << ans1 <<  " " << ans2 << " " << ans3 << endl;
       assert(ans1 == ans2);
       assert(ans1 == ans3);
       random_shuffle(begin(arr), begin(arr)+n);
       break;
    }
    return 0;

}
/*
n : 9
Partition:[0,8] pivot:2
4 3 7 8 0 5 6 1 2 
0:4 <-> 4:0
0 3 7 8 4 5 6 1 2 
1:3 <-> 7:1
0 1 7 8 4 5 6 3 2 
2:7 <-> 8:2
0 1 2 8 4 5 6 3 7 
Partition:[3,8] pivot:4
0 1 2 8 7 5 6 3 4 
3:8 <-> 7:3
0 1 2 3 7 5 6 8 4 
4:7 <-> 8:4
0 1 2 3 4 5 6 8 7 
Median = 4 4 4
*/
