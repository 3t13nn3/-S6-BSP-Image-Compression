#ifndef SUBSET_H
#define SUBSET_H

#include <time.h>

#include "point.h"

struct subset{
	Point _coordinates[4];
};
typedef struct subset Subset;

Subset newSubset4Points(Point topLeft, Point topRight, Point botLeft, Point botRight);

Subset newSubsetFromDimensions(short sizeX, short sizeY);

void printSubset(int nbTabulation, Subset * s);

#endif
