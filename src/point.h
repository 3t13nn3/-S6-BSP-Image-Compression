#ifndef POINT_H
#define POINT_H

#include <stdio.h>

struct point{

	short _x;
	short _y;
	short _z;
};
typedef struct point Point;

Point newPoint(short x, short y, short z);

void setPoint(short x, short y, short z, Point* p);

void printPoint(int nbTabulation, Point* p);

#endif
