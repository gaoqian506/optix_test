
#include <GL/glut.h>
#include <optix.h>
#include <sutil.h>

int main(int argc, char** argv) {

    RTcontext context = 0;
	RT_CHECK_ERROR( rtContextCreate( &context ) );	

	glutInit(&argc, argv );
	glutInitDisplayMode( GLUT_RGB | GLUT_ALPHA | GLUT_DOUBLE );
	glutInitWindowSize( 100, 100 );
	glutInitWindowPosition( 100, 100 );
	glutCreateWindow( argv[0] );



	
	glutMainLoop();
	return 0;
}
