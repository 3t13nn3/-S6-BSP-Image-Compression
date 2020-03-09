#include "node.h"

Node* newNode(Segment seg, Subset sub){

	Node* toReturn = malloc(sizeof(Node));

	toReturn->_leftChild = NULL;
	toReturn->_rightChild = NULL;
	toReturn->_subset = sub;
	toReturn->_segment = seg;

	return toReturn;
}

void addLeftNode(Segment seg, Subset sub, Node* father){

	Node* n = newNode(seg, sub);

	father->_leftChild = n;
}

void addRightNode(Segment seg, Subset sub, Node* father){

	Node* n = newNode(seg, sub);

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

}
