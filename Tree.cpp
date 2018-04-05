//
// Created by jufer on 19/3/2018.
//

#include "Tree.h"

using namespace std;

Tree::Tree() {
    root = NULL;
}

void Tree::addNode(int number) {
    Node* newNode = new Node(number);
    addNode(newNode, &root);
}

void Tree::addNode(Node* nuevo, Node** subRoot) {
    if(*subRoot == NULL) {
        *subRoot = nuevo;
    }
    else {
        if(nuevo->number < (*subRoot)->number) {
            addNode(nuevo, &(*subRoot)->left);
            balance(subRoot);
        }

        else if(nuevo->number > (*subRoot)->number) {
            addNode(nuevo, &(*subRoot)->right);
            balance(subRoot);
        }
    }
}

/* Given a non-empty binary search tree, return the node with minimum
   key value found in that tree. Note that the entire tree does not
   need to be searched. */
Node* Tree::minValueNode(Node* node) {
    Node* current = node;

    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;

    return current;
}

Node* Tree::deleteNode(int number) {
    return deleteNode(number, root);
}

Node* Tree::deleteNode(int number, Node* subRoot) {
    //caso base
    if(subRoot == NULL)
        return subRoot;
    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    if(number < subRoot->number)
        subRoot->left = deleteNode(number, subRoot->left);

    // If the key to be deleted is greater than the root's key,
    // then it lies in right subtree
    else if(number > subRoot->number)
        subRoot->right = deleteNode(number, subRoot->right);

    // if key is same as root's key, then This is the node
    // to be deleted
    else {
        // node with only one child or no child
        if(subRoot->left == NULL) {
            Node* temp = subRoot->right;
            delete subRoot;
            return temp;
        }
        else if(subRoot->right == NULL) {
            Node* temp = subRoot->left;
            delete subRoot;
            return temp;
        }
        // node with two children: Get the inorder successor (smallest
        // in the right subtree)
        Node* temp = minValueNode(subRoot->right);

        // Copy the inorder successor's content to this node
        subRoot->number = temp->number;

        // Delete the inorder successor
        subRoot->right = deleteNode(temp->number, subRoot->right);
    }
    return subRoot;
}

void Tree::preOrden() {
    preOrden(root);
}

void Tree::preOrden(Node* subRoot) {
    if(subRoot == NULL)
        return;
    cout << subRoot->number << endl;
    if(subRoot->left != NULL)
        preOrden(subRoot->left);
    if(subRoot->right != NULL)
        preOrden(subRoot->right);
}

void Tree::inOrden() {
    inOrden(root);
}

void Tree::inOrden(Node* subRoot) {
    if(subRoot == NULL)
        return;
    if(subRoot->left != NULL)
        inOrden(subRoot->left);
    cout << subRoot->number << endl;
    if(subRoot->right != NULL)
        inOrden(subRoot->right);
}

void Tree::postOrden() {
    postOrden(root);
}

void Tree::postOrden(Node* subRoot) {
    if(subRoot == NULL)
        return;
    if(subRoot->left != NULL)
        postOrden(subRoot->left);
    if(subRoot->right != NULL)
        postOrden(subRoot->right);
    cout << subRoot->number << endl;
}

int Tree::getHeight() {
    return getHeight(root);
}

int Tree::getHeight(Node* subRoot) {
    if(subRoot == NULL)
        return 0;
    else {
        int leftDepth = getHeight(subRoot->left);
        int rightDepth = getHeight(subRoot->right);
        if (leftDepth > rightDepth)
            return(leftDepth+1);
        else
            return(rightDepth+1);
    }
}

void Tree::printHojas() {
    printHojas(root);
}

void Tree::printHojas(Node* subRoot) {
    if(subRoot->left != NULL)
        printHojas(subRoot->left);
    if(subRoot->right != NULL)
        printHojas(subRoot->right);
    if(subRoot->left == NULL && subRoot->right == NULL)
        cout << subRoot->number << endl;
}

int Tree::getSize() {
    return getSize(root);
}

int Tree::getSize(Node* subRoot) {
    if(subRoot == NULL)
        return 0;
    return (getSize(subRoot->left) + 1 + getSize(subRoot->right));
}

void Tree::balance(Node **subRoot) {
    //si la diferencia de alturas es menor a 2, entonces no se balancea nada
    if(abs(getHeight((*subRoot)->left) - getHeight((*subRoot)->right)) < 2)
        return;
    //si la altura del nodo derecho de la sub raiz es mayor a la altura del nodo izquierdo de la sub raiz
    //entonces se procederá a hacer una rotacion a la izquierda, caso contrario se hara una rotacion a la derecha
    if(getHeight((*subRoot)->right) > getHeight((*subRoot)->left)) {
        if(getHeight((*subRoot)->right->right) >= getHeight((*subRoot)->right->left))
            leftRotate(subRoot);
        else
            leftDoubleRotate(subRoot);
    }
    else {
        if(getHeight((*subRoot)->left->left) >= getHeight((*subRoot)->right))
            rightRotate(subRoot);
        else
            rightDoubleRotate(subRoot);
    }
}

void Tree::leftRotate(Node **subRoot) {
    Node* right = (*subRoot)->right;
    (*subRoot)->right = right->left;
    right->left = *subRoot;
    *subRoot = right;
}

void Tree::rightRotate(Node **subRoot) {
    Node* left = (*subRoot)->left;
    (*subRoot)->left = left->right;
    left->right = *subRoot;
    *subRoot = left;
}

void Tree::leftDoubleRotate(Node **subRoot) {
    Node *right = (*subRoot)->right;
    rightRotate(&right);
    leftRotate(subRoot);
}

void Tree::rightDoubleRotate(Node **subRoot) {
    Node* left = (*subRoot)->left;
    leftRotate(&left);
    rightRotate(subRoot);
}
