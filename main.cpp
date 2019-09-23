#include"RBTree.h"
#include "TwoThreeTree.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <ctime>
#include <fstream> // Write into file
#include <utility>
#include <time.h>
#include <chrono>

using namespace std;

bool menu(bool programRunning, vector<int> nums, int n){
	bool menu = false;
	int opcMenu = 0;

	int valueToAdd = 0, valueToSearch = 0, valueToDelete = 0, hdlOfNode = 0;

	// Uncomment for RedBlack
	// RBTree<int> tree;
	// for (auto num : nums)
	// 	tree.insert(num);

	// Uncomment for 2-3 Tree
	TwoThreeTree<int> newTree;
	for (auto num : nums)
		newTree.insert23(num);

	while(programRunning == true){
		cout << "\nCHOOSE AN OPTION FROM THE MENU (1 - 10)" << endl;
		cout << "1. Insert a node\n2. Search for a node\n3. Delete a node\n4. Print tree in ascending order\n5. Print tree in descending order\n6. Calculate height of a given node\n7. Calculate depth of a given node\n8. Calculate the level of a given node\n9. Go back\n10. Exit program\n";
			cin >> opcMenu;

		switch(opcMenu){
			case 1:
			{
				cout << "\n ---- INSERT A NODE ---- " << endl;
				cout << "Type in the value to insert: \n";
					cin >> valueToAdd;
				// tree.insert(valueToAdd);
				newTree.insert23(valueToAdd);
				cout << "\n\n";
			}
			break;
			case 2:
			{
				cout << "\n ---- SEARCH FOR A NODE ---- " << endl;
				cout << "Type in the value to search in the tree: \n";
					cin >> valueToSearch;
				int numsToSearch[10];
				numsToSearch[0] = valueToSearch;
				auto start = chrono::steady_clock::now();
				// cout << endl << tree.search(valueToSearch)->key << endl;
				cout << endl << newTree.search23(numsToSearch[0]) << endl;
				auto end = chrono::steady_clock::now();
				cout << "\nElapsed time in milliseconds: \t" << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms";
				cout << "\n\n";
			}
			break;
			case 3:
			{
				cout << "\n ---- DELETE A NODE ---- " << endl;
				cout << "Type in the value to delete: \n";
					cin >> valueToDelete;
				//tree.remove(valueToDelete);
				newTree.delete23(valueToDelete);
				cout << "\n\n";
			}
			break;
			case 4:
			{
				cout << "\n ---- PRINT IN ASCENDING ORDER ---- " << endl;
				// tree.ascendingOrder();
				newTree.printAsc();
				cout << "\n\n";
			}
			break;
			case 5:
			{
				cout << "\n ---- PRINT IN DESCENDING ORDER ---- " << endl;
				// tree.descendingOrder();
				newTree.printDesc();
				cout << "\n\n";
			}
			break;
			case 6:
			{
				cout << "\n ---- CALCULATE HEIGHT ---- " << endl;
				cout << "Type in the node you want to calculate the height of: \n";
					cin >> hdlOfNode;
				// tree.printHeight(hdlOfNode);
				newTree.printHeight23(hdlOfNode);
				hdlOfNode = 0;
				cout << "\n\n";
			}
			break;
			case 7:
			{
				cout << "\n ---- CALCULATE DEPTH ---- " << endl;
				cout << "Type in the node you want to calculate the depth of: \n";
					cin >> hdlOfNode;
				// tree.printDepth(hdlOfNode);
				newTree.printDepth23(hdlOfNode);
				hdlOfNode = 0;
				cout << "\n\n";
			}
			break;
			case 8:
			{
				cout << "\n ---- CALCULATE LEVEL ---- " << endl;
				cout << "Type in the node you want to calculate the height of: \n";
					cin >> hdlOfNode;
				// tree.printLevel(hdlOfNode);
				newTree.printLevel23(hdlOfNode);
				hdlOfNode = 0;
				cout << "\n\n";
			}
			break;
			case 9:
			{
				cout << "\n ---- GO BACK ---- " << endl;
				menu = true;
				cout << "\n\n";
				return programRunning = false;
			}
			break;
			case 10:
			{
				cout << "\n ---- EXIT PROGRAM ---- " << endl;
				exit(0);
			}
			break;
		}
	}
	return programRunning;
}

void writeIntoFile(vector<int> nums, int n){
  int i;
  ofstream file_list;
  file_list.open("listElementsTree.txt");
  if (file_list.is_open()){
    for (i = 0; i < n; ++i){ //final state
      file_list << nums[i] << endl;
    }
  	file_list.close();
  }
}

int main(){
	int opcTree = 0;
	bool programRunning = true;

	srand(static_cast<unsigned int>(time(NULL)));
	size_t const n = 100000;
	vector<int> nums(n);

	//make vector
	for (size_t i = 0; i < n; ++i)
		nums[i] = static_cast<int>(i);

	//shuffle
	for (size_t i = n - 1; i > 0; --i)
		swap(nums[i], nums[static_cast<size_t>(rand()) % (i + 1)]);

	writeIntoFile(nums, n);

	while(programRunning == true){
		cout << "CHOOSE A TREE TO CREATE (1-5): " << endl;
		cout << "1. AVL Tree\n2. B Tree\n3. Redblack Tree\n4. 2-3 Tree\n5. Exit program" << endl;
		cin >> opcTree;

		switch(opcTree){
			case 1:
			{
				cout << "\n ---- AVL TREE ----\n";
				menu(programRunning, nums, n);
			}
			break;
			case 2:
			{
				cout << "\n ---- B TREE ----\n";
				menu(programRunning, nums, n);
			}
			break;
			case 3:
			{
				cout << "\n ---- REDBLACK TREE ----\n";
				menu(programRunning, nums, n);
			}
			break;
			case 4:
			{
				cout << "\n ---- 2-3 TREE ----\n";
				menu(programRunning, nums, n);
			}
			break;
			case 5:
			{
				cout << "\n ----  EXIT PROGRAM ---- \n";
				exit(0);
			}
		}
	}
	return 0;
}
