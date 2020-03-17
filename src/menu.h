#ifndef MENU_H
#define MENU_H

#include <unistd.h>
#include <math.h>
#include "ppm.h"

#include <GL/glut.h>
#include <GL/glu.h>

#include "subset.h"
#include "node.h"
#include "clut.h"
#include "cut.h"

#define ESCAPE 27
#define Q 113

//Accessing to our main image & CLUT from here
extern Image *image;
extern Image new;
extern CLUT myCLUT;
extern Node* root;


void Keyboard(unsigned char key, int x, int y);

void Mouse(int button, int state, int x, int y);

int Init(char *s);

int ReInit();

void Display(void);

void Reshape(int w, int h);

void menuFunc(int item);

void initWindow(int argc, char **argv);

void startGraphicalLoop();

#endif