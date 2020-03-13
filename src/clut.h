#ifndef CLUT_H
#define CLUT_H

#include <stdlib.h>
#include <math.h>

#include <GL/gl.h>

#include "ppm.h"

#define SHADE 256
#define PIXEL_ELEMENTS 3

struct clut{

	char*** _data;
};
typedef struct clut CLUT;

CLUT newCLUT();

void fillCLUTfromImage(CLUT * c, Image * img);

void printCLUT(CLUT * c);

void rgb2hsv(int r, int g, int b, int* h, int* s, int* v);

void hsv2rgb(int h, double s, double v, int* r, int* g, int* b);

#endif
