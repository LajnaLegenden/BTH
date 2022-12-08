#pragma once

#include "iostream"
#include "string"
#include <stdexcept>
#include <vector>

template<typename T>
class BST {


public:
    struct Node {
        T element;
        Node *parent;
        Node *left;
        Node *right;

        explicit Node(T &element, Node *parent = nullptr, Node *left = nullptr, Node *right = nullptr) : element(element), parent(parent), left(left), right(right) {
        }
    };
    BST();

    virtual ~BST();

    BST(const BST &other) = delete;

    BST(BST &&other) = delete;

    BST &operator=(const BST &other) = delete;

    BST &operator=(BST &&other) = delete;

    void insert(T element);

    void remove(T element);

    bool contains(T element) const;

    T minimum() const;

    T maximum() const;

    int nrOfNodes() const;

    int height() const;

    std::vector<T> path(T element) const;

    void inorder(std::vector<T> &vect) const;

    void preorder(std::vector<T> &vect) const;

    void postorder(std::vector<T> &vect) const;


    std::string ToGraphviz();

    void ToGraphvizHelper(std::string &listOfNodes, std::string &listOfConnections, Node *toWorkWith, size_t &uniqueID);

private:
    Node *root;
    int _nrOfNodes = 0;
    int maxHeight(Node *node) const;

    void inorderNode(std::vector<T> &vect, Node *node) const;

    void preorderNode(std::vector<T> &vect, Node *node) const;

    void postorderNode(std::vector<T> &vect, Node *node) const;

    T successor(Node *_root);
    T predecessor(Node *_root);

    Node *deleteNode(Node *node, T key);
    void destructor(Node *node);
};

template<typename T>
BST<T>::BST() {
    this->root = nullptr;
}
template<typename T>
void BST<T>::destructor(typename BST<T>::Node *node) {
    if(!node){
        return;
    }
    if (node->left) {
        destructor(node->left);
    }
    if (node->right) {
        destructor(node->right);
    }
    delete node;
}

template<typename T>
BST<T>::~BST() {
    destructor(this->root);
}


//funtion that trakes node and returns T
template<typename T>
T BST<T>::successor(Node *_root) {
    _root = _root->right;
    while (_root->left != nullptr) _root = _root->left;
    return _root->element;
}

template<typename T>
T BST<T>::predecessor(Node *_root) {
    _root = _root->left;
    while (_root->right != nullptr) _root = _root->right;
    return _root->element;
}
template<typename T>
typename BST<T>::Node *BST<T>::deleteNode(Node *node, T key) {
    if (node == nullptr) return nullptr;
    if (key > node->element) node->right = deleteNode(node->right, key);
    else if (key < node->element)
        node->left = deleteNode(node->left, key);
    else {
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            node = nullptr;
        } else if (node->right != nullptr) {
            node->element = successor(node);
            node->right = deleteNode(node->right, node->element);
        } else {
            node->element = predecessor(node);
            node->left = deleteNode(node->left, node->element);
        }
    }
    return node;
}

template<typename T>
int BST<T>::height() const {
    if (this->root == nullptr)
        return -1;
    return maxHeight(this->root);
}

template<typename T>
int BST<T>::maxHeight(Node *node) const {
    if (node == NULL)
        return -1;
    else {
        /* compute the depth of each subtree */
        int lDepth = maxHeight(node->left);
        int rDepth = maxHeight(node->right);

        /* use the larger one */
        if (lDepth > rDepth)
            return (lDepth + 1);
        else
            return (rDepth + 1);
    }
}


template<typename T>
bool BST<T>::contains(T element) const {
    Node *walker = this->root;

    while (true) {

        if (walker->element == element)
            return true;
        if (walker->element > element && walker->left != nullptr) {
            walker = walker->left;
        } else if (walker->element < element && walker->right != nullptr) {
            walker = walker->right;
        } else {
            return false;
        }
    }
}

template<typename T>
T BST<T>::maximum() const {
    Node *walker = this->root;

    if (this->root == nullptr) throw std::out_of_range("No elements in tree");

    while (true) {
        if (walker->right != nullptr) {
            walker = walker->right;
            continue;
        }
        return walker->element;
    }
}

template<typename T>
T BST<T>::minimum() const {
    Node *walker = this->root;
    if (this->root == nullptr) throw std::out_of_range("No elements in tree");

    while (true) {
        if (walker->left != nullptr) {
            walker = walker->left;
            continue;
        }
        return walker->element;
    }
}

template<typename T>
void BST<T>::preorder(std::vector<T> &vect) const {
    this->preorderNode(vect, this->root);
}

