#include "node.h"

Node* newNode(Segment seg, Subset sub, int previousCutAxe){

	Node* toReturn = (Node*)malloc(sizeof(Node));
	assert(toReturn);

	toReturn->_leftChild = NULL;
	toReturn->_rightChild = NULL;
	toReturn->_subset = sub;
	toReturn->_segment = seg;
	toReturn->_previousCutAxe = previousCutAxe;

	return toReturn;
}

void addLeftNode(Segment seg, Subset sub, Node* father, int previousCutAxe){

	Node* n = newNode(seg, sub, previousCutAxe);

	father->_leftChild = n;
}

void addRightNode(Segment seg, Subset sub, Node* father, int previousCutAxe){

	Node* n = newNode(seg, sub, previousCutAxe);

	father->_rightChild = n;
}

void printAllChildren(int indentation, Node* n){

	if(n->_leftChild != NULL){
		printAllChildren(indentation+1, n->_leftChild);
	}
	
	if(n->_rightChild != NULL){
		printAllChildren(indentation+1, n->_rightChild);
	}
	int i;
	for(i=0; i< indentation; i++){
		printf(".");
	}
	printf("Node:\n");

	printSubset(1, &n->_subset);

	printSegment(1, &n->_segment);

	printf("\tPrevious Cut Axe:\n\t\t%d\n", n->_previousCutAxe);

}
