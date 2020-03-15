#include "point.h"

Point newPoint(short x, short y, short z){

	return (Point){x, y, z};
}

void setPoint(short x, short y, short z, Point* p){

	p->_x = x;
	p->_y = y;
	p->_y = z;
}

void printPoint(int nbTabulation, Point* p){

	int i;
	for(i=0; i<nbTabulation; ++i){
		printf("\t");
	}
	printf("Point:\n");
	for(i=0; i<nbTabulation+1; ++i){
		printf("\t");
	}
	printf("x: %hd | y: %hd | z: %hd", p->_x, p->_y, p->_z);
	printf("\n");
}
