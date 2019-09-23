#include "TwoThreeNode.h"
#include <iomanip>
#include <queue>
#include <iostream>
#include <vector>

using namespace std;

template <class T>
class TwoThreeTree {

protected:
  TwoThreeNode<T> * root = nullptr;
  std::vector<T> leafLevel;

public:
  TwoThreeTree() { }
  ~TwoThreeTree();

  bool empty();

  void clear();
  void clear(TwoThreeNode<T> * node);

  TwoThreeNode<T> * getRoot() const;
  void setRoot(const T info);
  void setRoot(TwoThreeNode<T> * node);
  bool isRoot(TwoThreeNode<T> * node);

  void insert23(T info);
  void insert23(TwoThreeNode<T> * info);
  void insert23(TwoThreeNode<T> * parent, TwoThreeNode<T> * info);
  void insert23(TwoThreeNode<T> * parent, T info);

  void printAsc(TwoThreeNode<T> * node, int level);
  void printAsc();

  void printDesc(TwoThreeNode<T> * node, int level);
  void printDesc();

  void assignRoot(TwoThreeNode<T>* root);
  bool isTwoTree ();
  bool isTwoTree(TwoThreeNode<T>* node);

  void redistributeChildren(TwoThreeNode<T>* container, TwoThreeNode<T>* node1, TwoThreeNode<T>* node2);
  void divide(TwoThreeNode<T>* container);
  bool checkTwoNode(TwoThreeNode<T>* node);
  bool checkThreeNode(TwoThreeNode<T>* node);
  bool freeChildren(TwoThreeNode<T>* node);

  TwoThreeNode<T>* searchNode(const T info, TwoThreeNode<T> * node);
  bool search23(const T info);

  TwoThreeNode<T>* findNodeToDelete(TwoThreeNode<T>*, T info);
  bool deleteNode(TwoThreeNode<T>* node);
  bool delete23(T info);
  void fix(TwoThreeNode<T>* node);
  TwoThreeNode<T>* getSucesorInorder(TwoThreeNode<T>* node);

  void getleafLevel(TwoThreeNode<T>* node);
  bool getKeysNode(TwoThreeNode<T>* node);
  bool getChildrenNode(TwoThreeNode<T>* node);
  bool findNode(TwoThreeNode<T>*, T info);

  void isLeaf() ;
  bool isLeaf(TwoThreeNode<T> * node) ;

  void ancestor(TwoThreeNode<T> * node) const;

  int getHeight() const;
  int getHeight(TwoThreeNode<T> * node) const ;

  int getDepth() const;
  int getDepth(TwoThreeNode<T> * node) const;

  int getLevel() const;
  int getLevel(TwoThreeNode<T> * node) const;

  void order(T a[], int N);

  void printHeight23(T x);
  void printDepth23(T x);
  void printLevel23(T x);
  bool hasPath(TwoThreeNode<T>*& root, vector<T>&arr, T x);

};

template <class T>
TwoThreeTree<T>::~TwoThreeTree() {
  clear();
}

template <class T>
bool TwoThreeTree<T>::empty() {
  return root == nullptr;
}

template <class T>
void TwoThreeTree<T>::clear() {
  clear(root);
}

template <class T>
void TwoThreeTree<T>::clear(TwoThreeNode<T> * node) {
  if (node) {
    clear(node->getLeft());
    clear(node->getRight());
    delete node;
  }
}

template <class T>
TwoThreeNode<T> * TwoThreeTree<T>::getRoot() const {
  return root;
}

template <class T>
void TwoThreeTree<T>::setRoot(const T info) {
  TwoThreeNode<T> * node = new TwoThreeNode<T>(info);
  setRoot(node);
}

template <class T>
void TwoThreeTree<T>::setRoot(TwoThreeNode<T> * node) {
  if (!empty()) {
    node->setLeft(root);
    root->setParent(node);
    root = node;
  }
  else {
    root = node;
  }
}

template <class T>
bool TwoThreeTree<T>::isRoot(TwoThreeNode<T> * node) {
  return node == this->root;
}

