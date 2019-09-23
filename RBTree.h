#include"RBTNode.h"
#include <iomanip>
#include <vector>
#include <iostream>

using namespace std;

template<class T>
class  RBTree
{
public:
	RBTree();
	~RBTree();

	void insert(T key);    		// Key is the key value of the node to insert
	void remove(T key); 			// Delete the node of the key
	RBTNode<T>* search(T key);
	void print();
	void preOrder();    // Pre-order traversal Print red black tree
	void ascendingOrder();    //Intermediate traversal
	void descendingOrder();    // Post-order traversal
	bool ifNodeExists(RBTNode<T>* node, T value);
	void printHeight(T x);
	void printDepth(T x);
	void printLevel(T x);

private:
	void leftRotate(RBTNode<T>* &root, RBTNode<T>* x);// left-handed
	void rightRotate(RBTNode<T>* &root, RBTNode<T>* y);// right handed

	void insert(RBTNode<T>* &root, RBTNode<T>* node);// insert node, internal interface
	void InsertFixUp(RBTNode<T>* &root, RBTNode<T>* node);
	void destroy(RBTNode<T>* &node);

	void remove(RBTNode<T>*& root, RBTNode<T>*node);// Delete the node as KEY
	void removeFixUp(RBTNode<T>* &root, RBTNode<T>* node, RBTNode<T>*parent);

	RBTNode<T>* search(RBTNode<T>*node, T key) const;
	void print(RBTNode<T>* node)const;
	void preOrder(RBTNode<T>* tree)const;
	void ascendingOrder(RBTNode<T>* tree)const;
	void descendingOrder(RBTNode<T>* tree)const;

	bool hasPath(RBTNode<T>*& root, vector<T>&arr, T x);

private:
	RBTNode<T>*root;
};

