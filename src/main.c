#include "head.h"

Image* image;

/*Test function, care, cpt argument make 2^cpt nodes*/
void createTree(Node * n, int cpt) {
	if(cpt == 0 || cpt > 20)
		return;
	addLeftNode(newSegmentFromPoints(newPoint(-cpt,-cpt),newPoint(-cpt,-cpt)),newSubsetFromDimensions(-cpt,-cpt),n);
		createTree(n->_leftChild,cpt-1);
	addRightNode(newSegmentFromPoints(newPoint(cpt,cpt),newPoint(cpt,cpt)),newSubsetFromDimensions(cpt,cpt),n);
		createTree(n->_rightChild,cpt-1);
}

int main(int argc, char **argv) {

	if (argc<2) {
	fprintf(stderr, "Usage : ./bsp myImage.ppm\n");
	exit(0);
	}

	initWindow(argc, argv);


	/*Segment seg = newSegmentFromPoints(newPoint(0,0),newPoint(0,0));
	Subset sub = newSubsetFromDimensions(0,0);
	Node* root = newNode(seg, sub);

	createTree(root, 2);
	printAllChildren(0,root);*/

	Init(argv[1]);

	/*Subset s = newSubsetFromDimensions(image->sizeX, image->sizeY);
	printSubset(0, &s);

	Segment ss = getCutFromSubset(&s);
	printSegment(0, &ss);*/

	CLUT myCLUT = newCLUT();

	startGraphicalLoop();

	return 1;
}