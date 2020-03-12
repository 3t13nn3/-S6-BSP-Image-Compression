#ifndef CLUT_H
#define CLUT_H

#include <stdlib.h>

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

#endif
