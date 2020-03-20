#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>

#include <GL/glut.h>
#include <GL/glu.h>

//8 Points for representaing a rectangular space
#define NB_SUBSET_POINT 8
//4 Points to represente a cut plan
#define CUT_POINTS_SIZE 4
//Numbers of axes
#define AXES_NB 3
//Macros to each axes
#define X_AXE 0
#define Y_AXE 1
#define Z_AXE 2
//Each color component
#define NB_COMPONENT 3
#define H 360
#define S 256
#define V 256
//Keys macros
#define ESCAPE 27
#define Q 113

/*DATA STRUCT*/

struct Image {
    unsigned long sizeX;
    unsigned long sizeY;
    GLubyte *data;
};
typedef struct Image Image;


struct point{

	short _x;
	short _y;
	short _z;
};
typedef struct point Point;


struct subset{
	Point _coordinates[NB_SUBSET_POINT];
};
typedef struct subset Subset;


struct cut{

	Point _coordinates[CUT_POINTS_SIZE];
};
typedef struct cut Cut;

struct cloud{

	short _data[H][S][V][NB_COMPONENT];
};
typedef struct cloud Cloud;


/*PPM*/

int ImageLoad_PPM(char *filename, Image *image);

void imagesave_PPM(char *filename, Image *image);


/*POINT*/

Point newPoint(short x, short y, short z);

void setPoint(short x, short y, short z, Point* p);

void printPoint(int nbTabulation, Point* p);


/*SUBSET*/

/*
Subset representation:
        ^  5--------------6
        Z /|             /|
         / |    X>      / |
        1--------------2  |
        |  7-----------|--8
      Y | /            | /
     \/ |/             |/
        3--------------4

------------->                   1              2               3              4               5               6                7               8        */
Subset newSubsetFromPoints(Point topLeft, Point topRight, Point botLeft, Point botRight, Point topZLeft, Point topZRight, Point botZLeft, Point botZRight);

Subset newSubsetFromDimensions(short firstDimensionSize, short secondDimensionSize, short thirdDimensionSize);

void printSubset(int nbTabulation, Subset * s);


/*CUT*/

Cut newCutFromPoints(Point a, Point b, Point c, Point d);

Cut getCutFromSubset(Subset * sub, int cutAxe);

void printCut(int indentation, Cut * c);


/*Cloud*/

void fillCloudfromImage(Cloud * c, Image * img);

void printCloud(Cloud * c);

void rgb2hsv(int r, int g, int b, int* h, int* s, int* v);

void hsv2rgb(int h, double s, double v, int* r, int* g, int* b);

Image newImageFromCloud(Cloud * c, Image * img);


/*NODE*/

typedef struct node Node;
struct node{

	Node* _leftChild;
	Node* _rightChild;
	Subset _subset;
};


Node* newNode(Subset sub);

void addLeftNode(Subset sub, Node* father);

void addRightNode(Subset sub, Node* father);

void printAllChildren(int indentation, Node* n);

void freeAllChildren(Node* n);

void createTree(Node * n, int cpt, Cut cut, int actualCutAxe);

void modifyCloudFromTree(Cloud * c, Node * tree);


/*MENU*/

//Accessing to our main image & Cloud from here
extern Image *image;
extern Image new;
extern Cloud myCloud;
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
