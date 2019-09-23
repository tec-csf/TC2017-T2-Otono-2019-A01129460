/********************
**** Daniela Vignau | Ricardo Sandoval ******
****    A01021689   |  A01129460             ******
********************/
#include <algorithm>
#include <iostream>

using namespace std;

/* AVL node */
template <class T>
class AVLnode {
public:
    T key;
    int balance;
    AVLnode *left, *right, *parent;

    AVLnode(T k, AVLnode *p) : key(k), balance(0), parent(p),
                        left(NULL), right(NULL) {}

    ~AVLnode() {
        delete left;
        delete right;
    }
};

/* AVL tree */
template <class T>
class AVLtree {
public:
    AVLtree(void);
    ~AVLtree(void);
    bool insert(T key);
    void deleteKey(const T key);
    void printBalance();
    void ordenarAsc();
    void ordenarDes();
    int calculaAltura();
    AVLnode<T>* buscarNodo(const T key);
    int calculaAlturaDeNodo(const T key);
    int nivelDeNodo(const T key);

private:
    AVLnode<T>* root;

    AVLnode<T>* rotateLeft( AVLnode<T> *a );
    AVLnode<T>* rotateRight( AVLnode<T> *a );
    AVLnode<T>* rotateLeftThenRight( AVLnode<T> *n );
    AVLnode<T>* rotateRightThenLeft( AVLnode<T> *n );
    void rebalance( AVLnode<T> *n );
    int height( AVLnode<T> *n );
    void setBalance( AVLnode<T> *n );
    void printBalance( AVLnode<T> *n );
    void clearNode( AVLnode<T> *n );
    void ascendente( AVLnode<T> *n );
    void descendente( AVLnode<T> *n );
    int calculaAltura( AVLnode<T> *n );
    int calculaAlturaDeNodo( AVLnode<T> *n, const T key );
    int nivelDeNodo(AVLnode<T> *n, const T key);
    AVLnode<T>* buscarNodo(AVLnode<T> *n, const T key);
};

/* AVL class definition */
template <class T>
void AVLtree<T>::rebalance(AVLnode<T> *n) {
    setBalance(n);

    if (n->balance == -2) {
        if (height(n->left->left) >= height(n->left->right))
            n = rotateRight(n);
        else
            n = rotateLeftThenRight(n);
    }
    else if (n->balance == 2) {
        if (height(n->right->right) >= height(n->right->left))
            n = rotateLeft(n);
        else
            n = rotateRightThenLeft(n);
    }

    if (n->parent != NULL) {
        rebalance(n->parent);
    }
    else {
        root = n;
    }
}

template <class T>
AVLnode<T>* AVLtree<T>::rotateLeft(AVLnode<T> *a) {
    AVLnode<T> *b = a->right;
    b->parent = a->parent;
    a->right = b->left;

    if (a->right != NULL)
        a->right->parent = a;

    b->left = a;
    a->parent = b;

    if (b->parent != NULL) {
        if (b->parent->right == a) {
            b->parent->right = b;
        }
        else {
            b->parent->left = b;
        }
    }

    setBalance(a);
    setBalance(b);
    return b;
}

template <class T>
AVLnode<T>* AVLtree<T>::rotateRight(AVLnode<T> *a) {
    AVLnode<T> *b = a->left;
    b->parent = a->parent;
    a->left = b->right;

    if (a->left != NULL)
        a->left->parent = a;

    b->right = a;
    a->parent = b;

    if (b->parent != NULL) {
        if (b->parent->right == a) {
            b->parent->right = b;
        }
        else {
            b->parent->left = b;
        }
    }

    setBalance(a);
    setBalance(b);
    return b;
}

template <class T>
AVLnode<T>* AVLtree<T>::rotateLeftThenRight(AVLnode<T> *n) {
    n->left = rotateLeft(n->left);
    return rotateRight(n);
}

template <class T>
AVLnode<T>* AVLtree<T>::rotateRightThenLeft(AVLnode<T> *n) {
    n->right = rotateRight(n->right);
    return rotateLeft(n);
}

template <class T>
int AVLtree<T>::height(AVLnode<T> *n) {
    if (n == NULL)
        return -1;
    return 1 + std::max(height(n->left), height(n->right));
}

template <class T>
void AVLtree<T>::setBalance(AVLnode<T> *n) {
    n->balance = height(n->right) - height(n->left);
}

template <class T>
void AVLtree<T>::printBalance(AVLnode<T> *n) {
    if (n != NULL) {
        printBalance(n->left);
        std::cout << n->balance << " ";
        printBalance(n->right);
    }
}

template <class T>
AVLtree<T>::AVLtree(void) : root(NULL) {}

template <class T>
AVLtree<T>::~AVLtree(void) {
    delete root;
}

