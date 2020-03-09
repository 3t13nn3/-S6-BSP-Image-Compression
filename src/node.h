#ifndef NODE_H
#define NODE_H

#include <stdlib.h>

#include "segment.h"
#include "subset.h"

typedef struct node Node;
struct node{

	Node* _leftChild;
	Node* _rightChild;
	Subset _subset;
	Segment _segment;
};


Node* newNode(Segment seg, Subset sub);

void addLeftNode(Segment seg, Subset sub, Node* father);

void addRightNode(Segment seg, Subset sub, Node* father);

void printAllChildren(int indentation, Node* n);

#endif
