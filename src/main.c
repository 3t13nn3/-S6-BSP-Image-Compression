#include "head.h"

Image* image;
CLUT myCLUT;

int main(int argc, char **argv) {

	if (argc<2) {
		fprintf(stderr, "Usage : ./bsp myImage.ppm\n");
		exit(0);
	}

	initWindow(argc, argv);

	Subset sub = newSubsetFromDimensions(360,256,256);
	Cut myc = getCutFromSubset(&sub, X_AXE);
	Node* root = newNode(myc, sub, X_AXE);

	createTree(root, 9);
	printAllChildren(0,root);
	freeAllChildren(root);

	myCLUT = newCLUT();
	Init(argv[1]);

	//

	//printCut(1, &myc);
	
	//printCLUT(&myCLUT);

	/*Subset s = newSubsetFromDimensions(image->sizeX, image->sizeY);
	printSubset(0, &s);

	Segment ss = getCutFromSubset(&s);
	printSegment(0, &ss);*/

	startGraphicalLoop();

	return 1;
}