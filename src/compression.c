#include "head.h"

void compressToBSP(char *filename, CompressedImage *img, CLUTNode* root){

	FILE *fp;
	//open file for output
	fp = fopen(filename, "wb");
	if (!fp) {
	 fprintf(stderr, "Unable to open file '%s'\n", filename);
	 exit(1);
	}

    usedType nbSubset = getCLUTSize(root);
    //printf("%d\n", nbSubset);

    //writing the number of subset
    fwrite(&nbSubset, (size_t) 1, sizeof(usedType), fp);

	//image size
    fwrite(&img->sizeX, (size_t) 1, sizeof(unsigned long), fp);
    fwrite(&img->sizeY, (size_t) 1, sizeof(unsigned long), fp);

	// clut
	CLUTfileWriter(fp, root->_child);

	// pixel data
	int cpt = img->sizeY - 1;

	while(cpt >= 0){
        fwrite(&img->data[cpt * img->sizeX], (size_t) 1, (size_t) (img->sizeX)*(sizeof(usedType)), fp);
        //printf("%d\n", (img->data[cpt * img->sizeX]));
        --cpt;
	}
    
    
	fclose(fp);
}

Image loadCompressedBSP(char *filename){

    Image toReturn;

    FILE *fp;
    unsigned long bb;
    int c, size, sizex;
    GLubyte tmp, * ptrdeb, *ptrfin, *lastline;

    int i;
    int cpt = 0;
    GLubyte* r;
    GLubyte* g;
    GLubyte* b;
    usedType index;
    usedType nbSubset;

    //open PPM file for reading
    fp = fopen(filename, "rb");
    if (!fp) {
        fprintf(stderr, "Unable to open file '%s'\n", filename);
        exit(1);
    }

    fread(&nbSubset, sizeof(usedType), 1, fp);
    //printf("%dok\n", nbSubset);

    fread(&toReturn.sizeX, sizeof(unsigned long), 1, fp);
    fread(&toReturn.sizeY, sizeof(unsigned long), 1, fp);
    //printf("%lu %lu\n", toReturn.sizeX, toReturn.sizeY);

    r = (GLubyte*)malloc((size_t) nbSubset * sizeof(GLubyte));
    g = (GLubyte*)malloc((size_t) nbSubset * sizeof(GLubyte));
    b = (GLubyte*)malloc((size_t) nbSubset * sizeof(GLubyte));

    while (cpt < nbSubset){

        GLubyte aa,bb,cc;

        fread(&index, sizeof(usedType), 1, fp);
        fread(&aa, sizeof(GLubyte), 1, fp);
        fread(&bb, sizeof(GLubyte), 1, fp);
        fread(&cc, sizeof(GLubyte), 1, fp);
        r[(int)index]=aa;
        g[(int)index]=bb;
        b[(int)index]=cc;
        //printf("%d %d %d %d\n", index, r[(int)index], g[(int)index], b[(int)index]);
        cpt++;
    }
    

	/* allocation memoire */
	size = toReturn.sizeX * toReturn.sizeY * 3;
	//printf("Size image %lu %lu => %d\n", toReturn.sizeX, toReturn.sizeY, size);
	toReturn.data = (GLubyte *) malloc ((size_t) size * sizeof (GLubyte));
	assert(toReturn.data);
    

    //read pixel data from file
    for(i = 0; i < (int)(toReturn.sizeX * toReturn.sizeY); i ++){
        //lit mal ici
        fread(&index, sizeof(usedType), 1, fp);
        //printf("%d\n", (int)index);
        toReturn.data[i*3] = r[index];
        toReturn.data[(i*3)+1] = g[index];
        toReturn.data[(i*3)+2] = b[index];
    }
    /*if (fread(toReturn.data, (size_t) 1, (size_t) size, fp) == 0) {
         fprintf(stderr, "Error loading image '%s'\n", filename);
         exit(1);
    }*/

	/* remettre l image dans le bon sens */
	sizex = toReturn.sizeX;
	//sizey = toReturn.sizeY;
	lastline = toReturn.data + size - sizex * 3;
	for (bb = 0; bb < toReturn.sizeY / 2; bb++) {
	  ptrdeb = toReturn.data + bb * sizex * 3;
	  ptrfin = lastline - (bb * sizex * 3);
	//	printf("%d => %ld %ld\n", b, (int) ptrdeb, (int) ptrfin);
	  for (c = 0; c < 3 * sizex; c++) {
		  tmp = *ptrdeb;
		  *ptrdeb = *ptrfin;
		  *ptrfin = tmp;
		  ptrfin++;
		  ptrdeb++;
	  }		
	}
    fclose(fp);

    return toReturn;
}
