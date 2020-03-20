#include "head.h"

Node* newNode(Subset sub){

	Node* toReturn = (Node*)malloc(sizeof(Node));
	assert(toReturn);

	toReturn->_leftChild = NULL;
	toReturn->_rightChild = NULL;
	toReturn->_subset = sub;

	return toReturn;
}

void addLeftNode(Subset sub, Node* father){

	Node* n = newNode(sub);

	father->_leftChild = n;
}

void addRightNode(Subset sub, Node* father){

	Node* n = newNode(sub);

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
void createTree(Node * n, int cpt, Cut cut, int actualCutAxe) {
	if(cpt == 0 || cpt > 40)
		return;


	Subset left;
	Subset right;

	int nextCut = (actualCutAxe+1)%AXES_NB;

	switch (actualCutAxe){
		case X_AXE:

			left  = newSubsetFromPoints(n->_subset._coordinates[0],cut._coordinates[0],n->_subset._coordinates[2],cut._coordinates[2],
			                            n->_subset._coordinates[4],cut._coordinates[1],n->_subset._coordinates[6],cut._coordinates[3]);
			
			right = newSubsetFromPoints(cut._coordinates[0],n->_subset._coordinates[1],cut._coordinates[2],n->_subset._coordinates[3],
			                            cut._coordinates[1],n->_subset._coordinates[5],cut._coordinates[3],n->_subset._coordinates[7]);

			break;

		case Y_AXE:

			left  = newSubsetFromPoints(n->_subset._coordinates[0],n->_subset._coordinates[1],cut._coordinates[0],cut._coordinates[1],
			                            n->_subset._coordinates[4],n->_subset._coordinates[5],cut._coordinates[2],cut._coordinates[3]);
			
			right = newSubsetFromPoints(cut._coordinates[0],cut._coordinates[1],n->_subset._coordinates[2],n->_subset._coordinates[3],
			                            cut._coordinates[2],cut._coordinates[3],n->_subset._coordinates[6],n->_subset._coordinates[7]);

			break;

		case Z_AXE:

			left  = newSubsetFromPoints(n->_subset._coordinates[0],n->_subset._coordinates[1],n->_subset._coordinates[2],n->_subset._coordinates[3],
			                            cut._coordinates[0],cut._coordinates[1],cut._coordinates[2],cut._coordinates[3]);
			
			right = newSubsetFromPoints(cut._coordinates[0],cut._coordinates[1],cut._coordinates[2],cut._coordinates[3],
			                            n->_subset._coordinates[4],n->_subset._coordinates[5],n->_subset._coordinates[6],n->_subset._coordinates[7]);

			break;

		default:
			break;
	}

	addLeftNode(left,n);
		createTree(n->_leftChild,cpt-1,getCutFromSubset(&left, nextCut),nextCut);
	addRightNode(right,n);
		createTree(n->_rightChild,cpt-1,getCutFromSubset(&right, nextCut),nextCut);
}

void modifyCloudFromTree(Cloud * c, Node * tree){
	
	if(tree->_leftChild != NULL){
		modifyCloudFromTree(c, tree->_leftChild);
	}
	
	if(tree->_rightChild != NULL){
		modifyCloudFromTree(c, tree->_rightChild);
	}

	if(tree->_leftChild == NULL && tree->_rightChild == NULL) { //leaf -> subset

		/*Calculus for the average of all components of the subset*/
		int i, j, k;
		long long int hAverage = 0, sAverage = 0, vAverage = 0;
		long long int nbIterations = ((tree->_subset._coordinates[7]._x - tree->_subset._coordinates[0]._x) 
		                            * (tree->_subset._coordinates[7]._y - tree->_subset._coordinates[0]._y)
									* (tree->_subset._coordinates[7]._z - tree->_subset._coordinates[0]._z));

		if(nbIterations > 0 ){
			for(i = tree->_subset._coordinates[0]._x; i < tree->_subset._coordinates[7]._x; ++i){

				for(j = tree->_subset._coordinates[0]._y; j < tree->_subset._coordinates[7]._y; ++j){

					for(k = tree->_subset._coordinates[0]._z; k < tree->_subset._coordinates[7]._z; ++k){

						if(c->_data[i][j][k] != NULL){

							hAverage+= i;
							sAverage+= j;
							vAverage+= k;	
						}
					}
				}
			}

			hAverage/=nbIterations*3;
			sAverage/=nbIterations*3;
			vAverage/=nbIterations*3;

			/*Assignation of the subset average component for every components of the subset*/
			for(i = tree->_subset._coordinates[0]._x; i < tree->_subset._coordinates[7]._x; ++i){

				for(j = tree->_subset._coordinates[0]._y; j < tree->_subset._coordinates[7]._y; ++j){

					for(k = tree->_subset._coordinates[0]._z; k < tree->_subset._coordinates[7]._z; ++k){

							c->_data[i][j][k][0] = (short)hAverage;
							c->_data[i][j][k][1] = (short)sAverage;
							c->_data[i][j][k][2] = (short)vAverage;
					}
				}
			}
		}
	}
}