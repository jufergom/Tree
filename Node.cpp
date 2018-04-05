//
// Created by jufer on 19/3/2018.
//

#include "Node.h"

Node::Node(int number) {
    this->number = number;
    left = NULL;
    right = NULL;
}

int Node::getHeight() {
    if(left == NULL && right == NULL)
        return 0;
    int leftDepth = 0;
    int rightDepth = 0;
    if(left != NULL)
        leftDepth = left->getHeight();
    if(right != NULL)
        rightDepth = right->getHeight();
    if (leftDepth > rightDepth)
        return(leftDepth+1);
    return(rightDepth+1);
}
