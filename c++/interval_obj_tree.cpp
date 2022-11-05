//Reference https://www.geeksforgeeks.org/interval-tree/
#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

struct string_prefix {
    uint8_t m_rsvd : 4;
    uint8_t m_len  : 4;
    char m_data[15];

    int length() const {
        return m_len;
    }
    void init(const char * data, int len) {
       this->m_len = len;
       for(int i = 0; i < len; ++i) {
           m_data[i] = data[i];
       }
    }
    string_prefix(const char * data) {
       init(data, strlen(data));
    }
    string_prefix(const char * data, int len) {
       init(data, len);
    }
    string_prefix(const std::string &str) {
       init(str.c_str(), str.length());
    }
    string_prefix & operator=(const string_prefix & other) {
        this->m_len = other.length();
        for(int i = 0; i < this->m_len; ++i) {
            this->m_data[i] = other.m_data[i];
        }
        return *this;
    }
    bool operator==(const string_prefix & other) const {
        int a = length();
        int b = other.length();
        if (a != b) return false;
        for(int i = 0; i < a; ++i) {
            if (m_data[i] != other.m_data[i]) {
                return false;
            }
        }
        return true;
    }
    bool operator<(const string_prefix & other) const {
        int a = length();
        int b = other.length();
        int len = min(a,b);
        for (int i = 0; i < len; ++i) {
            if (m_data[i] == other.m_data[i]) {
                continue;
            }
            return (m_data[i] < other.m_data[i]);
        }
        return a < b;
    }
    bool operator<=(const string_prefix & other) const {
        return *this == other || *this < other;
    }
}; 

ostream & operator<<(ostream & out, const string_prefix& s) {
   int len = s.length();
   for(int i = 0; i< len; ++i) {
       out << s.m_data[i];
   }
   return out;
}

// Structure to represent an interval
template<typename IEType>
struct Interval
{
    IEType low;
    IEType high;
    Interval(IEType l, IEType h) : low(l), high(h) {}
};

// Structure to represent a node in Interval Search Tree
template<typename IEType>
struct ITNode
{
	Interval<IEType> *i;
    ITNode(Interval<IEType> *ii) :  i(ii), m_min(&(ii->low)), m_max(&(ii->high)), left(nullptr), right(nullptr) {}
    IEType *m_min;
    IEType *m_max;
	ITNode<IEType> *left, *right;
};

template<typename IEType>
ITNode<IEType> *insert(ITNode<IEType> *root, Interval<IEType> *i)
{
	if (root == NULL)
		return new ITNode<IEType>(i);

	IEType & l = root->i->low;

	if (i->low < l)
		root->left = insert(root->left, i);
	else
		root->right = insert(root->right, i);

	if (i->low < *(root->m_min))
		root->m_min = &i->low;
	if (*(root->m_max) < i->high)
		root->m_max = &i->high;

	return root;
}

// A utility function to check if given two intervals overlap
template<typename IEType>
bool doOVerlap(Interval<IEType> *i1, Interval<IEType> *i2)
{
	if (i1->low <= i2->high && i2->low <= i1->high)
		return true;
	return false;
}

// The main function that searches a given interval i in a given
// Interval Tree.
template<typename IEType>
Interval<IEType> *overlapSearch(ITNode<IEType> *root, Interval<IEType> *i)
{
	// Base Case, tree is empty
	if (root == NULL) return NULL;

	// If given interval overlaps with root
	if (doOVerlap<IEType>(root->i, i))
		return root->i;

	// If left child of root is present and min of right child is
	// greater than or equal to given interval, then i may
	// overlap with an interval is left subtree
	if (root->right != NULL && *(root->right->m_min) < i->high)
		return overlapSearch<IEType>(root->right, i);
    else
	    return overlapSearch<IEType>(root->left, i);
}

template<typename IEType>
void inorder(ITNode<IEType> *root, int i)
{
	if (root == NULL) return;

	inorder<IEType>(root->left, i+1);

    for(int j = 0; j < i; ++j) {
        cout << "  ";
    }
	cout << "[" << root->i->low << ", " << root->i->high << "]"
		<< " m_min = " << *(root->m_min) << " -> "
		<< " m_max = " << *(root->m_max) << endl;

	inorder<IEType>(root->right, i+1);
}

// Driver program to test above functions
int test_string()
{
	// Let us create interval tree shown in above figure
	Interval<string_prefix> arr[] = {
        {string_prefix("15"), string_prefix("20")}, 
        {string_prefix("10"), string_prefix("30")},
        {string_prefix("17"), string_prefix("19")},
		{string_prefix("05"), string_prefix("20")},
        {string_prefix("12"), string_prefix("15")},
        {string_prefix("30"), string_prefix("40")}
	};
	int n = sizeof(arr)/sizeof(arr[0]);
	ITNode<string_prefix> *root = NULL;
	for (int i = 0; i < n; i++)
		root = insert<string_prefix>(root, &arr[i]);

	cout << "Inorder traversal of constructed Interval Tree is\n";
	inorder<string_prefix>(root, 0);

	Interval<string_prefix> xarr[] = {
        {string_prefix("06"), string_prefix("07")}, 
        {string_prefix("00"), string_prefix("99")}, 
        {string_prefix("15"), string_prefix("17")}, 
        {string_prefix("31"), string_prefix("33")}, 
        {string_prefix("32"), string_prefix("44")}, 
        {string_prefix("50"), string_prefix("90")}, 
        {string_prefix("01"), string_prefix("02")}
    };
    for(auto & e : xarr) {
		cout << "\nSearching for interval [" << e.low << "," << e.high << "]";
		Interval<string_prefix> *res = overlapSearch<string_prefix>(root, &e);
		if (res == NULL)
			cout << " No Overlapping Interval";
		else
			cout << " Overlaps with [" << res->low << ", " << res->high << "]";
    }
    cout << endl;
	return 0;
}

int test_int()
{
	// Let us create interval tree shown in above figure
	Interval<int> arr[] = {
        {15, 20}, 
        {10, 30},
        {17, 19},
		{5, 20},
        {12, 15},
        {30, 40}
	};
	int n = sizeof(arr)/sizeof(arr[0]);
    for(int i = 0; i < n; ++i) {
       cout << arr[i].low << " " << arr[i].high << endl;
    }
	ITNode<int> *root = NULL;
	for (int i = 0; i < n; i++)
		root = insert<int>(root, &arr[i]);

	cout << "Inorder traversal of constructed Interval Tree is\n";
	inorder<int>(root, 0);

	Interval<int> xarr[] = {
        {6, 7}, 
        {0, 99}, 
        {15, 17}, 
        {31, 33}, 
        {32, 44}, 
        {50, 90}, 
        {1, 2}
    };
    for(auto & e : xarr) {
		cout << "\nSearching for interval [" << e.low << "," << e.high << "]";
		Interval<int> *res = overlapSearch<int>(root, &e);
		if (res == NULL)
			cout << " No Overlapping Interval";
		else
			cout << " Overlaps with [" << res->low << ", " << res->high << "]";
    }
    cout << endl;
	return 0;
}

int main() {
    test_string();
    test_int();
    return 0;

}
