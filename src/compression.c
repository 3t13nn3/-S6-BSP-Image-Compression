#include "head.h"

void decimalToBinary(int number, char ** binaryNumber){

    int i, j;

    for (i = treeDepth - 1; i >= 0; i--){

        j = number >> i;

        if (j & 1) {

            (*binaryNumber)[i] = 1;
        } else {

            (*binaryNumber)[i] = 0;
        }
    }
}

int binaryToDecimal(char ** binary){

    int i, toReturn = 0;
    for(i = treeDepth - 1; i >= 0; i--){

        toReturn = toReturn << 1 | (*binary)[i];

    }
    return toReturn;
}

void compressToBSP(char *filename, CompressedImage *img, CLUTNode* root){

	FILE *fp;
	//open file for output
	fp = fopen(filename, "wb");
	if (!fp) {
	 fprintf(stderr, "Unable to open file '%s'\n", filename);
	 exit(1);
	}

    int nbColor = getCLUTSize(root);
    int cpt = 0;
    char type;

    if(treeDepth <= 8){
        type = 0;
    } else {
        type = 1;
    }

    fwrite(&type, (size_t) 1, sizeof(char), fp);

    if(treeDepth <= 8){
        //writing the number of subset of GLubyte
        GLubyte nbSubset = (GLubyte)getCLUTSize(root);
        fwrite(&nbSubset, (size_t) 1, sizeof(GLubyte), fp);
    } else {
        //writing the number of subset as ushort
        unsigned short nbSubset = (unsigned short)getCLUTSize(root);
        fwrite(&nbSubset, (size_t) 1, sizeof(unsigned short), fp);
    }

    //image size
    fwrite(&img->sizeX, (size_t) 1, sizeof(unsigned long), fp);
    fwrite(&img->sizeY, (size_t) 1, sizeof(unsigned long), fp);

    // clut
    CLUTfileWriter(fp, root->_child, type);


    char * binary= (char*)malloc(treeDepth * sizeof(char));

    // pixel data
    while(cpt < (int)(img->sizeY * img->sizeX)){

        unsigned long int dataToWrite = 0x00;
        
        for(int i = 0; i < (int)(floor(64/treeDepth)); ++i){

            decimalToBinary(img->data[cpt], &binary);

            for(int j = treeDepth - 1; j>=0; --j){

                if(binary[j] == 1){
                    dataToWrite |= 1UL << ((i * treeDepth) + j);
                }
            }
            ++cpt;
        }

        fwrite(&dataToWrite, (size_t) 1, (size_t)(sizeof(unsigned long int)), fp);
        
    }

    free(binary);
  
	fclose(fp);
}

Image loadCompressedBSP(char *filename){

    Image toReturn;

    FILE *fp;
    int size;

    int i;
    int cpt = 0;
    GLubyte* r;
    GLubyte* g;
    GLubyte* b;
    char type;

    //open PPM file for reading
    fp = fopen(filename, "rb");
    if (!fp) {
        fprintf(stderr, "Unable to open file '%s'\n", filename);
        exit(1);
    }

    fread(&type, sizeof(char), 1, fp);

    if(type == 0){ // using GLubyte for indexs

        GLubyte index;
        GLubyte nbSubset;

        fread(&nbSubset, sizeof(GLubyte), 1, fp);

        fread(&toReturn.sizeX, sizeof(unsigned long), 1, fp);
        fread(&toReturn.sizeY, sizeof(unsigned long), 1, fp);
        //printf("%lu %lu\n", toReturn.sizeX, toReturn.sizeY);

        r = (GLubyte*)malloc((size_t) nbSubset * sizeof(GLubyte));
        g = (GLubyte*)malloc((size_t) nbSubset * sizeof(GLubyte));
        b = (GLubyte*)malloc((size_t) nbSubset * sizeof(GLubyte));

        while (cpt < nbSubset){

            GLubyte aa,bb,cc;

            fread(&index, sizeof(GLubyte), 1, fp);
            fread(&aa, sizeof(GLubyte), 1, fp);
            fread(&bb, sizeof(GLubyte), 1, fp);
            fread(&cc, sizeof(GLubyte), 1, fp);
            r[(int)index]=aa;
            g[(int)index]=bb;
            b[(int)index]=cc;

            cpt++;
        }

        /* allocation memoire */
        size = toReturn.sizeX * toReturn.sizeY * 3;

        toReturn.data = (GLubyte *) malloc ((size_t) size * sizeof (GLubyte));
        assert(toReturn.data);
        //read pixel data from file
        char * binary= (char*)malloc(treeDepth * sizeof(char));
        unsigned long int binarysData;
        

        i = 0;
        while ( i < (int)(toReturn.sizeX * toReturn.sizeY)){

            fread(&binarysData, sizeof(unsigned long int), 1, fp);
            
            for(int j = 0; j < (int)(floor(64/treeDepth)); ++j){
                for(int k = treeDepth - 1; k>=0; --k){

                    binary[k] = (char)(binarysData >> ((j * treeDepth) + k)) & 0x01;
                }
                index = (GLubyte)binaryToDecimal(&binary);

                toReturn.data[(int)i*3] = r[index];
                toReturn.data[(int)(i*3)+1] = g[index];
                toReturn.data[(int)(i*3)+2] = b[index];

                i++;
            }
        }
    } else { //using ushort for indexs
    
        unsigned short index;
        unsigned short nbSubset;

        fread(&nbSubset, sizeof(unsigned short), 1, fp);

        fread(&toReturn.sizeX, sizeof(unsigned long), 1, fp);
        fread(&toReturn.sizeY, sizeof(unsigned long), 1, fp);
        //printf("%lu %lu\n", toReturn.sizeX, toReturn.sizeY);

        r = (GLubyte*)malloc((size_t) nbSubset * sizeof(GLubyte));
        g = (GLubyte*)malloc((size_t) nbSubset * sizeof(GLubyte));
        b = (GLubyte*)malloc((size_t) nbSubset * sizeof(GLubyte));

        while (cpt < nbSubset){

            GLubyte aa,bb,cc;

            fread(&index, sizeof(unsigned short), 1, fp);
            fread(&aa, sizeof(GLubyte), 1, fp);
            fread(&bb, sizeof(GLubyte), 1, fp);
            fread(&cc, sizeof(GLubyte), 1, fp);
            r[(int)index]=aa;
            g[(int)index]=bb;
            b[(int)index]=cc;

            cpt++;
        }
        
        /* allocation memoire */
        size = toReturn.sizeX * toReturn.sizeY * 3;

        toReturn.data = (GLubyte *) malloc ((size_t) size * sizeof (GLubyte));
        assert(toReturn.data);
        
        char * binary= (char*)malloc(treeDepth * sizeof(char));
        unsigned long int binarysData;
        

        i = 0;
        while ( i < (int)(toReturn.sizeX * toReturn.sizeY)){

            fread(&binarysData, sizeof(unsigned long int), 1, fp);
            
            for(int j = 0; j < (int)(floor(64/treeDepth)); ++j){
                for(int k = treeDepth - 1; k>=0; --k){

                    binary[k] = (char)(binarysData >> ((j * treeDepth) + k)) & 0x01;
                }
                index = (unsigned short)binaryToDecimal(&binary);

                toReturn.data[(int)i*3] = r[index];
                toReturn.data[(int)(i*3)+1] = g[index];
                toReturn.data[(int)(i*3)+2] = b[index];

                i++;
            }
        }
    }

    fclose(fp);

    return toReturn;
}
