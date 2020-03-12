#include "clut.h"
#include <stdio.h>
CLUT newCLUT(){
	
	CLUT toReturn;
	int i, j;

	/*ALLOCATING*/
	toReturn._data = malloc((size_t) SHADE * sizeof(char***));
	for(i = 0; i < SHADE; ++i){

		toReturn._data[i] = malloc((size_t) SHADE * sizeof(char**));

		for(j = 0; j < SHADE; ++j){

			toReturn._data[i][j] = malloc((size_t) SHADE * sizeof(char*));
		}
	}

	return toReturn;
}

void fillCLUTfromImage(CLUT * c, Image * img){

	int i;
	for(i = 0;  i < (int)(3 * img->sizeX * img->sizeY); ++i){
		if(!c->_data[img->data[i]][img->data[i+1]][img->data[i+2]]){
			c->_data[img->data[i]][img->data[i+1]][img->data[i+2]] = 1;
		}
	}
}

void printCLUT(CLUT * c){

	int i, j, k;
	for(i = 0; i < SHADE; ++i){

		for(j = 0; j < SHADE; ++j){

			for(k = 0; k < SHADE; ++k){
				if(c->_data[i][j][k])
					printf("%d,%d,%d %d\n", i, j, k, c->_data[i][j][k]);
			}
		}
	}
}
