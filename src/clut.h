#ifndef CLUT_H
#define CLUT_H

#include <stdlib.h>

#include <GL/gl.h>

#define SHADE 256
#define PIXEL_ELEMENTS 3

struct clut{

	GLubyte**** _data;
};
typedef struct clut CLUT;

CLUT newCLUT();

#endif
