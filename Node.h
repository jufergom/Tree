#ifndef TREE_NODE_H
#define TREE_NODE_H

#include <iostream>

struct Node {
    int number;
    Node* left;
    Node* right;

    Node(int);
    int getHeight();
};


#endif //TREE_NODE_H
