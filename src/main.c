#include "head.h"

int main(int argc, char **argv) {

	int r,g,b,h,s,v;

	/*for(int i = 0; i < 360; ++i){
		for(int j = 0; j < 256; j++){
			for(int k = 0; k < 256; k++){	

				rgb2hsv(i,j,k, &h,&s,&v);

				printf("%d %d %d\n", h, s, v);

				hsv2rgb(h, s, v, &r, &g, &b);

				printf("%d %d %d\n", r, g, b);
			}
		}
	}*/

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