template <class T>
void TwoThreeTree<T>::insert23(T info) {
  insert23(this->root, info);
}

template <class T>
void TwoThreeTree<T>::insert23(TwoThreeNode<T> * info) {
  insert23(this->root, info);
}

template <class T>
void TwoThreeTree<T>::assignRoot(TwoThreeNode<T>* node) {
  root = node;
}

template <class T>
void TwoThreeTree<T>::redistributeChildren(TwoThreeNode<T>* container, TwoThreeNode<T>* node1, TwoThreeNode<T>* node2) {
  node1->setLeft(container->getLeft());
  node1->setRight(container->getMiddle());
  node2->setLeft(container->getTemp());
  node2->setRight(container->getRight());
  node1->getLeft()->setParent(node1);
  node1->getRight()->setParent(node1);
  node2->getLeft()->setParent(node2);
  node2->getRight()->setParent(node2);
}

template <class T>
void TwoThreeTree<T>::divide(TwoThreeNode<T>* container) {

  if(isRoot(container)) {
    TwoThreeNode<T>* newRoot = new TwoThreeNode<T>(container->getTempMiddle());
    assignRoot(newRoot);
    TwoThreeNode<T>* node1 = new TwoThreeNode<T>(container->getSmall());
    TwoThreeNode<T>* node2 = new TwoThreeNode<T>(container->getBig());
    if(container->getTemp()!=nullptr)
      redistributeChildren(container, node1, node2);
    newRoot->setLeft(node1);
    newRoot->setRight(node2);
    newRoot->getLeft()->setParent(newRoot);
    newRoot->getRight()->setParent(newRoot);
    delete container;
  }
  else if(container->getParent() != nullptr) {
    TwoThreeNode<T>* parent = container->getParent();
    if(parent->isFull()) {
      parent->setInfoMiddle(container->getTempMiddle());
      if(parent->getRight() == container) {
        TwoThreeNode<T>* node1 = new TwoThreeNode<T>(container->getSmall());
        TwoThreeNode<T>* node2 = new TwoThreeNode<T>(container->getBig());
        if(container->getTemp()!=nullptr)
          redistributeChildren(container, node1, node2);
        parent->setRight(node2);
        parent->setTemp(node1);
        parent->getRight()->setParent(parent);
        parent->getTemp()->setParent(parent);
        delete container;
      }
      else if(parent->getLeft() == container) {
        TwoThreeNode<T>* node1 = new TwoThreeNode<T>(container->getSmall());
        TwoThreeNode<T>* node2 = new TwoThreeNode<T>(container->getBig());
        if(container->getTemp()!=nullptr)
          redistributeChildren(container, node1, node2);
        parent->setLeft(node1);
        parent->setTemp(parent->getMiddle());
        parent->setMiddle(node2);
        parent->getLeft()->setParent(parent);
        parent->getMiddle()->setParent(parent);
        parent->getTemp()->setParent(parent);
        delete container;

      }
      else {
        TwoThreeNode<T>* node1 = new TwoThreeNode<T>(container->getSmall());
        TwoThreeNode<T>* node2 = new TwoThreeNode<T>(container->getBig());
        if(container->getTemp()!=nullptr)
          redistributeChildren(container, node1, node2);
        parent->setMiddle(node1);
        parent->setTemp(node2);
        parent->getMiddle()->setParent(parent);
        parent->getTemp()->setParent(parent);
        delete container;
      }
      divide(parent);
    }
    else {
      parent->setInfo(container->getTempMiddle());
      if(parent->getRight() == container)
      {
        TwoThreeNode<T>* node1 = new TwoThreeNode<T>(container->getSmall());
        TwoThreeNode<T>* node2 = new TwoThreeNode<T>(container->getBig());
        if(container->getTemp()!=nullptr)
          redistributeChildren(container, node1, node2);
        parent->setRight(node2);
        parent->setMiddle(node1);
        parent->getRight()->setParent(parent);
        parent->getMiddle()->setParent(parent);
        delete container;
      }
      else if(parent->getLeft() == container) {
        TwoThreeNode<T>* node1 = new TwoThreeNode<T>(container->getSmall());
        TwoThreeNode<T>* node2 = new TwoThreeNode<T>(container->getBig());
        if(container->getTemp()!=nullptr)
          redistributeChildren(container, node1, node2);
        parent->setLeft(node1);
        parent->setMiddle(node2);
        parent->getLeft()->setParent(parent);
        parent->getMiddle()->setParent(parent);
        delete container;
      }
      if(parent->hasThreeKeys())
        divide(parent);
    }
  }
}

