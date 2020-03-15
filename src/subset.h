#ifndef SUBSET_H
#define SUBSET_H

#include <time.h>

#include "point.h"

#define NB_SUBSET_POINT 8

//8 Points for representaing a rectangular space
struct subset{
	Point _coordinates[NB_SUBSET_POINT];
};
typedef struct subset Subset;

/*
Subset representation:
   5--------6
  /|       /|
 / |      / |
1--------2  |
|  7-----|--8
| /      | /
|/       |/
3--------4

------------->                   1              2               3              4               5               6                7               8        */
Subset newSubsetFromPoints(Point topLeft, Point topRight, Point botLeft, Point botRight, Point topZLeft, Point topZRight, Point botZLeft, Point botZRight);

Subset newSubsetFromDimensions(short firstDimensionSize, short secondDimensionSize, short thirdDimensionSize);

void printSubset(int nbTabulation, Subset * s);

#endif
