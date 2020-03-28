#include "head.h"

void fillCloudfromImage(Cloud * c, Image * img){

	int i;
	int h = 0;
	int s = 0;
	int v = 0;

	for(i = 0;  i < (int)(3 * img->sizeX * img->sizeY); ++i){

		//converting RGB (image pixel) to HSV for our Cloud format
		rgb2hsv(img->data[i], img->data[i+1], img->data[i+2], &h, &s, &v);

		//Affecting a variable as a higher cost than a simple test, we don't want to reafect a variable
		if(c->_data[h][s][v] == NULL){
			
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
				if(c->_data[i][j][k] != NULL){
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
		*h+=359;

}

/*
void hsv2rgb(int h, double s, double v, int* r, int* g, int* b){

	//We made calculus on double and at least giving them to integer pointer
	double rt = 0;
	double gt = 0;
	double bt = 0;
	

	//tranlate saturation and value into [0;1] range
	
	s/=255;
	v/=255;
	//printf("%f %f \n", s , v);
	double c = s * v;
	double x = c * (1 - abs( ( (h/60)%2 ) - 1) );
	double m = v - c;

	//avoid if else condition by using switch
	int part = ceil(h/60);
	switch(part){
		case 1: //if(0 <= h && h < 60)
			*r = (int) c + m;
			*g = (int) x + m;
			*b = (int) m;
			break;
		case 2: //if(60 <= h && h < 120)
			*r = (int) x + m;
			*g = (int) c + m;
			*b = (int) m;
			break;
		case 3: //if(120 <= h && h < 180)
			*r = (int) m;
			*g = (int) c + m;
			*b = (int) x + m;
			break;
		case 4: //if(180 <= h && h < 240)
			*r = (int) m;
			*g = (int) x + m;
			*b = (int) c + m;
			break;
		case 5: //if(240 <= h && h < 300)
			*r = (int) x + m;
			*g = (int) m;
			*b = (int) c + m;
			break;
		case 6: //if(300 <= h && h < 360)
			*r = (int) c + m;
			*g = (int) m;
			*b = (int) x + m;
			break;
	}

	*r = (int)(rt+m)*255;
	*g = (int)(gt+m)*255;
	*b = (int)(bt+m)*255;
}*/

/*https://stackoverflow.com/questions/3018313/algorithm-to-convert-rgb-to-hsv-and-hsv-to-rgb-in-range-0-255-for-both*/
void hsv2rgb(int h, int s, int v, int* r, int* g, int* b){

    int rr,gg,bb;
    unsigned char region, remainder, p, q, t;

	h = h *255 / 359;

	//printf("%d %d %d\n", h, s , v);
    if (s == 0)
    {
        rr = v;
        gg = v;
        bb = v;
		*r = rr;
		*g = gg;
		*b = bb;
        return;
    }

    region = h / 43;
    remainder = (h - (region * 43)) * 6; 

    p = (v * (255 - s)) >> 8;
    q = (v * (255 - ((s * remainder) >> 8))) >> 8;
    t = (v * (255 - ((s * (255 - remainder)) >> 8))) >> 8;

    switch (region)
    {
        case 0:
            rr = v; gg = t; bb = p;
            break;
        case 1:
            rr = q; gg = v; bb = p;
            break;
        case 2:
            rr = p; gg = v; bb = t;
            break;
        case 3:
            rr = p; gg = q; bb = v;
            break;
        case 4:
            rr = t; gg = p; bb = v;
            break;
        default:
            rr = v; gg = p; bb = q;
            break;
    }

	//printf("%d %d %d \n", rr, gg ,bb);
	*r = rr;
	*g = gg;
	*b = bb;
}


Image newImageFromCloud(Cloud * c, Image * img){

	int i, h = 0, s = 0, v = 0, r = 0, g = 0, b = 0;
	Image new;
	new.sizeX = img->sizeX;
	new.sizeY = img->sizeY;
	int size = new.sizeX * new.sizeY * 3;
	new.data = (GLubyte *) malloc ((size_t) size * sizeof (GLubyte));

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

CompressedImage newCompressedImageFromCloud(Cloud * c, Image * img, CLUTNode * root){

	int i, h = 0, s = 0, v = 0, r = 0, g = 0, b = 0;
	CompressedImage new;
	new.sizeX = img->sizeX;
	new.sizeY = img->sizeY;
	int size = new.sizeX * new.sizeY;
	new.data = (usedType *) malloc ((size_t) size * sizeof (usedType));

	GLubyte* CLUTData = (GLubyte*)malloc((size_t) 3 * sizeof(GLubyte));

	for(i = 0; i< size * 3; i += 3 ){

		rgb2hsv(img->data[i], img->data[i+1], img->data[i+2], &h, &s, &v);

		hsv2rgb(c->_data[h][s][v][0], c->_data[h][s][v][1], c->_data[h][s][v][2], &r, &g, &b);


		CLUTData[0] = r;
		CLUTData[1] = g;
		CLUTData[2] = b;
		

		new.data[(int)i/3] = getIndexFromData(CLUTData, root);
		
	}
    free(CLUTData);

	return new;
}
