#include "head.h"

int main(int argc, char **argv) {

	if (argc<3) {
		fprintf(stderr, "Usage : ./bsp myImage.ppm treeDepth\n");
		exit(0);
	}
	else if((1 << atoi(argv[2])) > (int)(1 << (8 * sizeof(usedType)))){ //checking if we can stock the number of subset

		printf("Too much subset for the choosed type.\n");
		exit(0);
	}

	treeDepth = atoi(argv[2]);

	initWindow(argc, argv);
	Subset sub = newSubsetFromDimensions(H,S,V);
	Cut myc = getCutFromSubset(&sub, X_AXE, 50);
	root = newNode(sub);

	createTree(root, treeDepth, myc, X_AXE);
	
	CLUT = newEmptyCLUTNode();
	//printCloud(&myCloud);
	//printAllChildren(0,root);

	Init(argv[1]);

	modifyCloudFromTree(&myCloud, CLUT, root);
	
	new = newImageFromCloud(&myCloud, image);
	compressed = newCompressedImageFromCloud(&myCloud, image, CLUT);
	printAllCLUTChildren(CLUT->_child);

	startGraphicalLoop();

	return 1;
}
