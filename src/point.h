#ifndef POINT_H
#define POINT_H

#include <stdio.h>

struct point{

	short _x;
	short _y;
};
typedef struct point Point;

Point newPoint(short x, short y);

void setPoint(short x, short y, Point* p);

void printPoint(int nbTabulation, Point* p);

#endif