template<typename T>
void BST<T>::preorderNode(std::vector<T> &vect, Node *node) const {
    vect.push_back(node->element);

    if (node->left != nullptr) preorderNode(vect, node->left);

    if (node->right != nullptr) preorderNode(vect, node->right);
}

template<typename T>
std::vector<T> BST<T>::path(T element) const {
    std::vector<T> path;
    Node *walker = this->root;

    while (true) {
        path.push_back(walker->element);
        if (walker->element == element)
            return path;
        if (walker->element > element && walker->left != nullptr) {
            walker = walker->left;
        } else if (walker->element < element && walker->right != nullptr) {
            walker = walker->right;
        } else {
            throw std::out_of_range("Element not in tree");
        }
    }
}

template<typename T>
void BST<T>::inorder(std::vector<T> &vect) const {
    this->inorderNode(vect, this->root);
}

template<typename T>
void BST<T>::inorderNode(std::vector<T> &vect, Node *node) const {
    if (node->left != nullptr) {
        inorderNode(vect, node->left);
    }
    vect.push_back(node->element);


    if (node->right != nullptr) inorderNode(vect, node->right);
}

template<typename T>
void BST<T>::postorder(std::vector<T> &vect) const {
    this->postorderNode(vect, this->root);
}

template<typename T>
void BST<T>::insert(T element) {
    this->_nrOfNodes++;
    if (this->root == nullptr) {
        this->root = new Node(element);
        return;
    }

    Node *walker = this->root;
    bool added = false;

    while (!added) {
        if (element < walker->element) {
            if (walker->left != nullptr) {
                walker = walker->left;
            } else {

                walker->left = new Node(element, walker);
                added = true;
            }
        } else {
            if (walker->right != nullptr) {
                walker = walker->right;
            } else {
                walker->right = new Node(element, walker);

                added = true;
            }
        }
    }
}


template<typename T>
void BST<T>::postorderNode(std::vector<T> &vect, BST::Node *node) const {

    if (node->left) {
        postorderNode(vect, node->left);
    }
    if (node->right) {
        postorderNode(vect, node->right);
    }
    vect.push_back(node->element);
}
template<typename T>
int BST<T>::nrOfNodes() const {
    return this->_nrOfNodes;
}
template<typename T>
void BST<T>::remove(T element) {
    if (this->nrOfNodes() == 1) {
        delete this->root;
        this->root = nullptr;
    }
    this->deleteNode(this->root, element);
    this->_nrOfNodes--;
}
template<typename T>
void BST<T>::ToGraphvizHelper(std::string &listOfNodes, std::string &listOfConnections, Node *toWorkWith, size_t &uniqueID)// Member function of the BST class
{
    size_t myID = uniqueID;
    listOfNodes += std::string("\t") + std::to_string(myID) + std::string(" [label=\"") + std::to_string(toWorkWith->element) + std::string("\"];\n");
    if (toWorkWith->left) {
        listOfConnections += std::string("\t") + std::to_string(myID) + std::string(" -> ") + std::to_string(uniqueID + 1) + std::string(" [color=blue];\n");
        ToGraphvizHelper(listOfNodes, listOfConnections, toWorkWith->left, ++uniqueID);
    } else {
        listOfNodes += std::string("\t") + std::to_string(++uniqueID) + std::string(" [label=") + std::string("nill, style = invis];\n");
        listOfConnections += std::string("\t") + std::to_string(myID) + std::string(" -> ") + std::to_string(uniqueID) + std::string(" [ style = invis];\n");
    }

    if (toWorkWith->right) {
        listOfConnections += std::string("\t") + std::to_string(myID) + std::string(" -> ") + std::to_string(uniqueID + 1) + std::string(" [color=red];\n");
        ToGraphvizHelper(listOfNodes, listOfConnections, toWorkWith->right, ++uniqueID);
    } else {
        listOfNodes += std::string("\t") + std::to_string(++uniqueID) + std::string(" [label=") + std::string("nill, style = invis];\n");
        listOfConnections += std::string("\t") + std::to_string(myID) + std::string(" -> ") + std::to_string(uniqueID) + std::string(" [ style = invis];\n");
    }
}


template<typename T>
std::string BST<T>::ToGraphviz()// Member function of the BST class
{
    std::string toReturn = "";
    if (root)// root is a pointer to the root node of the tree
    {
        std::string listOfNodes;
        std::string listOfConnections = std::string("\t\"Root\" -> ") + std::to_string(0) + std::string(";\n");
        toReturn += std::string("digraph {\n");
        size_t id = 0;
        ToGraphvizHelper(listOfNodes, listOfConnections, root, id);
        toReturn += listOfNodes;
        toReturn += listOfConnections;
        toReturn += std::string("}");
    }
    std::move(toReturn);
    return toReturn;
}