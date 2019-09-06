#include <iostream>
#include <chrono>
using namespace std;

struct Node
{
    int key;
    struct Node *left, *right;
};

// A utility function to create a new BST Node
struct Node *newNode(int item)
{
    struct Node *temp = new Node;
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

// Stores inoder traversal of the BST
// in arr[]
void storeSorted(Node *root, int arr[], int &i)
{
    if (root != NULL)
    {
        storeSorted(root->left, arr, i);
        arr[i++] = root->key;
        storeSorted(root->right, arr, i);
    }
}

/* A utility function to insert a new
   Node with given key in BST */
Node* insert(Node* node, int key)
{
    /* If the tree is empty, return a new Node */
    if (node == NULL) return newNode(key);

    /* Otherwise, recur down the tree */
    if (key < node->key)
        node->left  = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);

    /* return the (unchanged) Node pointer */
    return node;
}

// This function sorts arr[0..n-1] using Tree Sort
void treeSort(int arr[], int n)
{
    struct Node *root = NULL;

    // Construct the BST
    root = insert(root, arr[0]);
    for (int i=1; i<n; i++)
        insert(root, arr[i]);

    // Store inoder traversal of the BST
    // in arr[]
    int i = 0;
    storeSorted(root, arr, i);
}

// Driver Program to test above functions
int main()
{
    const int size = 200000;
	int arr[size];

	for (int i = 0; i < size; ++i) {
		arr[i] = 1 + rand() % 50;
	}
	auto start = chrono::steady_clock::now();
    int n = sizeof(arr)/sizeof(arr[0]);

    treeSort(arr, n);
    auto end = chrono::steady_clock::now();
	cout << "\nTime of execution: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " milisegundos." << endl;
	return 0;
}
