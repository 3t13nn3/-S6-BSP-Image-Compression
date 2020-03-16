#ifndef SEGMENT_H
#define SEGMENT_H

#include <stdio.h>
#include <math.h>

#include "point.h"
#include "subset.h"

struct segment{

	Point _p1;
	Point _p2;
};
typedef struct segment Segment;

Segment newSegmentFromPoints(Point p1, Point p2);

Segment newSegmentFromCoordinates(short x1, short y1, short z1, short x2, short y2, short z2);

void setSegmentFromPoints(Point p1, Point p2, Segment* s);

void setSegmentFromCoordinates(short x1, short y1, short z1, short x2, short y2, short z2, Segment* s);

void printSegment(int nbTabulation, Segment* s);

#endif
