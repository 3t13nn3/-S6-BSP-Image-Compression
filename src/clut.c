#include "head.h"

CLUTNode* newEmptyCLUTNode(){

	CLUTNode* toReturn = (CLUTNode*)malloc(sizeof(CLUTNode));
	assert(toReturn);

	toReturn->_child = NULL;
    toReturn->_data = NULL;
    toReturn->_index = -1;

	return toReturn;
}

void setCLUTNode(short* data, short index, CLUTNode * n){

    int i;

    n->_data = (short*)malloc((size_t) 3 * sizeof(short));

    for(i = 0; i< 3; ++i){
	    n->_data[i] = data[i];
    }
    
	n->_index = index;
}

/*Return the index of the new node*/
void addCLUTNodeChild(short* data, CLUTNode* father){

    while(father->_child != NULL){

        if(father->_child->_data[0] == data[0] && father->_child->_data[1] == data[1] && father->_child->_data[2] == data[2]){ //if the color is already in our CLUT
            return;
        }
        father = father->_child;
    }

    CLUTNode* n = newEmptyCLUTNode();
    setCLUTNode(data, father->_index + 1, n);

    father->_child = n;
    //printf("%d\n",father->_index);
}

GLubyte getIndexFromData(short* data, CLUTNode* father){
    
    while(father->_child != NULL){
                
        if(father->_child->_data[0] == data[0] && father->_child->_data[1] == data[1] && father->_child->_data[2] == data[2]){ //if the color is already in our CLUT
            //printf("%d %d %d %d %d %d\n", father->_child->_data[0], data[0], father->_child->_data[1], data[1], father->_child->_data[2], data[2]);
            break;
        }
        father = father->_child;
    }
    return (GLubyte)father->_index;
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

void CLUTfileWriter(FILE *fp, CLUTNode* n){
    
    fprintf(fp," %d %d %d %d", n->_index, n->_data[0],n->_data[1],n->_data[2]);

	if(n->_child != NULL){

		printAllCLUTChildren(n->_child);
	}
}