template <class T>
bool TwoThreeTree<T>:: checkTwoNode(TwoThreeNode<T>* node) {
  if((node->hasLower() && !node->hasHigher()) || (!node->hasLower() && node->hasHigher()))
    return true;
  else
    return false;
}

template <class T>
bool TwoThreeTree<T>:: checkThreeNode(TwoThreeNode<T>* node) {
  if(node->hasLower() && node->hasHigher())
    return true;
  else
    return false;
}

template <class T>
bool TwoThreeTree<T>::freeChildren(TwoThreeNode<T>* node) {
  if(node->getLeft() == nullptr || node->getMiddle() == nullptr || node->getRight() == nullptr)
    return true;
  else
    return false;
}

template <class T>
void TwoThreeTree<T>::insert23(TwoThreeNode<T> * parent, T info) {
  TwoThreeNode<T>* container = new TwoThreeNode<T>();
  if(root == nullptr)
  {
    assignRoot(new TwoThreeNode<T>(info));
    return;
  }
  container = searchNode(info, root);
  if(checkTwoNode(container))
  {
    container->setInfo(info);
    container->deleteTempMiddle();
  }
  else if(checkThreeNode(container))
  {
    container->setInfoMiddle(info);
    divide(container);
  }
}

template <class T>
bool TwoThreeTree<T>::search23(const T info) {
  bool found;

  if (searchNode(info, root) != nullptr) {
    found = true;
  }
  else {
    found = false;
  }

  return found;

}

template <class T>
TwoThreeNode<T>* TwoThreeTree<T>::searchNode(const T info, TwoThreeNode<T> * node) {
  if(node == nullptr)
    return nullptr;
  if(isLeaf(node))
    return node;
  else if(checkTwoNode(node)) {
    if(info <= node->getSmall())
      return searchNode(info, node->getLeft());
    else
      return searchNode(info, node->getRight());
  }
  else if(checkThreeNode(node)) {
    if(info <= node->getSmall())
      return searchNode(info, node->getLeft());
    else if(info > node->getBig())
      return searchNode(info, node->getRight());
    else
      return searchNode(info, node->getMiddle());
  }
  return node;
}

template <class T>
void TwoThreeTree<T>::printAsc() {
  printAsc(root, 0);
  cout << "  " << endl;
}

template <class T>
void TwoThreeTree<T>::printAsc(TwoThreeNode<T> * node, int lv) {
  if(node == nullptr)
    return;
  if(isLeaf(node)) {
    if(checkTwoNode(node)) {
      cout << node->getSmall() << "  "<< flush;
    }
    else if(checkThreeNode(node)) {
      cout << node->getSmall() << "  " << node->getBig();
    }
  }
  else if(checkTwoNode(node)) {
    printAsc(node->getLeft(), lv);
    cout << node->getSmall() << "  "<< flush;
    printAsc(node->getRight(), lv);
  }
  else if(checkThreeNode(node)) {
    printAsc(node->getLeft(), lv);
    cout << node->getSmall() << "  "<< flush;
    printAsc(node->getMiddle(), lv);
    cout << node->getBig() << "  "<< flush;
    printAsc(node->getRight(), lv);
  }
}

template <class T>
void TwoThreeTree<T>::printDesc() {
  printDesc(root, 0);
  cout << "  " << endl;
}

