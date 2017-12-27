
#include <GL/glut.h>

int main(int argc, char** argv) {

	glutInit(&argc, argv );
	glutInitDisplayMode( GLUT_RGB | GLUT_ALPHA | GLUT_DOUBLE );
	glutInitWindowSize( 100, 100 );
	glutInitWindowPosition( 100, 100 );
	glutCreateWindow( argv[0] );

	
	glutMainLoop();
	return 0;
}