template<class T>		//Constructor
RBTree<T>::RBTree() :root(NULL) {
	root = nullptr;
}
template<class T>		//Destructor
RBTree<T>::~RBTree() {
	destroy(root);
}
template<class T>		//Left
void RBTree<T>::leftRotate(RBTNode<T>* &root, RBTNode<T>* x) {
	RBTNode<T>*y = x->right;
	x->right = y->left;
	if (y->left != NULL)
		y->left->parent = x;

	y->parent = x->parent;
	if (x->parent == NULL)
		root = y;
	else {
		if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
};
template<class T>		//right spin
void RBTree<T>::rightRotate(RBTNode<T>*&root, RBTNode<T>*y) {
	RBTNode<T>*x = y->left;
	y->left = x->right;
	if (x->right != NULL)
		x->right->parent = y;

	x->parent = y->parent;
	if (y->parent == NULL)
		root = x;
	else {
		if  (y == y->parent->right)
			y->parent->right = x;
		else
			y->parent->left = x;
	}
	x->right = y;
	y->parent = x;
};

template<class T> //check if the value already exists in the tree
bool RBTree<T>::ifNodeExists(RBTNode<T>* node, T value){
    if (node == NULL)
        return false;
    if (node->key == value)
        return true;
    // recur on left subtree
    bool res1 = ifNodeExists(node->left, value);
    // recur on right subtree
    bool res2 = ifNodeExists(node->right, value);
    return res1 || res2;
};

template<class T>		//insert
void RBTree<T>::insert(T key){
	RBTNode<T> *x = root;
	bool exists = ifNodeExists(root, key);
	if(exists == true){
		cout << "The value " << key << " already exists in the tree\n";
	}else{
		RBTNode<T>*z = new RBTNode<T>(key, Red, NULL, NULL, NULL);
		insert(root, z);
}
};
template<class T>
void RBTree<T>::insert(RBTNode<T>* &root, RBTNode<T>* node){
	RBTNode<T> *x = root;
	RBTNode<T> *y = NULL;
	while (x != NULL){
		y = x;
		if (node->key > x->key)
		x = x->right;
		else
		x = x->left;
	}
	node->parent = y;
	if(y!=NULL)	{
		if (node->key > y->key)
		y->right = node;
		else
		y->left = node;
	}
	else
	root = node;
	node->color = Red;
	InsertFixUp(root, node);
};
template<class T>
void RBTree<T>::InsertFixUp(RBTNode<T>* &root, RBTNode<T>* node){
	RBTNode<T>*parent;
	parent = node->parent;
	while (node != RBTree::root  && parent->color == Red)	{
		RBTNode<T>*gparent = parent->parent;
		if (gparent->left == parent){
			RBTNode<T>*uncle = gparent->right;
			if (uncle != NULL && uncle->color == Red){
				parent->color = Black;
				uncle->color = Black;
				gparent->color = Red;
				node = gparent;
				parent = node->parent;
			}
			else
			{
				if (parent->right == node){
					leftRotate(root, parent);
					swap(node, parent);
				}
				rightRotate(root, gparent);
				gparent->color = Red;
				parent->color = Black;
				break;
			}
		}
		else
		{
			RBTNode<T>*uncle = gparent->left;
			if (uncle != NULL && uncle->color == Red){
				gparent->color = Red;
				parent->color = Black;
				uncle->color = Black;

				node = gparent;
				parent = node->parent;
			}
			else
			{
				if (parent->left == node){
					rightRotate(root, parent);
					swap(parent, node);
				}
				leftRotate(root, gparent);
				parent->color = Black;
				gparent->color = Red;
				break;
			}
		}
	}
	root->color = Black;
}
template<class T>
//Destroy the red black tree
void RBTree<T>::destroy(RBTNode<T>* &node){
	if (node == NULL)
		return;
	destroy(node->left);
	destroy(node->right);
	delete node;
	node = nullptr;
}

template<class T>
void RBTree<T>::remove(T key){
	RBTNode<T>*deletenode = search(root,key);
	if (deletenode != NULL)
		remove(root, deletenode);
}
template<class T>
void RBTree<T>::remove(RBTNode<T>*&root, RBTNode<T>*node){
	RBTNode<T> *child, *parent;
	RBTColor color;
	//The node left and right of the deleted node is not empty (not the leaf node)
	if (node->left != NULL && node->right != NULL){
		RBTNode<T> *replace = node;
		// Find the successor node (the lowest node of the right subtree of the current node)
		replace = node->right;
		while (replace->left != NULL){
			replace = replace->left;
		}
		//The deleted node is not the root node.
		if (node->parent != NULL){
			if (node->parent->left == node)
				node->parent->left = replace;
			else
				node->parent->right = replace;
		}
		//root node situation
		else
			root = replace;
		//child is the right node of the replacement node, which is the node that needs subsequent adjustment.
		//Because replace is a successor node, it is impossible for him to have a left child.
		//The same reason that the precursor node cannot have the right child node
		child = replace->right;
		parent = replace->parent;
		color = replace->color;

		// The node is replaced by the parent node of the repalce
		if (parent == node)
			parent = replace;
		else
		{
			//Children's node exists
			if (child != NULL)
				child->parent = parent;
			parent->left = child;

			replace->right = node->right;
			node->right->parent = replace;
		}
		replace->parent = node->parent;
		replace->color = node->color;
		replace->left = node->left;
		node->left->parent = replace;
		if (color == Black)
			removeFixUp(root, child, parent);

		delete node;
		return;
	}
	// When the deleted node has only the left (right) node is empty, find the child node of the deleted node
	if (node->left != NULL)
		child = node->left;
	else
		child = node->right;

	parent = node->parent;
	color = node->color;
	if (child)
	{
		child->parent = parent;
	}
	//The deleted node is not the root node
	if (parent)
	{
		if (node == parent->left)
			parent->left = child;
		else
			parent->right = child;
	}
	//The deleted node is the root node
	else
		RBTree::root = child;

	if (color == Black)
	{
		removeFixUp(root, child, parent);
	}
	delete node;

}
template<class T>
void RBTree<T>::removeFixUp(RBTNode<T>* &root, RBTNode<T>* node,RBTNode<T>*parent){
	RBTNode<T>*othernode;
	while ((!node) || node->color == Black && node != RBTree::root){
		if (parent->left == node){
			othernode = parent->right;
			if (othernode->color == Red){
				othernode->color = Black;
				parent->color = Red;
				leftRotate(root, parent);
				othernode = parent->right;
			}
			else
			{
				if (!(othernode->right) || othernode->right->color == Black){
					othernode->left->color=Black;
					othernode->color = Red;
					rightRotate(root, othernode);
					othernode = parent->right;
				}
				othernode->color = parent->color;
				parent->color = Black;
				othernode->right->color = Black;
				leftRotate(root, parent);
				node = root;
				break;
			}
		}
		else
		{
			othernode = parent->left;
			if (othernode->color == Red){
				othernode->color = Black;
				parent->color = Red;
				rightRotate(root, parent);
				othernode = parent->left;
			}
			if ((!othernode->left || othernode->left->color == Black) && (!othernode->right || othernode->right->color == Black)){
				othernode->color = Red;
				node = parent;
				parent = node->parent;
			}
			else
			{
				if (!(othernode->left) || othernode->left->color == Black){
					othernode->right->color = Black;
					othernode->color = Red;
					leftRotate(root, othernode);
					othernode = parent->left;
				}
				othernode->color = parent->color;
				parent->color = Black;
				othernode->left->color = Black;
				rightRotate(root, parent);
				node = root;
				break;
			}
		}
	}
	if (node)
		node->color = Black;
}

template<class T>
RBTNode<T>* RBTree<T>::search(T key){
	RBTNode<T> *x = root;
	RBTNode<T> *z = new RBTNode<T>(key, Red, NULL, NULL, NULL);
	bool inTree = ifNodeExists(root, key);
	if(inTree == false){
		cout << "The following node does not exist in the tree: ";
		return z;
	}
	else
		return search(root, key);
}

template<class T>
RBTNode<T>* RBTree<T>::search(RBTNode<T>*node, T key) const{
	if (node == NULL || node->key == key){
		cout << "The following node does exist in the tree: ";
		return node;
	}else{
		if (key > node->key)
			return search(node->right, key);
		else
			return search(node->left, key);
	}
}

template<class T>
// HEIGHT: LONGEST PATH FROM THAT NODE TO A LEAF
bool RBTree<T>::hasPath(RBTNode<T>*& root, vector<T>& arr, T x){
	if(root == NULL) return false;
	arr.push_back(root->key); //save the nodes value in vector
	if(root->key == x) return true;
	if(hasPath(root->left, arr, x) || hasPath(root->right, arr, x)) return true;
	arr.pop_back();
	return false;
}

template<class T>
void RBTree<T>::printHeight(T x){
	RBTNode<T> *y = root;
	vector<T> arr;
	int h = 0;
	cout << "Printing path: \n";
	if(hasPath(root, arr, x)){
		for(int i = 0; i < arr.size() - 1; ++i){
			cout << arr[i] << " -> ";
			h++;
		}
		cout << arr[arr.size() - 1];
	} else
		cout << "There's no path of " << x << endl;
	cout << "\nHeight of node " << x << " is " << h << endl;
}

template<class T>
void RBTree<T>::printDepth(T x){
	RBTNode<T> *y = root;
	vector<T> arr;
	int d = 0;
	cout << "Printing path: \n";
	if(hasPath(root, arr, x)){
		for(int i = arr.size() - 1; i > 0 ; --i){
			cout << arr[i] << " -> ";
			d++;
		}
		cout << arr[0];
	} else
		cout << "There's no path of " << x << endl;
	cout << "\nDepth of node " << x << " to root is " << d << endl;
}

template<class T>
void RBTree<T>::printLevel(T x){
	RBTNode<T> *y = root;
	vector<T> arr;
	int l = 0;
	cout << "Printing path: \n";
	if(hasPath(root, arr, x)){
		for(int i = arr.size() - 1; i > 0 ; --i){
			cout << arr[i] << " -> ";
			l++;
		}
		cout << arr[0];
	} else
		cout << "There's no path of " << x << endl;
	cout << "\nLevel of node " << x << " is " << l + 1 << endl;
}

template<class T>		// Traverse RB tree
void RBTree<T>::ascendingOrder() {
	if (root == NULL)
		cout << "Empty Redblack tree\n";
	else
		ascendingOrder(root);
};

template<class T>
void RBTree<T>::ascendingOrder(RBTNode<T>* tree)const {
	if (tree != NULL) {
		ascendingOrder(tree->left);
		cout << tree->key << " ";
		ascendingOrder(tree->right);
	}
}

template<class T>      // Traverse RB tree
void RBTree<T>::descendingOrder() {
	if (root == NULL)
		cout << "Empty Redblack tree\n";
	else
		descendingOrder(root);
};

template<class T>
void RBTree<T>::descendingOrder(RBTNode<T>* tree)const {
	if (tree != NULL) {
		descendingOrder(tree->right);
		cout << tree->key << " ";
		descendingOrder(tree->left);
	}
}
