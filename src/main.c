#include "head.h"

int main(int argc, char **argv) {

	if (argc<3) {
		fprintf(stderr, "Usage : ./bsp myImage.ppm treeDepth\n");
		exit(0);
	}
	else if(atoi(argv[2]) > 20){
		printf("Too much subset to create, depth of 20 is sufficient.\n");
		exit(0);
	}

	treeDepth = atoi(argv[2]);

	initWindow(argc, argv);
	Subset sub = newSubsetFromDimensions(H,S,V);
	Cut myc = getCutFromSubset(&sub, X_AXE);
	root = newNode(sub);

	createTree(root, treeDepth-1, myc, X_AXE);
	
	CLUT = newEmptyCLUTNode();
	//printAllChildren(0,root);

	Init(argv[1]);

	modifyCloudFromTree(&myCloud, CLUT, root);
	//printAllCLUTChildren(CLUT->_child);
	new = newImageFromCloud(&myCloud, image);
	compressed = newCompressedImageFromCloud(&myCloud, image, CLUT);
	startGraphicalLoop();

	return 1;
}
