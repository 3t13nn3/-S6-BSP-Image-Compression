#include "point.h"

Point newPoint(short x, short y){

	return (Point){x, y};
}

void setPoint(short x, short y, Point* p){

	p->_x = x;
	p->_y = y;
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
	printf("x: %hd | y: %hd", p->_x, p->_y);
	printf("\n");
}
