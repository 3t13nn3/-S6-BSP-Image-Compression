#ifndef CUT_H
#define CUT_H

#include <math.h>

#include "point.h"
#include "subset.h"

#define CUT_POINTS_SIZE 4

#define AXES_NB 3

#define X_AXE 0
#define Y_AXE 1
#define Z_AXE 2

struct cut{

	Point _coordinates[CUT_POINTS_SIZE];
};
typedef struct cut Cut;

Cut newCutFromPoints(Point a, Point b, Point c, Point d);

Cut getCutFromSubset(Subset * sub, int cutAxe);

void printCut(int indentation, Cut * c);

#endif
