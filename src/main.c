#include "head.h"

Image *image;

int main(int argc, char **argv) {  

  if (argc<2) {
    fprintf(stderr, "Usage : ./bsp my_image.ppm\n");
    exit(0);
  }

  glutInit(&argc, argv); 
  glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
  glutInitWindowSize(640,480);  
  glutInitWindowPosition(100, 100);  
  glutCreateWindow("VPUP8");  

  Init(argv[1]);

  glutCreateMenu(menuFunc);

  glutAddMenuEntry("Sauver", 0);
  glutAddMenuEntry("Quit", 1);
  glutAddMenuEntry("Informations", 2);
  glutAttachMenu(GLUT_LEFT_BUTTON);

  glutDisplayFunc(Display);  
  glutReshapeFunc(Reshape);
  glutKeyboardFunc(Keyboard);
  
  glutMouseFunc(Mouse);

  glutMainLoop();  

  return 1;
}