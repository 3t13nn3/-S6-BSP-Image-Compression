#include "menu.h"

void Keyboard(unsigned char key, int x, int y) {
	switch(key){
	case ESCAPE:
		exit(1);
		break;
	case Q:
		exit(1);
		break;
	default:
		fprintf(stderr, "Unused key\n");
	}
}

void Mouse(int button, int state, int x, int y) {

	switch(button){
	case GLUT_LEFT_BUTTON:
		break;
	case GLUT_MIDDLE_BUTTON:
		break;
	case GLUT_RIGHT_BUTTON:
		break;    
	}
	glutPostRedisplay();
}

int Init(char *s) {

	image = (Image *) malloc(sizeof(Image));
	if (image == NULL) {
		fprintf(stderr, "Out of memory\n");
		return(-1);
	}
	if (ImageLoad_PPM(s, image)==-1) 
	return(-1);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glutReshapeWindow(image->sizeX, image->sizeY);
	
	return (0);
}

int ReInit() {

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glutReshapeWindow(image->sizeX, image->sizeY);
	
	return (0);
}

void Display(void) {
	
	GLint w, h;

	glClear(GL_COLOR_BUFFER_BIT);

	w = glutGet(GLUT_WINDOW_WIDTH);
	h = glutGet(GLUT_WINDOW_HEIGHT);
	glDrawPixels(image->sizeX, image->sizeY, GL_RGB, GL_UNSIGNED_BYTE, 
				 image->data);

	glFlush();
}

void Reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble) w, 0.0, (GLdouble)h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void menuFunc(int item) {
	char s[256];

	switch(item){
	case 0:
		printf("Entrer le nom pour l'image dans cette taille\n");
		scanf("%s", &s[0]);
		imagesave_PPM(s, image);
		break;
	case 1:
		free(image);
		exit(0);
		break;
	case 2:
		case 6:
		printf("Taille de l image : %d %d\n", (int) image->sizeX, (int) image->sizeY);
		break;
	default:
		break;
	}
}