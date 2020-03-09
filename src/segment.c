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
	for(i=0; i<nbTabulation; ++i){
		printf("\t");
	}
	printPoint(1,&s->_p2);
	printf("\n");
}

Segment getCutFromSubset(Subset * sub){

	/*Here, we are randomly generating points for the cut segment*/
	srand(time(NULL));
	float factor, antifactor, distA, distB, T;
	

	Point a;
	distA = sqrt(pow((sub->_coordinates[1]._x - sub->_coordinates[0]._x), 2) + pow((sub->_coordinates[1]._y - sub->_coordinates[0]._y), 2));
	factor = rand()%(int)(distA+1);

	T = factor/distA;

	a._x = (1 - T) * sub->_coordinates[0]._x + T * sub->_coordinates[1]._x;
    a._y = (1 - T) * sub->_coordinates[0]._y + T * sub->_coordinates[1]._y;

	Point b;
	distB = sqrt(pow((sub->_coordinates[3]._x - sub->_coordinates[2]._x), 2) + pow((sub->_coordinates[3]._y - sub->_coordinates[2]._y), 2));
	antifactor = ((distA - factor) / distB) * distA;

	T = antifactor/distA;

	b._x = (1 - T) * sub->_coordinates[2]._x + T * sub->_coordinates[3]._x;
    b._y = (1 - T) * sub->_coordinates[2]._y + T * sub->_coordinates[3]._y;

	return newSegmentFromPoints(a,b);
}
