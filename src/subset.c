#include "head.h"

Subset newSubsetFromPoints(Point topLeft, Point topRight, Point botLeft, Point botRight, Point topZLeft, Point topZRight, Point botZLeft, Point botZRight) {

	Subset toReturn;

	toReturn._coordinates[0] = topLeft;
	toReturn._coordinates[1] = topRight;
	toReturn._coordinates[2] = botLeft;
	toReturn._coordinates[3] = botRight;
	toReturn._coordinates[4] = topZLeft;
	toReturn._coordinates[5] = topZRight;
	toReturn._coordinates[6] = botZLeft;
	toReturn._coordinates[7] = botZRight;

	return toReturn;
}

Subset newSubsetFromDimensions(short firstDimensionSize, short secondDimensionSize, short thirdDimensionSize) {

	Subset toReturn;

	firstDimensionSize--;
	secondDimensionSize--;
	thirdDimensionSize--;

	toReturn._coordinates[0] = newPoint(0, 0, 0);
	toReturn._coordinates[1] = newPoint(firstDimensionSize, 0, 0);
	toReturn._coordinates[2] = newPoint(0, secondDimensionSize, 0);
	toReturn._coordinates[3] = newPoint(firstDimensionSize, secondDimensionSize, 0);
	toReturn._coordinates[4] = newPoint(0, 0, thirdDimensionSize);
	toReturn._coordinates[5] = newPoint(firstDimensionSize, 0, thirdDimensionSize);
	toReturn._coordinates[6] = newPoint(0, secondDimensionSize, thirdDimensionSize);
	toReturn._coordinates[7] = newPoint(firstDimensionSize, secondDimensionSize, thirdDimensionSize);

	return toReturn;
}

void printSubset(int nbTabulation, Subset * s){

	int i,j;
	for(i=0; i<nbTabulation; ++i){
		printf("\t");
	}
	printf("Subset:\n");

	for(i = 0; i< NB_SUBSET_POINT; ++i){
		for(j=0; j<nbTabulation; ++j){
			printf("\t");
		}

		printPoint(1, &s->_coordinates[i]);
	}
	printf("\n");
}