template <class T>
void TwoThreeTree<T>::printDesc(TwoThreeNode<T> * node, int lv) {
  if(node == nullptr)
    return;
  if(isLeaf(node)) {
    if(checkTwoNode(node)) {
      cout << node->getSmall() << " "<< flush;
    }
    else if(checkThreeNode(node)) {
      cout << node->getBig() << " " << node->getSmall() << " ";
    }
  }
  else if(checkTwoNode(node)) {
    printDesc(node->getRight(), lv);
    cout << node->getSmall() << " "<< flush;
    printDesc(node->getLeft(), lv);
  }
  else if(checkThreeNode(node)) {
    printDesc(node->getRight(), lv);
    cout << node->getBig() << " "<< flush;
    printDesc(node->getMiddle(), lv);
    cout << node->getSmall() << " "<< flush;
    printDesc(node->getLeft(), lv);
  }
}


template <class T>
void TwoThreeTree<T>::fix(TwoThreeNode<T>* node) {
  if(isRoot(node)) {
    assignRoot(node->getMiddle());
    delete node;
  }
  else {
    bool threeKeys = false;
    TwoThreeNode<T>* parent = node->getParent();
    if(checkTwoNode(parent)) {
      TwoThreeNode<T>* sibiling = new TwoThreeNode<T>();
      if(parent->getRight() == node)
        sibiling = parent->getLeft();
      else
        sibiling = parent->getRight();
      if(parent->getRight() == node) {

        if(checkThreeNode(parent->getLeft())){
          threeKeys = true;
          T sibilingLower = sibiling->getSmall();
          T sibilingHigher = sibiling->getBig();
          T parentVal = parent->getSmall();
          T keys[3] = {sibilingLower,sibilingHigher,parentVal};
          order(keys,3);
          T low = keys[0];
          T mid = keys[1];
          T high = keys[2];
          node->setInfo(high);
          parent->deleteKeys();
          parent->setInfo(mid);
          sibiling->deleteKeys();
          sibiling->setInfo(low);


          if(!isLeaf(node)) {
            node->setRight(node->getMiddle());
            node->setMiddle(nullptr);
            node->setLeft(sibiling->getRight());
            node->getLeft()->setParent(node);
            sibiling->setRight(sibiling->getMiddle());
            sibiling->setMiddle(nullptr);
          }
        }
      }
      else {
        if(checkThreeNode(parent->getRight()))
        {
          threeKeys = true;
          T sibilingLower = sibiling->getSmall();
          T sibilingHigher = sibiling->getBig();
          T parentVal = parent->getSmall();
          T keys[3] = {sibilingLower,sibilingHigher,parentVal};
          order(keys,3);
          T low = keys[0];
          T mid = keys[1];
          T high = keys[2];
          node->setInfo(low);
          parent->deleteKeys();
          parent->setInfo(mid);
          sibiling->deleteKeys();
          sibiling->setInfo(high);

          if(!isLeaf(node)) {
            node->setLeft(node->getMiddle());
            node->setMiddle(nullptr);
            node->setRight(sibiling->getLeft());
            node->getRight()->setParent(node);
            sibiling->setLeft(sibiling->getMiddle());
            sibiling->setMiddle(nullptr);
          }
        }
      }
    }
    else if(checkThreeNode(parent)) {
      TwoThreeNode<T>* sibiling = new TwoThreeNode<T>();
      if(parent->getRight() == node) {
        if(checkThreeNode(parent->getMiddle())) {
          threeKeys = true;
          sibiling = parent->getMiddle();
          node->setInfo(parent->getBig());
          parent->setBig(sibiling->getBig());
          sibiling->deleteBig();
          if(!isLeaf(node)) {
            node->setRight(node->getMiddle());
            node->setLeft(sibiling->getRight());
            node->getLeft()->setParent(node);
            sibiling->setRight(sibiling->getMiddle());
            sibiling->setMiddle(nullptr);
          }
        }
      }
      else if(parent->getMiddle() == node) {
        if(checkThreeNode(parent->getLeft())) {
          threeKeys = true;
          sibiling = parent->getLeft();
          node->setInfo(parent->getSmall());
          parent->setSmall(sibiling->getBig());
          sibiling->deleteBig();
          if(!isLeaf(node)) {
            node->setRight(node->getMiddle());
            node->setLeft(sibiling->getRight());
            node->getLeft()->setParent(node);
            sibiling->setRight(sibiling->getMiddle());
            sibiling->setMiddle(nullptr);
          }
        }
      }
      else {
        if(checkThreeNode(parent->getMiddle())) {
          threeKeys = true;
          sibiling = parent->getMiddle();
          node->setInfo(parent->getSmall());
          parent->setSmall(sibiling->getSmall());
          sibiling->changeBigToSmall();
          if(!isLeaf(node)) {
            node->setLeft(node->getMiddle());
            node->setRight(sibiling->getLeft());
            node->getRight()->setParent(node);
            sibiling->setLeft(sibiling->getMiddle());
            sibiling->setMiddle(nullptr);
          }
        }
      }
    }
    if(!threeKeys) {
      TwoThreeNode<T>* sibiling = new TwoThreeNode<T>();
      if(checkTwoNode(parent)) {
        if(parent->getRight() == node) {
          sibiling = parent->getLeft();
          sibiling->setInfo(parent->getSmall());

          if(!isLeaf(node)) {
            sibiling->setMiddle(sibiling->getRight());
            sibiling->setRight(node->getMiddle());
          }
          parent->setMiddle(sibiling);
          parent->getMiddle()->setParent(parent);
          parent->setLeft(nullptr);
          parent->setRight(nullptr);
          parent->deleteKeys();
          delete node;
        }
        else {
          sibiling = parent->getRight();
          sibiling->setInfo(parent->getSmall());
          if(!isLeaf(node))
          {
            sibiling->setMiddle(sibiling->getLeft());
            sibiling->setLeft(node->getMiddle());
            sibiling->getLeft()->setParent(sibiling);
          }
          parent->setMiddle(sibiling);
          parent->getMiddle()->setParent(parent);
          parent->setLeft(nullptr);
          parent->setRight(nullptr);
          parent->deleteKeys();
          delete node;
        }
      }
      else if(checkThreeNode(parent)) {
        if(parent->getRight() == node) {
          sibiling = parent->getMiddle();
          sibiling->setInfo(parent->getBig());
          if(!isLeaf(node)) {
            sibiling->setMiddle(sibiling->getRight());
            sibiling->setRight(node->getMiddle());
            sibiling->getRight()->setParent(sibiling);
          }
          parent->setRight(sibiling);
          parent->getRight()->setParent(parent);
          parent->setMiddle(nullptr);
          parent->deleteBig();
          delete node;
        }
        else if(parent->getMiddle() == node) {
          sibiling = parent->getLeft();
          sibiling->setInfo(parent->getSmall());
          if(!isLeaf(node)) {
            sibiling->setMiddle(sibiling->getRight());
            sibiling->setRight(node->getMiddle());
            sibiling->getRight()->setParent(sibiling);
          }
          parent->setLeft(sibiling);
          parent->getLeft()->setParent(parent);
          parent->setMiddle(nullptr);
          parent->deleteSmall();
          parent->changeBigToSmall();
          delete node;
        }
        else {
          sibiling = parent->getMiddle();
          sibiling->setInfo(parent->getSmall());
          if(!isLeaf(node)) {
            sibiling->setMiddle(sibiling->getLeft());
            sibiling->setLeft(node->getMiddle());
            sibiling->getLeft()->setParent(sibiling);
          }
          parent->setLeft(sibiling);
          parent->getLeft()->setParent(parent);
          parent->setMiddle(nullptr);
          parent->deleteSmall();
          parent->changeBigToSmall();
          delete node;
        }
      }
      if(parent->noKeys()) {
        sibiling->setParent(parent);
        fix(parent);
      }
    }
  }
}

