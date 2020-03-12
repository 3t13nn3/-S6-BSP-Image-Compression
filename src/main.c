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
#include <math.h>

void rgb2hsv(int r, int g, int b){

	int h;
	int s;
	int v;

	//keeping the lower part of rgb
	int min = r < g ? r : g;
	min = min < b ? min : b;

	//keeping the max part of rgb
	int max = r > g ? r : g;
	max = max > b ? max : b;

	double delta = max - min;
	//value
	v = round(max);
	printf("r %d  g %d  b %d delat %f\n", r, g, b, delta);

	//Test delta first because delta will be used in division and we don't want to divide by 0
	if(delta == 0){
		h = 0;
		s = 0;
		return;
	}
	//Hue Calculation
	if(r == max)
		h = round((g - b)/delta) * 60;
	else if(g == max)
		h = round(((b - r)/delta)+2) * 60;
	else
		h = round(((r - g)/delta)+4) * 60;


	//Saturation calculation
	if(max == 0){
		s = 0;
	} else {
		s = round(delta*256/max);
	}
	printf("r %d  g %d  b %d \n", r, g, b);

	printf("h %d  s %d  v %d \n", h, s ,v);
}

void hsv2rgb(int h, double s, double v){
	double r, g, b;

	s/=100;
	v/=100;

	double c = s * v;
	printf("%f\ %f %f \n", c, s, v);
	double x = c * (1 - abs(((h/60)%2) - 1));
	double m = v - c;

	int part = ceil(x/60);
	printf("%d\n", x);
	switch(part){
		case 1: //if(0 <= h && h < 60)
			r = c;
			g = x;
			b = 0;
			break;
		case 2: //if(60 <= h && h < 120)
			r = x;
			g = c;
			b = 0;
			break;
		case 3: //if(120 <= h && h < 180)
			r = 0;
			g = c;
			b = x;
			break;
		case 4: //if(180 <= h && h < 240)
			r = 0;
			g = x;
			b = c;
			break;
		case 5: //if(240 <= h && h < 300)
			r = x;
			g = 0;
			b = c;
			break;
		case 6: //if(300 <= h && h < 360)
			r = c;
			g = 0;
			b = x;
			break;

	}

	/*if(0 <= h && h < 60){
		r = c;
		g = x;
		b = 0;
	} else if(60 <= h && h < 120){
		r = x;
		g = c;
		b = 0;
	} else if(120 <= h && h < 180){
		r = 0;
		g = c;
		b = x;
	} else if(180 <= h && h < 240){
		r = 0;
		g = x;
		b = c;
	} else if(240 <= h && h < 300){
		r = x;
		g = 0;
		b = c;
	} else if(300 <= h && h < 360){
		r = c;
		g = 0;
		b = x;
	}*/

	r = (r+m)*255;
	g = (g+m)*255;
	b = (b+m)*255;

	printf("r %d  g %d  b %d \n", r, g, b);

	printf("h %d  s %d  v %d \n", h, s ,v);

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
	rgb2hsv(4, 25, 25);

	hsv2rgb(10, 61, 80);


	CLUT myCLUT = newCLUT();

	Init(argv[1], &myCLUT);
	//printCLUT(&myCLUT);

	/*Subset s = newSubsetFromDimensions(image->sizeX, image->sizeY);
	printSubset(0, &s);

	Segment ss = getCutFromSubset(&s);
	printSegment(0, &ss);*/

	startGraphicalLoop();

	return 1;
}