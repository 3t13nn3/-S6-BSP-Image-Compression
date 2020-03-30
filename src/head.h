#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <time.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define TIME

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

#ifdef GLUBYTE
  typedef GLubyte usedType;
#else
  typedef unsigned short usedType;
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
int treeDepth;

/*PPM*/

int ImageLoad_PPM(char *filename, Image *image);

void imagesave_PPM(char *filename, Image *img);

/*POINT*/

//create a new point with 3 coordinates
Point newPoint(short x, short y, short z);

//point setter
void setPoint(short x, short y, short z, Point* p);

//point printer
void printPoint(int nbTabulation, Point* p);


/*SUBSET*/

/*
Subset representation:
		^  5--------------6
		Z /|			 /|
		 / |	X>	  / |
		1--------------2  |
		|  7-----------|--8
	  Y | /			| /
	 \/ |/			 |/
		3--------------4

------------->				   1			  2			   3			  4			   5			   6				7			   8		*/
Subset newSubsetFromPoints(Point topLeft, Point topRight, Point botLeft, Point botRight, Point topZLeft, Point topZRight, Point botZLeft, Point botZRight);

//Generate a subset from a 3D dimension
Subset newSubsetFromDimensions(short firstDimensionSize, short secondDimensionSize, short thirdDimensionSize);

//subset printer
void printSubset(int nbTabulation, Subset * s);


/*CUT*/

//create a cut witch is a plan
Cut newCutFromPoints(Point a, Point b, Point c, Point d);

//create a cut from a subset, can choose where the cut is in fucntion of proprtion and axes
Cut getCutFromSubset(Subset * sub, int cutAxe, int pourcentage);

//cut printer
void printCut(int indentation, Cut * c);


/*Cloud*/

//filling our cloud color in function, of our image
void fillCloudfromImage(Cloud * c, Image * img);

//cloud printer
void printCloud(Cloud * c);

void rgb2hsv(int r, int g, int b, int* h, int* s, int* v);

void hsv2rgb(int h, int s, int v, int* r, int* g, int* b);

//for preview
Image newImageFromCloud(Cloud * c, Image * img);

//create an image based on CLUT index
CompressedImage newCompressedImageFromCloud(Cloud * c, Image * img, CLUTNode * root);

/*NODE*/

//create a BSP node
Node* newNode(Subset sub);

void addLeftNode(Subset sub, Node* father);

void addRightNode(Subset sub, Node* father);

//BSP node printer
void printAllChildren(int indentation, Node* n);

void freeAllChildren(Node* n);

//Creating our BSP tree in function of axe, init cut, and depth
void createTree(Node * n, int cpt, Cut cut, int actualCutAxe);

//Editing our Cloud in function of different BSP spaces
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

//Creating a CLUT node
CLUTNode* newEmptyCLUTNode();

//Set data of a CLUT node
void setCLUTNode(GLubyte* data, usedType index, CLUTNode * n);

//Add a child to our CLUT
void addCLUTNodeChild(GLubyte* data, CLUTNode* father);

//free
void freeAllCLUTChildren(CLUTNode* n);

//return an idex from a data
usedType getIndexFromData(GLubyte* data, CLUTNode* father);

//return total size
usedType getCLUTSize(CLUTNode* father);

//printer
void printAllCLUTChildren(CLUTNode* n);

//Write ou CLUT in our compressed Image
void CLUTfileWriter(FILE *fp, CLUTNode* n, char type);


/*COMPRESSION*/


void decimalToBinary(int number, char ** binaryNumber);

int binaryToDecimal(char ** binary);

//Write ou compressed image into a file
void compressToBSP(char *filename, CompressedImage *img, CLUTNode* root);

//recovery compressed image from a file
Image loadCompressedBSP(char *filename);
