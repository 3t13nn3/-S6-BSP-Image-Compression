#include "head.h"

Image* image;
Image new;
Cloud myCloud;
Node* root;

int main(int argc, char **argv) {

	if (argc<3) {
		fprintf(stderr, "Usage : ./bsp myImage.ppm treeDepth\n");
		exit(0);
	}

	initWindow(argc, argv);

	Subset sub = newSubsetFromDimensions(360,256,256);
	Cut myc = getCutFromSubset(&sub, X_AXE);
	root = newNode(sub);

	createTree(root, atoi(argv[2]), myc, X_AXE);

	Init(argv[1]);

	fillCloudfromImage(&myCloud,image);
	modifyCloudFromTree(&myCloud, root);

	startGraphicalLoop();

	return 1;
}