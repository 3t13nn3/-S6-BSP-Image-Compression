#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

//8 Points to represent a rectangular space
#define NB_SUBSET_POINT 8
//4 Points to represent a cut plan
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

#ifdef SHORT
  typedef short usedType;
#else
  typedef GLubyte usedType;
#endif

/*DATA STRUCT*/

struct Image {
    unsigned long sizeX;
    unsigned long sizeY;
    GLubyte *data;
};
typedef struct Image Image;

struct compressedImage {
    unsigned long sizeX;
    unsigned long sizeY;
    usedType *data;
};
typedef struct compressedImage CompressedImage;

struct point{

	short _x;
	GLubyte _y;
	GLubyte _z;
};
typedef struct point Point;


struct cut{

	Point _coordinates[CUT_POINTS_SIZE];
};
typedef struct cut Cut;


struct subset{
	Point _coordinates[NB_SUBSET_POINT];
};
typedef struct subset Subset;


struct cloud{

	short _data[H][S][V][NB_COMPONENT];
};
typedef struct cloud Cloud;


typedef struct node Node;
struct node{

	Node* _leftChild;
	Node* _rightChild;
	Subset _subset;
};


int treeDepth;

typedef struct clutNode CLUTNode;
struct clutNode{

	CLUTNode* _child;
  GLubyte* _data;
  usedType _index;
};

/*GLOBAL*/

Image* image;
Image new;
CompressedImage compressed;
Image extracted;
Cloud myCloud;
Node* root;
CLUTNode * CLUT;

/*PPM*/

int ImageLoad_PPM(char *filename, Image *image);

void imagesave_PPM(char *filename, Image *img);

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

Cut getCutFromSubset(Subset * sub, int cutAxe, int pourcentage);

void printCut(int indentation, Cut * c);


/*Cloud*/

void fillCloudfromImage(Cloud * c, Image * img);

void printCloud(Cloud * c);

void rgb2hsv(int r, int g, int b, int* h, int* s, int* v);

void hsv2rgb(int h, int s, int v, int* r, int* g, int* b);

Image newImageFromCloud(Cloud * c, Image * img);

CompressedImage newCompressedImageFromCloud(Cloud * c, Image * img, CLUTNode * root);

/*NODE*/

Node* newNode(Subset sub);

void addLeftNode(Subset sub, Node* father);

void addRightNode(Subset sub, Node* father);

void printAllChildren(int indentation, Node* n);

void freeAllChildren(Node* n);

void createTree(Node * n, int cpt, Cut cut, int actualCutAxe);

void modifyCloudFromTree(Cloud * c, CLUTNode * CLUT, Node * tree);


/*MENU*/

void Keyboard(unsigned char key, int x, int y);

void Mouse(int button, int state, int x, int y);

int Init(char *s);

int ReInit();

void Display(void);

void Reshape(int w, int h);

void menuFunc(int item);

void initWindow(int argc, char **argv);

void startGraphicalLoop();


/*CLUT*/

CLUTNode* newEmptyCLUTNode();

void setCLUTNode(GLubyte* data, usedType index, CLUTNode * n);

void addCLUTNodeChild(GLubyte* data, CLUTNode* father);

void freeAllCLUTChildren(CLUTNode* n);

usedType getIndexFromData(GLubyte* data, CLUTNode* father);

usedType getCLUTSize(CLUTNode* father);

void printAllCLUTChildren(CLUTNode* n);

void CLUTfileWriter(FILE *fp, CLUTNode* n);


/*COMPRESSION*/

void compressToBSP(char *filename, CompressedImage *img, CLUTNode* root);

Image loadCompressedBSP(char *filename);

void extractFromBSP(char *filename);
