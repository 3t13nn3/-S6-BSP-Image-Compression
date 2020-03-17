#ifndef CLUT_H
#define CLUT_H

#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include <GL/gl.h>

#include "ppm.h"

#define H 360
#define S 256
#define V 256

#define NB_COMPONENT 3

struct clut{

	short**** _data;
};
typedef struct clut CLUT;

CLUT newCLUT();

void fillCLUTfromImage(CLUT * c, Image * img);

void printCLUT(CLUT * c);

void freeCLUT(CLUT * c);

void rgb2hsv(int r, int g, int b, int* h, int* s, int* v);

void hsv2rgb(int h, double s, double v, int* r, int* g, int* b);

Image newImageFromCLUT(CLUT * c, Image * img);

#endif
