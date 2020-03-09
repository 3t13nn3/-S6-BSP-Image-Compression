#include "subset.h"

Subset newSubset4Points(Point topLeft, Point topRight, Point botLeft, Point botRight) {

	Subset toReturn;

	toReturn._coordinates[0] = topLeft;
	toReturn._coordinates[1] = topRight;
	toReturn._coordinates[2] = botLeft;
	toReturn._coordinates[3] = botRight;

	return toReturn;
}

Subset newSubsetFromDimensions(short sizeX, short sizeY) {

	Subset toReturn;

	toReturn._coordinates[0] = newPoint(0,0);
	toReturn._coordinates[1] = newPoint(sizeX,0);
	toReturn._coordinates[2] = newPoint(0,sizeY);
	toReturn._coordinates[3] = newPoint(sizeX, sizeY);

	return toReturn;
}

void printSubset(int nbTabulation, Subset * s){

	int i,j;
	for(i=0; i<nbTabulation; ++i){
		printf("\t");
	}
	printf("Subset:\n");

	for(i = 0; i< 4; ++i){
		for(j=0; j<nbTabulation; ++j){
			printf("\t");
		}

		printPoint(1, &s->_coordinates[i]);
	}
	printf("\n");
}
