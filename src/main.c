#include "head.h"

Image* image;

/*Test function, care, cpt argument make 2^cpt nodes*/
void createTree(Node * n, int cpt) {
	if(cpt == 0 || cpt > 20)
		return;
	addLeftNode(newSegmentFromPoints(newPoint(-cpt,-cpt,-cpt*2),newPoint(-cpt,-cpt,-cpt*2)),newSubsetFromDimensions(-cpt,-cpt,-cpt*2),n,Y_AXE);
		createTree(n->_leftChild,cpt-1);
	addRightNode(newSegmentFromPoints(newPoint(cpt,cpt,cpt*2),newPoint(cpt,cpt,cpt*2)),newSubsetFromDimensions(cpt,cpt,cpt*2),n,Z_AXE);
		createTree(n->_rightChild,cpt-1);
}

int main(int argc, char **argv) {

	if (argc<2) {
		fprintf(stderr, "Usage : ./bsp myImage.ppm\n");
		exit(0);
	}

	initWindow(argc, argv);


	Segment seg = newSegmentFromPoints(newPoint(0,0,0),newPoint(0,0,0));
	Subset sub = newSubsetFromDimensions(360,256,256);
	/*Node* root = newNode(seg, sub, X_AXE);

	createTree(root, 2);
	printAllChildren(0,root);
	int h,s,v;
	int r,g,b;

	rgb2hsv(4, 25, 25,&h,&s,&v);

	hsv2rgb(180, 84, 10,&r,&g,&b);
*/

	CLUT myCLUT = newCLUT();
	freeCLUT(&myCLUT);
	Init(argv[1], &myCLUT);

	Cut myc = getCutFromSubset(&sub, Y_AXE);

	printCut(1, &myc);
	
	//printCLUT(&myCLUT);

	/*Subset s = newSubsetFromDimensions(image->sizeX, image->sizeY);
	printSubset(0, &s);

	Segment ss = getCutFromSubset(&s);
	printSegment(0, &ss);*/

	startGraphicalLoop();

	return 1;
}