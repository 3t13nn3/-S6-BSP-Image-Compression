#include "node.h"

Node* newNode(Cut cut, Subset sub, int cutAxe){

	Node* toReturn = (Node*)malloc(sizeof(Node));
	assert(toReturn);

	toReturn->_leftChild = NULL;
	toReturn->_rightChild = NULL;
	toReturn->_subset = sub;
	toReturn->_cut = cut;
	toReturn->_cutAxe = cutAxe;

	return toReturn;
}

void addLeftNode(Cut cut, Subset sub, Node* father, int cutAxe){

	Node* n = newNode(cut, sub, cutAxe);

	father->_leftChild = n;
}

void addRightNode(Cut cut, Subset sub, Node* father, int cutAxe){

	Node* n = newNode(cut, sub, cutAxe);

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

	printCut(1, &n->_cut);

	printf("\tPrevious Cut Axe:\n\t\t%d\n", n->_cutAxe);

}

void freeAllChildren(Node* n){

	if(n->_leftChild != NULL){
		freeAllChildren(n->_leftChild);
	}
	
	if(n->_rightChild != NULL){
		freeAllChildren(n->_rightChild);
	}

	free(n);
}

/*Test function, care, cpt argument make 2^cpt nodes*/
void createTree(Node * n, int cpt) {
	if(cpt == 0 || cpt > 10)
		return;

	//SPLIT SUBSET BY THE CUT
	//n->_subset;
	//n->_cut;

	Subset left;
	Subset right;

	int nextCut = (n->_cutAxe+1)%AXES_NB;

	switch (n->_cutAxe){
		case X_AXE:

			left  = newSubsetFromPoints(n->_subset._coordinates[0],n->_cut._coordinates[0],n->_subset._coordinates[2],n->_cut._coordinates[2],
			                            n->_subset._coordinates[4],n->_cut._coordinates[1],n->_subset._coordinates[6],n->_cut._coordinates[3]);
			
			right = newSubsetFromPoints(n->_cut._coordinates[0],n->_subset._coordinates[1],n->_cut._coordinates[2],n->_subset._coordinates[3],
			                            n->_cut._coordinates[1],n->_subset._coordinates[5],n->_cut._coordinates[3],n->_subset._coordinates[7]);

			break;

		case Y_AXE:

			left  = newSubsetFromPoints(n->_subset._coordinates[0],n->_subset._coordinates[1],n->_cut._coordinates[0],n->_cut._coordinates[1],
			                            n->_subset._coordinates[4],n->_subset._coordinates[5],n->_cut._coordinates[2],n->_cut._coordinates[3]);
			
			right = newSubsetFromPoints(n->_cut._coordinates[0],n->_cut._coordinates[1],n->_subset._coordinates[2],n->_subset._coordinates[3],
			                            n->_cut._coordinates[2],n->_cut._coordinates[3],n->_subset._coordinates[6],n->_subset._coordinates[7]);

			break;

		case Z_AXE:

			left  = newSubsetFromPoints(n->_subset._coordinates[0],n->_subset._coordinates[1],n->_subset._coordinates[2],n->_subset._coordinates[3],
			                            n->_cut._coordinates[0],n->_cut._coordinates[1],n->_cut._coordinates[2],n->_cut._coordinates[3]);
			
			right = newSubsetFromPoints(n->_cut._coordinates[0],n->_cut._coordinates[1],n->_cut._coordinates[2],n->_cut._coordinates[3],
			                            n->_subset._coordinates[4],n->_subset._coordinates[5],n->_subset._coordinates[6],n->_subset._coordinates[7]);

			break;

		default:
			break;
	}

	addLeftNode(getCutFromSubset(&left, nextCut),left,n,nextCut);
		createTree(n->_leftChild,cpt-1);
	addRightNode(getCutFromSubset(&right, nextCut),right,n,nextCut);
		createTree(n->_rightChild,cpt-1);
}

void modifyCLUTFromTree(CLUT * c, Node * tree){
	if(tree->_leftChild != NULL){
		modifyCLUTFromTree(c, tree->_leftChild);
	}
	
	if(tree->_rightChild != NULL){
		modifyCLUTFromTree(c, tree->_rightChild);
	}

	if(tree->_leftChild != NULL && tree->_rightChild != NULL) { //leaf -> subset
		int i, j, k;
		long long int hAverage = 0, sAverage = 0, vAverage = 0;
		for(i = tree->_subset._coordinates[0]._x; i < tree->_subset._coordinates[0]._x; ++i){
			for(j = tree->_subset._coordinates[0]._y; j < tree->_subset._coordinates[0]._y; ++j){
				for(k = tree->_subset._coordinates[0]._z; k < tree->_subset._coordinates[0]._z; ++k){
					if(c->_data[i][j][k]){
						hAverage+= i;
						sAverage+= j;
						vAverage+= k;
					}
				}
			}
		}
	}

}