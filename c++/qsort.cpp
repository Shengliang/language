#include <bits/stdc++.h>
using namespace std;

int partition(vector<int>&  ar, int i, int j) {

   int pl=j;
   int f =0;
   int x = ar[j];
   for(int t=i; t<j; t++) {
       if (ar[t] > x) {
           if (f==0) {
               f=1;
               pl=t;
           }
       } else if(f==1) {
           int tmp = ar[t];
           ar[t] = ar[pl];
           ar[pl] = tmp;
           pl++;
       }
   }
   if ((f==1) && (pl<j) && (pl>=0))  {
      //cout << "swap: " << ar[j] << " " << ar[pl] << endl;
      ar[j] = ar[pl];
      ar[pl] = x;
 
   }
#if 0
   for(int t=i; t<=j ; t++) {
        cout << ar[t] << " ";
   }
   cout << endl;
#endif
   for(int t=0; t<ar.size(); t++) {
        cout << ar[t] << " ";
   }
   cout << endl;
   return pl;
    
}

void qsort(vector<int>& ar, int i, int j)
{
   if (i<j) {
       int p = partition(ar,i,j);
       qsort(ar, i, p-1);
       qsort(ar, p+1, j);
   }    
}

void quickSort(vector <int> &arr) {
   // Complete this function
   int i=0;
   int j=arr.size()-1;

   qsort(arr, i, j);

}

int main()
{
    int n;
    cin >> n;

    vector <int> arr(n);
    for(int i = 0; i < (int)n; ++i) {
        cin >> arr[i];
    }

    quickSort(arr);
    return 0;
}