template <class T>
bool AVLtree<T>::insert(T key) {
    if (root == NULL) {
        root = new AVLnode<T>(key, NULL);
    }
    else {
        AVLnode<T>
            *n = root,
            *parent;

        while (true) {
            if (n->key == key)
                return false;

            parent = n;

            bool goLeft = n->key > key;
            n = goLeft ? n->left : n->right;

            if (n == NULL) {
                if (goLeft) {
                    parent->left = new AVLnode<T>(key, parent);
                }
                else {
                    parent->right = new AVLnode<T>(key, parent);
                }

                rebalance(parent);
                break;
            }
        }
    }

    return true;
}

template <class T>
void AVLtree<T>::deleteKey(const T delKey) {
    if (root == NULL)
        return;

    AVLnode<T>
        *n       = root,
        *parent  = root,
        *delNode = NULL,
        *child   = root;

    while (child != NULL) {
        parent = n;
        n = child;
        child = delKey >= n->key ? n->right : n->left;
        if (delKey == n->key)
            delNode = n;
    }

    if (delNode != NULL) {
        delNode->key = n->key;

        child = n->left != NULL ? n->left : n->right;

        if (root->key == delKey) {
            root = child;
        }
        else {
            if (parent->left == n) {
                parent->left = child;
            }
            else {
                parent->right = child;
            }

            rebalance(parent);
        }
    }
}

template <class T>
void AVLtree<T>::printBalance() {
    printBalance(root);
    std::cout << std::endl;
}


template <class T>
void AVLtree<T>::ordenarAsc(){
    ascendente(root);
}

template <class T>
void AVLtree<T>::ascendente(AVLnode<T> *n){
    if(n != NULL){
        ascendente(n->left);
        cout << n->key << " ";
        ascendente(n->right);
    }
}

template <class T>
void AVLtree<T>::ordenarDes(){
    descendente(root);
}

template <class T>
void AVLtree<T>::descendente(AVLnode<T> *n){
    if(n != NULL)
     {
        descendente(n->right);
        cout << n->key << " ";
        descendente(n->left);
     }
}

template <class T>
int AVLtree<T>::calculaAltura(){
    return calculaAltura(root);
}

template <class T>
int AVLtree<T>::calculaAltura(AVLnode<T> *n) {
   int h = 0;
   if (n != NULL) {
      int l_height = calculaAltura(n->left);
      int r_height = calculaAltura(n->right);
      int max_height = max(l_height, r_height);
      h = max_height + 1;
   }
   return h;
}

template <class T>
int AVLtree<T>::calculaAlturaDeNodo(const T key){
    return calculaAlturaDeNodo(root, key);
}

template <class T>
int AVLtree<T>::calculaAlturaDeNodo(AVLnode<T> *n, const T key){
    int altura=1;
	while( n ){
		if( key == n->key ) return altura;
		else{
			altura++;
			if( key < n->key ) n = n->left;
			else n = n->right;
        }
	}
	return 0;
}

template <class T>
int AVLtree<T>::nivelDeNodo(const T key){
    nivelDeNodo(root, key);
}

template <class T>
int AVLtree<T>::nivelDeNodo(AVLnode<T> *n, const T key){
    int nivel = 0;
    while(n){
        if(n->key == key){
            return nivel;
        }else{
            nivel++;
            if(key < n->key){
                n = n->left;
            }else{
                n = n->right;
            }
        }
    }
    return -1;
}

template <class T>
AVLnode<T>* AVLtree<T>::buscarNodo(const T key){
    return buscarNodo(root, key);
}

template <class T>
AVLnode<T>* AVLtree<T>::buscarNodo(AVLnode<T> *n, const T key){
    if(n == NULL){
        return NULL;
    }else if(n->key == key){
        return n;
    }else if(key < n->key ){
        return buscarNodo(n->left, key);
    }else{
        return buscarNodo(n->right, key);
    }
}

int main(void)
{
    int altura, altNodo, keyAlto, keyNiv, nivNodo;
    AVLnode<int>* busqueda;

    AVLtree<int> t;
    for (int i = 1; i <= 100000; ++i){
        t.insert(rand()%50);
    }

    //Ordenamiento ascendente
    cout<<"Orden Ascendente del arbol\n";
    t.ordenarAsc();
    cout<<"\n\nOrden Ascendente del arbol\n";
    //Ordenamiento descendente
    t.ordenarDes();
    //Borrar Elemento;
    cout<<"\n\nBorrar elemento del arbol";
    t.deleteKey(5);
    //Calcular altura árbol
    altura = t.calculaAltura();
    cout<<"\n\nAltura del arbol: "<< altura;
    //Busqueda de un nodo;
    cout<<"\n\nBusqueda de un elemento del arbol ";
    busqueda = t.buscarNodo(2);
    cout<<"\nNodo del elemento del arbol: apuntador->" << busqueda << " elemento->" << busqueda->key;

    //Calcula Altura de un Nodo
    keyAlto = 8;
    altNodo = t.calculaAlturaDeNodo(keyAlto);
    cout<<"\n\nAltura del numero " << keyAlto << " en el arbol: " << altNodo;
    //Calcula Nivel de un Nodo
    keyNiv = 8;
    nivNodo = t.nivelDeNodo(keyNiv);
    cout<<"\n\nNivel del numero " << keyNiv << " en el arbol: " << nivNodo;

}