template <class T>
bool TwoThreeTree<T>::delete23(T info) {
  TwoThreeNode<T>* node = new TwoThreeNode<T>();
  node = findNodeToDelete(root, info);
  if(node) {
    TwoThreeNode<T>* leafNode = new TwoThreeNode<T>();
    if(!isLeaf(node)) {
      leafNode = getSucesorInorder(node);
      T swapVal = leafNode->getSmall();
      node->setSmall(swapVal);
    }
    else {
      if(node->getBig() == info) {
        node->deleteBig();
        return true;
      }
    }
    leafNode->deleteSmall();
    if(leafNode->noKeys()) {
      fix(leafNode);
    }
    return true;
  }
  else
    return false;
}

template <class T>
TwoThreeNode<T>* TwoThreeTree<T>::getSucesorInorder(TwoThreeNode<T>* node) {
  if (node) {
    TwoThreeNode<T> * workingNode = node->getLeft();
    if(workingNode){
      while (workingNode->getRight() != nullptr) {
        workingNode = workingNode->getRight();
      }
      return workingNode;
    }
    return nullptr;

  } else {
    return nullptr;
  }
}

template <class T>
TwoThreeNode<T>* TwoThreeTree<T>::findNodeToDelete(TwoThreeNode<T>* node, T info) {
  if(node == nullptr)
    return nullptr;
  if(isLeaf(node)) {
    if(checkTwoNode(node)) {
      if(node->getSmall() == info){
        return node;
      }
    }
    else if(checkThreeNode(node)) {
      if(node->getSmall() == info || node->getBig() == info) {
        return node;
      }
    }
    return nullptr;
  }
  else if(checkTwoNode(node)) {
    if(info == node->getSmall()) {
      return node;
    }

    if(info < node->getSmall())
      return findNodeToDelete(node->getLeft(), info);
    else
      return findNodeToDelete( node->getRight(), info);
  }
  else if(checkThreeNode(node))
{
    if(node->getSmall() == info || node->getBig() == info) {
      return node;
    }
    if(info < node->getSmall())
      return findNodeToDelete(node->getLeft(), info);
    else if(info > node->getBig())
      return findNodeToDelete(node->getRight(), info);
    else
      return findNodeToDelete(node->getMiddle(), info);
  }
  return nullptr;
}

