#ifndef NODE_H
#define NODE_H

#include "segment.h"

typedef struct node Node;
struct node{

	Node* _leftChild;
	Node* _rightChild;
	Segment _s;
};


Node* newNode(Segment s);

void setNode(Segment s, Node* n);

void printAllChildren(Node* n);

#endif
