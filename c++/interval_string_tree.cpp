//Reference https://www.geeksforgeeks.org/interval-tree/
#include <iostream>
using namespace std;

// Structure to represent an interval
struct Interval
{
    std::string low;
    std::string high;
    Interval(std::string l, std::string h) : low(l), high(h) {}
};

// Structure to represent a node in Interval Search Tree
struct ITNode
{
	Interval *i;
    ITNode(Interval *ii ) :  i(ii), m_min(&(ii->low)), m_max(&(ii->high)), left(nullptr), right(nullptr) {}
    std::string *m_min;
    std::string *m_max;
	ITNode *left, *right;
};

ITNode *insert(ITNode *root, Interval *i)
{
	if (root == NULL)
		return new ITNode(i);

	std::string& l = root->i->low;

	if (i->low < l)
		root->left = insert(root->left, i);
	else
		root->right = insert(root->right, i);

	if (*(root->m_min) > i->low)
		root->m_min = &i->low;
	if (*(root->m_max) < i->high)
		root->m_max = &i->high;

	return root;
}

// A utility function to check if given two intervals overlap
bool doOVerlap(Interval *i1, Interval *i2)
{
	if (i1->low <= i2->high && i2->low <= i1->high)
		return true;
	return false;
}

// The main function that searches a given interval i in a given
// Interval Tree.
Interval *overlapSearch(ITNode *root, Interval *i)
{
	// Base Case, tree is empty
	if (root == NULL) return NULL;

	// If given interval overlaps with root
	if (doOVerlap(root->i, i))
		return root->i;

	// If left child of root is present and min of right child is
	// greater than or equal to given interval, then i may
	// overlap with an interval is left subtree
	if (root->right != NULL && *(root->right->m_min) < i->high)
		return overlapSearch(root->right, i);
    else
	    return overlapSearch(root->left, i);
}

void inorder(ITNode *root, int i)
{
	if (root == NULL) return;

	inorder(root->left, i+1);

    for(int j = 0; j < i; ++j) {
        cout << "  ";
    }
	cout << "[" << root->i->low << ", " << root->i->high << "]"
		<< " m_min = " << *(root->m_min) << " -> "
		<< " m_max = " << *(root->m_max) << endl;

	inorder(root->right, i+1);
}

// Driver program to test above functions
int main()
{
	// Let us create interval tree shown in above figure
	Interval arr[] = {
        {"15", "20"}, {"10", "30"}, {"17", "19"},
		{"05", "20"}, {"12", "15"}, {"30", "40"}
	};
	int n = sizeof(arr)/sizeof(arr[0]);
	ITNode *root = NULL;
	for (int i = 0; i < n; i++)
		root = insert(root, &arr[i]);

	cout << "Inorder traversal of constructed Interval Tree is\n";
	inorder(root, 0);

	Interval xarr[] = {{"06", "07"}, {"00", "99"}, {"15", "17"}, {"31", "33"}, {"32", "44"}, {"50", "90"}, {"01", "02"}};
    for(auto & x : xarr) {
		cout << "\nSearching for interval [" << x.low << "," << x.high << "]";
		Interval *res = overlapSearch(root, &x);
		if (res == NULL)
			cout << " No Overlapping Interval";
		else
			cout << " Overlaps with [" << res->low << ", " << res->high << "]";
    }
    cout << endl;
	return 0;
}

