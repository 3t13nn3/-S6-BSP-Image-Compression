#include "head.h"

Image* image;
Image new;
CLUT myCLUT;
Node* root;

int main(int argc, char **argv) {

	if (argc<3) {
		fprintf(stderr, "Usage : ./bsp myImage.ppm treeDepth\n");
		exit(0);
	}

	initWindow(argc, argv);

	Subset sub = newSubsetFromDimensions(360,256,256);
	Cut myc = getCutFromSubset(&sub, X_AXE);
	root = newNode(myc, sub, X_AXE);

	createTree(root, atoi(argv[2]));
	//printAllChildren(0,root);

	myCLUT = newCLUT();

	Init(argv[1]);

	fillCLUTfromImage(&myCLUT,image);
	modifyCLUTFromTree(&myCLUT, root);

	startGraphicalLoop();

	return 1;
}