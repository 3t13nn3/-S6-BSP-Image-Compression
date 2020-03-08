#include "segment.h"

Segment newSegmentFromPoints(Point p1, Point p2){

	return (Segment){p1, p2};
}

Segment newSegmentFromCoordinates(short x1, short y1, short x2, short y2){

	return (Segment){newPoint(x1, y1),
	                 newPoint(x2, y2)};
}

void setSegmentFromPoints(Point p1, Point p2, Segment* s){

	s->_p1 = p1;
	s->_p2 = p2;
}

void setSegmentFromCoordinates(short x1, short y1, short x2, short y2, Segment* s){

	s->_p1 = newPoint(x1, y1);
	s->_p2 = newPoint(x2, y2);
}

void printSegment(int nbTabulation, Segment* s){

	int i;
	for(i=0; i<nbTabulation; ++i){
		printf("\t");
	}
	printf("Segment:\n");
	for(i=0; i<nbTabulation; ++i){
		printf("\t");
	}
	printPoint(1,&s->_p1);
	printPoint(1,&s->_p2);
	printf("\n");
}
