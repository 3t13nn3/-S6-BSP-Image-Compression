#include "clut.h"
#include <stdio.h>
CLUT newCLUT(){
	
	CLUT toReturn;
	int i, j, k, l;

	/*ALLOCATING*/
	toReturn._data = malloc((size_t) SHADE * sizeof(GLubyte****));
	for(i = 0; i < SHADE; ++i){

		toReturn._data[i] = malloc((size_t) SHADE * sizeof(GLubyte***));

		for(j = 0; j < SHADE; ++j){

			toReturn._data[i][j] = malloc((size_t) SHADE * sizeof(GLubyte**));

			for(k = 0; k < SHADE; ++k){

				toReturn._data[i][j][k] = malloc((size_t) PIXEL_ELEMENTS * sizeof(GLubyte*));
				for(l = 0; l < PIXEL_ELEMENTS; ++l){

					toReturn._data[i][j][k][l] = malloc(sizeof(GLubyte));
				}
			}

		}
	}

	/*FILLING*/
	for(i = 0; i < SHADE; ++i){

		for(j = 0; j < SHADE; ++j){

			for(k = 0; k < SHADE; ++k){

				toReturn._data[i][j][k][0] = (GLubyte)i;
				toReturn._data[i][j][k][1] = (GLubyte)j;
				toReturn._data[i][j][k][2] = (GLubyte)k;
			}
		}
	}

	return toReturn;
}
