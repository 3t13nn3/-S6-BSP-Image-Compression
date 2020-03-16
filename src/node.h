#ifndef NODE_H
#define NODE_H

#include <stdlib.h>
#include <assert.h>

#include "cut.h"
#include "subset.h"
#include "clut.h"

typedef struct node Node;
struct node{

	Node* _leftChild;
	Node* _rightChild;
	Subset _subset;
	Cut _cut;
	int _cutAxe;
};


Node* newNode(Cut cut, Subset sub, int cutAxe);

void addLeftNode(Cut cut, Subset sub, Node* father, int cutAxe);

void addRightNode(Cut cut, Subset sub, Node* father, int cutAxe);

void printAllChildren(int indentation, Node* n);

void freeAllChildren(Node* n);

void createTree(Node * n, int cpt);

void modifyCLUTFromTree(CLUT * c, Node * tree);

#endif
