
#include <bits/stdc++.h>

using namespace std;


// A Dequeue (Double ended queue) based method for printing maximum element of
// all subarrays of size k
void printKMax(int arr[], int n, int k)

{

    // Create a Double Ended Queue, dq that will store indexes of array elements
    // The queue will store indexes of useful elements in every window and it will
    // maintain decreasing order of values from front to rear in dq, i.e.,
    // arr[dq.front[]] to arr[dq.rear()] are sorted in decreasing order
    assert(k > 0);
    assert(n >= k);
    std::deque<int> dq(1, 0);
    cout << "=========================" << k << " " << n << endl;

    int i;
    for (i = 1; i < k; ++i) {
	// Remove all smaller elements in the back.
        while ((!dq.empty()) && arr[i] >= arr[dq.back()]) {
            dq.pop_back();
	}
        dq.push_back(i);
    }
    cout << "Q["; for(auto e: dq) cout << arr[e] << " " ;    cout << "]" << endl;

    // Process rest of the elements, i.e., from arr[k] to arr[n-1]
    for (; i < n; ++i) {

        // The element at the front of the queue is the largest element of
        // previous window, so print it
        cout << "\nmax:" << arr[dq.front()] << endl;

        // Remove the elements which are out of this window
        while ((!dq.empty()) && dq.front() <= i - k) {
	    cout << "pop oow:" << dq.front() <<  " " << arr[dq.front()] << endl;
            dq.pop_front(); // Remove from front of queue
	}


        // Remove all elements smaller than the currently being added element
        while ((!dq.empty()) && arr[i] >= arr[dq.back()]) {
	    cout << "pop smaller:" << dq.back() << " " << arr[dq.back()] << endl;
            dq.pop_back();
	}

        // Add current element at the rear of dq
        dq.push_back(i);
	cout << "push:" << dq.back() << " " << arr[dq.back()] << endl;
        cout << "Q["; for(auto e: dq) cout << arr[e] << " " ;    cout << "]" << endl;
    }

    // Print the maximum element of last window
    cout << "max:" << arr[dq.front()] << endl;
    cout << "Q["; for(auto e: dq) cout << arr[e] << " " ;    cout << "]" << endl;
    cout << endl;
}



// Driver program to test above functions

int main()

{

    //int arr[] = { 12, 1, 78, 90, 57, 89, 56 };
    int arr[] = { 312, 301, 278, 190, 157, 89, 56 };

    int n = sizeof(arr) / sizeof(arr[0]);

    int k = 3;
    printKMax(arr, n, k);
    k = 4;
    printKMax(arr, n, k);
    k = 5;
    printKMax(arr, n, k);
    k = 6;
    printKMax(arr, n, k);
    k = 7;
    printKMax(arr, n, k);

    return 0;

}
