#include "head.h"

CLUTNode* newEmptyCLUTNode(){

	CLUTNode* toReturn = (CLUTNode*)malloc(sizeof(CLUTNode));
	assert(toReturn);

	toReturn->_child = NULL;
	toReturn->_data = NULL;
	toReturn->_index = -1;

	return toReturn;
}

void setCLUTNode(GLubyte* data, usedType index, CLUTNode * n){

	int i;

	n->_data = (GLubyte*)malloc((size_t) 3 * sizeof(GLubyte));

	for(i = 0; i< 3; ++i){
		n->_data[i] = data[i];
	}
	
	n->_index = index;
}

void addCLUTNodeChild(GLubyte* data, CLUTNode* father){

	while(father->_child != NULL){

		if(father->_child->_data[0] == data[0] && father->_child->_data[1] == data[1] && father->_child->_data[2] == data[2]){ //if the color is already in our CLUT

			return;
		}
		father = father->_child;

	}

	CLUTNode* n = newEmptyCLUTNode();
	setCLUTNode(data, father->_index + 1, n);

	father->_child = n;
}

usedType getIndexFromData(GLubyte* data, CLUTNode* father){
	
	while(father->_child != NULL){
		if(father->_child->_data[0] == data[0] && father->_child->_data[1] == data[1] && father->_child->_data[2] == data[2]){ //if the color is already in our CLUT
			//printf("%d %d %d %d %d %d\n", father->_child->_data[0], data[0], father->_child->_data[1], data[1], father->_child->_data[2], data[2]);
			break;
		}
		father = father->_child;
	}
	return father->_index + 1;
}

usedType getCLUTSize(CLUTNode* father){
	
	while(father->_child != NULL){
		father = father->_child;
	}
	return father->_index + 1;
}

void freeAllCLUTChildren(CLUTNode* n){

	if(n->_child != NULL){
		free(n->_data);
		freeAllCLUTChildren(n->_child);
	}
	free(n);
}

void printAllCLUTChildren(CLUTNode* n){

	printf("%d %d %d %d\n", n->_index, n->_data[0],n->_data[1],n->_data[2]);

	if(n->_child != NULL){
		
		printAllCLUTChildren(n->_child);
	}
}

void CLUTfileWriter(FILE *fp, CLUTNode* n, char type){

	if(n->_child != NULL){

		CLUTfileWriter(fp, n->_child, type);
	}

	GLubyte r, g, b;
	r = n->_data[0];
	g = n->_data[1];
	b = n->_data[2];

	if(type == 0){ //GLubyte

		GLubyte index;
		index = (GLubyte)n->_index;

		fwrite(&index, (size_t) 1, sizeof(GLubyte), fp);
	} else { //ushort

		unsigned short index;
		index = (unsigned short)n->_index;

		fwrite(&index, (size_t) 1, sizeof(unsigned short), fp);
	}
	fwrite(&r, (size_t) 1, sizeof(GLubyte), fp);
	fwrite(&g, (size_t) 1, sizeof(GLubyte), fp);
	fwrite(&b, (size_t) 1, sizeof(GLubyte), fp);
}
