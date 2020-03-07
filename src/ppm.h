#ifndef PPM_H
#define PPM_H

#include <stdio.h> 
#include <stdlib.h>
#include <assert.h>

#include <GL/gl.h>	

struct Image {
    unsigned long sizeX;
    unsigned long sizeY;
    GLubyte *data;
};
typedef struct Image Image;
typedef unsigned short utab [3][3][3];

int ImageLoad_PPM(char *filename, Image *image);
void imagesave_PPM(char *filename, Image *image);

#endif