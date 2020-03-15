#include "clut.h"

CLUT newCLUT(){
	
	CLUT toReturn;
	int i, j;

	/*ALLOCATING*/
	toReturn._data = malloc((size_t) H * sizeof(char***));
	for(i = 0; i < H; ++i){

		toReturn._data[i] = malloc((size_t) S * sizeof(char**));

		for(j = 0; j < S; ++j){

			toReturn._data[i][j] = malloc((size_t) V * sizeof(char*));
		}
	}

	return toReturn;
}

void fillCLUTfromImage(CLUT * c, Image * img){

	int i;
	for(i = 0;  i < (int)(3 * img->sizeX * img->sizeY); ++i){
		//Very usefull test, considfrable gain of speed by checking if this color is already affected
		//Affecting a variable as a higher cost than a simple test, we don't want to reafect a variable
		if(!c->_data[img->data[i]][img->data[i+1]][img->data[i+2]]){
			c->_data[img->data[i]][img->data[i+1]][img->data[i+2]] = 1;
		}
	}
}

void printCLUT(CLUT * c){

	int i, j, k;
	for(i = 0; i < H; ++i){

		for(j = 0; j < S; ++j){

			for(k = 0; k < V; ++k){
				if(c->_data[i][j][k])
					printf("%d,%d,%d %d\n", i, j, k, c->_data[i][j][k]);
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
	*v = floor(max);
	//printf("r %d  g %d  b %d delat %f\n", r, g, b, delta);

	//Test delta first because delta will be used in division and we don't want to divide by 0
	if(delta == 0){
		h = 0;
		s = 0;
		return;
	}

	//Hue Calculation
	if(r == max)
		*h = floor((g - b)/delta) * 60;
	else if(g == max)
		*h = floor(((b - r)/delta)+2) * 60;
	else
		*h = floor(((r - g)/delta)+4) * 60;


	//Saturation calculation
	if(max == 0){
		*s = 0;
	} else {
		*s = floor(delta*256/max);
	}
	//printf("r %d  g %d  b %d \n", r, g, b);

	//printf("h %d  s %d  v %d \n", *h, *s ,*v);
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

	*r = (rt+m)*256;
	*g = (gt+m)*256;
	*b = (bt+m)*256;
}
