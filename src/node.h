#ifndef NODE_H
#define NODE_H

#include <stdlib.h>
#include <assert.h>

#include "segment.h"
#include "subset.h"

typedef struct node Node;
struct node{

	Node* _leftChild;
	Node* _rightChild;
	Subset _subset;
	Segment _segment;
	int _previousCutAxe;
};


Node* newNode(Segment seg, Subset sub, int previousCutAxe);

void addLeftNode(Segment seg, Subset sub, Node* father, int previousCutAxe);

void addRightNode(Segment seg, Subset sub, Node* father, int previousCutAxe);

void printAllChildren(int indentation, Node* n);

#endif
