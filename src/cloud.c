#include "head.h"

void fillCloudfromImage(Cloud * c, Image * img){

	int i;
	int h = 0;
	int s = 0;
	int v = 0;
	for(i = 0;  i < (int)(3 * img->sizeX * img->sizeY); ++i){

		//converting RGB (image pixel) to HSV for our Cloud format
		rgb2hsv(img->data[i], img->data[i+1], img->data[i+2], &h, &s, &v);

		//printf("%d,%d,%d\n",img->data[i], img->data[i+1], img->data[i+2]);
		//printf("--->%d,%d,%d\n", h,s,v);
		//Affecting a variable as a higher cost than a simple test, we don't want to reafect a variable
		if(!c->_data[h][s][v][0]){
			c->_data[h][s][v][0] = h;
			c->_data[h][s][v][1] = s;
			c->_data[h][s][v][2] = v;
		}
	}
}

void printCloud(Cloud * c){

	int i, j, k;
	for(i = 0; i < H; ++i){

		for(j = 0; j < S; ++j){

			for(k = 0; k < V; ++k){
				if(c->_data[i][j][k][0]){
					printf("%d,%d,%d -> %d, %d, %d\n", i, j, k, c->_data[i][j][k][0], c->_data[i][j][k][1], c->_data[i][j][k][2]);
				}
			}
		}
	}
}


void rgb2hsv(int r, int g, int b, int* h, int* s, int* v){

	//keeping the lower part of rgb
	int min = r < g ? r : g;
	min = min < b ? min : b;

	//keeping the max part of rgb
	int max = r > g ? r : g;
	max = max > b ? max : b;

	double delta = max - min;
	//value
	*v = max;
	//printf("r %d  g %d  b %d delat %f\n", r, g, b, delta);

	//Test delta first because delta will be used in division and we don't want to divide by 0
	if(delta == 0){
		h = 0;
		s = 0;
		return;
	}

	//Hue Calculation
	if(r == max){
		*h = ((g - b)/delta) * 60;
	}
	else if(g == max)
		*h = (((b - r)/delta)+2) * 60;
	else
		*h = (((r - g)/delta)+4) * 60;


	//Saturation calculation
	if(max == 0){
		*s = 0;
	} else {
		*s = delta*255/max;
	}

	//angle couldn't be negativ, then add a complete round in degree
	if(*h < 0)
		*h+=360;

}

void hsv2rgb(int h, double s, double v, int* r, int* g, int* b){

	//We made calculus on double and at least giving them to integer pointer
	double rt = 0;
	double gt = 0;
	double bt = 0;

	//tranlate saturation and value into [0;1] range
	s/=100;
	v/=100;

	double c = s * v;
	double x = c * (1 - abs( ( (h/60)%2 ) - 1) );
	double m = v - c;

	//avoid if else condition by using switch
	int part = ceil(h/60);
	switch(part){
		case 1: //if(0 <= h && h < 60)
			rt = c;
			gt = x;
			bt = 0;
			break;
		case 2: //if(60 <= h && h < 120)
			rt = x;
			gt = c;
			bt = 0;
			break;
		case 3: //if(120 <= h && h < 180)
			rt = 0;
			gt = c;
			bt = x;
			break;
		case 4: //if(180 <= h && h < 240)
			rt = 0;
			gt = x;
			bt = c;
			break;
		case 5: //if(240 <= h && h < 300)
			rt = x;
			gt = 0;
			bt = c;
			break;
		case 6: //if(300 <= h && h < 360)
			rt = c;
			gt = 0;
			bt = x;
			break;

	}

	*r = (rt+m)*255;
	*g = (gt+m)*255;
	*b = (bt+m)*255;
}

Image newImageFromCloud(Cloud * c, Image * img){

	int i, h = 0, s = 0, v = 0, r = 0, g = 0, b = 0;
	int size = img->sizeX * img->sizeY * 3;
	Image new = *img;

	for(i = 0; i< size; i+=3){

		rgb2hsv(img->data[i], img->data[i+1], img->data[i+2], &h, &s, &v);
		//printf("%d %d %d\n", c->_data[h][s][v][0],c->_data[h][s][v][1],c->_data[h][s][v][2]);
		hsv2rgb(c->_data[h][s][v][0], c->_data[h][s][v][1], c->_data[h][s][v][2], &r, &g, &b);
		//printf("----->%d %d %d\n", r, g, b);
		new.data[i] = (GLubyte)r;
		new.data[i+1] = (GLubyte)g;
		new.data[i+2] = (GLubyte)b;
		
	}
	return new;
}