template <class T>
bool TwoThreeTree<T>::findNode(TwoThreeNode<T>* node, T info) {
  if(node == nullptr)
    return false;
  if(isLeaf(node)) {
    if(checkTwoNode(node)) {
      if(node->getSmall() == info)
      {
        return true;
      }
    }
    else if(checkThreeNode(node)) {
      if(node->getSmall() == info || node->getBig() == info) {
        return true;
      }
    }
    return false;
  }
  else if(checkTwoNode(node)) {
    if(info == node->getSmall()) {
      return true;
    }

    if(info < node->getSmall())
      return findNode(node->getLeft(), info);
    else
      return findNode( node->getRight(), info);
  }
  else if(checkThreeNode(node)) {
    if(node->getSmall() == info || node->getBig() == info) {
      return true;
    }
    if(info < node->getSmall())
      return findNode(node->getLeft(), info);
    else if(info > node->getBig())
      return findNode(node->getRight(), info);
    else
      return findNode(node->getMiddle(), info);
  }
  return false;
}

template <class T>
bool TwoThreeTree<T>::isTwoTree() {
  return isTwoTree(root);
}

template <class T>
bool TwoThreeTree<T>::isTwoTree(TwoThreeNode<T>* node) {
  leafLevel.clear();
  getleafLevel(root);
  T cmp = leafLevel[0];
  bool leafs = true;
  for(int i=1; i<leafLevel.size(); i++) {
    if(leafLevel[i] != cmp)
      leafs = false;
  }
  return leafs;
}

template <class T>
void TwoThreeTree<T>::getleafLevel(TwoThreeNode<T>* node) {
  if(node == nullptr)
    return;
  if(isLeaf(node)) {
    leafLevel.push_back(getLevel(node));
  }
  else if(checkTwoNode(node)) {
    getleafLevel(node->getLeft());
    getleafLevel(node->getRight());
  }
  else if(checkThreeNode(node)) {
    getleafLevel(node->getLeft());
    getleafLevel(node->getMiddle());
    getleafLevel(node->getRight());
  }
}

template <class T>
void TwoThreeTree<T>::isLeaf() {
  isLeaf(root);
}

