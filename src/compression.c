#include "head.h"

void compressToBSP(char *filename, Image *img, CLUTNode* root){

	FILE *fp;
	//open file for output
	fp = fopen(filename, "wb");
	if (!fp) {
	 fprintf(stderr, "Unable to open file '%s'\n", filename);
	 exit(1);
	}

    //format
    fprintf(fp, "BSP\n");
    //nb of subspaces 2<<(nb)
    GLubyte nbSubset = getCLUTSize(root);

    fwrite(&nbSubset, (size_t) 1, sizeof(GLubyte), fp);
    fprintf(fp, "\n");
	//comments
	fprintf(fp, "# Created by EP\n");

	//image size
	fprintf(fp, "%lu %lu\n",img->sizeX,img->sizeY);

	// clut
	CLUTfileWriter(fp, root->_child);
	fprintf(fp, "\n");

	// pixel data
	int cpt = img->sizeY - 1;

	while(cpt >= 0){
        fwrite(&img->data[cpt * img->sizeX], (size_t) 1, (size_t) (img->sizeX), fp);
        --cpt;
	}
    
    
	fclose(fp);
}

Image loadCompressedBSP(char *filename){

    Image toReturn;

    char d, buff[16];
    FILE *fp;
    unsigned long b;
    int c, rgb_comp_color, size, sizex;//, sizey;
    GLubyte tmp, * ptrdeb, *ptrfin, *lastline;

    int i;
    int cpt = 0;
    GLubyte clutSize;
    GLubyte* h;
    GLubyte* s;
    GLubyte* v;
    GLubyte index;
    GLubyte nbSubset;

    //open PPM file for reading
    fp = fopen(filename, "rb");
    if (!fp) {
        fprintf(stderr, "Unable to open file '%s'\n", filename);
        exit(1);
    }

    //read image format
    if (!fgets(buff, sizeof(buff), fp)) {
        perror(filename);
        exit(1);
    }

    //check the image format
    if (buff[0] != 'B' || buff[1] != 'S' || buff[2] != 'P') {
         fprintf(stderr, "Invalid image format (must be 'BSP')\n");
         exit(1);
    }

    fread(&nbSubset, sizeof(GLubyte), 1, fp);
    printf("%dok\n", nbSubset);

    getc(fp);
    //check for comments
    c = getc(fp);
    while (c == '#') {
	    while (getc(fp) != '\n')
	        ;
	    c = getc(fp);
    }

   ungetc(c,fp);
    
    //read image size information
    if (fscanf(fp, "%lu %lu", &toReturn.sizeX, &toReturn.sizeY) != 2) {
        fprintf(stderr, "Invalid image size (error loading '%s')\n", filename);
        exit(1);
    }
        
    printf("%lu %lu\n", toReturn.sizeX, toReturn.sizeY);
    
    getc(fp);

    h = (GLubyte*)malloc((size_t) nbSubset * sizeof(GLubyte));
    s = (GLubyte*)malloc((size_t) nbSubset * sizeof(GLubyte));
    v = (GLubyte*)malloc((size_t) nbSubset * sizeof(GLubyte));

    while (cpt < nbSubset){

        GLubyte aa,bb,cc;

        fread(&index, sizeof(GLubyte), 1, fp);
        fread(&aa, sizeof(GLubyte), 1, fp);
        fread(&bb, sizeof(GLubyte), 1, fp);
        fread(&cc, sizeof(GLubyte), 1, fp);
        h[index]=aa;
        s[index]=bb;
        v[index]=cc;
        printf("%d %d %d %d\n", index, h[index], s[index], v[index]);
        cpt++;
    }
    


	/* allocation memoire */
	size = toReturn.sizeX * toReturn.sizeY * 3;
	printf("Size image %lu %lu => %d\n", toReturn.sizeX, toReturn.sizeY, size);
	toReturn.data = (GLubyte *) malloc ((size_t) size * sizeof (GLubyte));
	assert(toReturn.data);
									

    //read pixel data from file
    for(i = 0; i < (int)toReturn.sizeX * toReturn.sizeY; i ++){

        fread(&index, sizeof(GLubyte), 1, fp);
        //printf("%d\n", index);
        toReturn.data[i*3] = h[index];
        toReturn.data[(i*3)+1] = s[index];
        toReturn.data[(i*3)+2] = v[index];
    }
    /*if (fread(toReturn.data, (size_t) 1, (size_t) size, fp) == 0) {
         fprintf(stderr, "Error loading image '%s'\n", filename);
         exit(1);
    }*/

	/* remettre l image dans le bon sens */
	sizex = toReturn.sizeX;
	//sizey = toReturn.sizeY;
	lastline = toReturn.data + size - sizex * 3;
	for (b = 0; b < toReturn.sizeY / 2; b++) {
	  ptrdeb = toReturn.data + b * sizex * 3;
	  ptrfin = lastline - (b * sizex * 3);
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

void extractFromBSP(char *filename){

    
}
