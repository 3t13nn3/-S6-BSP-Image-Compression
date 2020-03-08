#include "head.h"

Image *image;

int main(int argc, char **argv) {

	if (argc<2) {
	fprintf(stderr, "Usage : ./bsp myImage.ppm\n");
	exit(0);
	}

	initWindow(argc, argv);


	Init(argv[1]);

	startGraphicalLoop();

	return 1;
}