template <class T>
bool TwoThreeTree<T>::isLeaf(TwoThreeNode<T> * node) {
  if(node->getLeft() == nullptr && node->getMiddle() == nullptr && node->getRight() == nullptr)
    return true;
  else
    return false;
}

template <class T>
void TwoThreeTree<T>::ancestor(TwoThreeNode<T> * node) const {
  if (node) {
    cout << *node << " -> ";
    ancestor(node->getParent());
  }
}

template <class T>
int TwoThreeTree<T>::getHeight() const {
  return getHeight(root);
}

template <class T>
int TwoThreeTree<T>::getHeight(TwoThreeNode<T> * node) const {
  if (!node)
    return -1;
  return 1 + std::max(getHeight(node->getLeft()), getHeight(node->getRight()));
}

template <class T>
int TwoThreeTree<T>::getDepth() const {
  return getDepth(root);
}

template <class T>
int TwoThreeTree<T>::getDepth(TwoThreeNode<T> * node) const {
  if (node == nullptr) {
    return 0;
  }
  else {
    return getDepth(node->getParent())+1;
  }
}

template <class T>
int TwoThreeTree<T>::getLevel() const {
  return getLevel(root);
}

template <class T>
int TwoThreeTree<T>::getLevel(TwoThreeNode<T> * node) const {
  int level = 0;
  while (node != nullptr && node->getParent() != nullptr) {
    level++;
    node = node->getParent();
  }
  return level;
}

template <class T>
void TwoThreeTree<T>::order(T a[], int N) {

  int i, j, flag = 1;
  int temp;
  int numLength = N;
  for(i = 1; (i <= numLength) && flag; i++) {
    flag = 0;
    for (j=0; j < (numLength -1); j++) {
      if (a[j+1] < a[j]) {
        temp = a[j];
        a[j] = a[j+1];
        a[j+1] = temp;
        flag = 1;
      }
    }
  }
  return;
}

template<class T>
// HEIGHT: LONGEST PATH FROM THAT NODE TO A LEAF
bool TwoThreeTree<T>::hasPath(TwoThreeNode<T>*& root, vector<T>& arr, T x){
	if(root == NULL) return false;
	arr.push_back(x); //save the nodes value in vector
	if(x == x) return true;
	if(hasPath(root->left, arr, x) || hasPath(root->right, arr, x)) return true;
	arr.pop_back();
	return false;
}

template<class T>
void TwoThreeTree<T>::printHeight23(T x){
	TwoThreeNode<T> *y = root;
	vector<T> arr;
	int h = 1;
	cout << "Printing path: \n";
	if(hasPath(root, arr, x)){
		for(int i = 0; i < arr.size() - 1; ++i){
			cout << arr[i] << " -> ";
			h = (h + 4 * 3) * 4;
		}
		cout << arr[arr.size() - 1];
	} else
		cout << "There's no path of " << x << endl;
	cout << "\nHeight of node " << x << " is " << h << endl;
}

template<class T>
void TwoThreeTree<T>::printDepth23(T x){
	TwoThreeNode<T> *y = root;
	vector<T> arr;
	int d = 1;
	cout << "Printing path: \n";
	if(hasPath(root, arr, x)){
		for(int i = arr.size() - 1; i > 0 ; --i){
			cout << arr[i] << " -> ";
			d = (d + 4) * 5;
		}
		cout << arr[0];
	} else
		cout << "There's no path of " << x << endl;
	cout << "\nDepth of node " << x << " to root is " << d << endl;
}

template<class T>
void TwoThreeTree<T>::printLevel23(T x){
	TwoThreeNode<T> *y = root;
	vector<T> arr;
	int l = 1;
	cout << "Printing path: \n";
	if(hasPath(root, arr, x)){
		for(int i = arr.size() - 1; i > 0 ; --i){
			cout << arr[i] << " -> ";
			l = (l + 4) * 5;
		}
		cout << arr[0];
	} else
		cout << "There's no path of " << x << endl;
	cout << "\nLevel of node " << x << " is " << l + 1 << endl;
}
