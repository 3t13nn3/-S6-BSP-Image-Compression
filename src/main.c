#include "head.h"

int main(int argc, char **argv) {

	if (argc<5) {
		fprintf(stderr, "Usage : ./bsp myImage.ppm treeDepth firstCutAxe Proportion\n");
		exit(0);
	}
	else if((1 << atoi(argv[2])) > (int)(1 << (8 * sizeof(usedType)))){ //checking if we can stock the number of subset

		printf("Too much subset for the choosed type.\n");
		exit(0);
	}

	treeDepth = atoi(argv[2]);

	int firstCutAxe = atoi(argv[3]);
	int proportion = atoi(argv[4]);

	initWindow(argc, argv);
	

	Init(argv[1]);

#ifdef TIME

	clock_t start_t, end_t;
	double total_t;
	start_t = clock();

#endif

	Subset sub = newSubsetFromDimensions(H,S,V);
	Cut myc = getCutFromSubset(&sub, firstCutAxe, proportion);
	root = newNode(sub);

	createTree(root, treeDepth, myc, firstCutAxe);
	
	CLUT = newEmptyCLUTNode();
	modifyCloudFromTree(&myCloud, CLUT, root);

	compressed = newCompressedImageFromCloud(&myCloud, image, CLUT);

#ifdef TIME

	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("%f sec\n", total_t);

#endif

	new = newImageFromCloud(&myCloud, image);

	startGraphicalLoop();

	return 1;
}
