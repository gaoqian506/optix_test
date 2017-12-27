
#include <GL/glew.h>
#include <GL/glut.h>
//#include <optix_world.h>
#include <optixu/optixpp_namespace.h>
#include <sutil.h>

int width = 512;
int height = 512;

optix::Context context;

int main(int argc, char** argv) {


	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_RGB | GLUT_ALPHA | GLUT_DEPTH | GLUT_DOUBLE );
	glutInitWindowSize( width, height );
	glutInitWindowPosition( 100, 100 );
	glutCreateWindow( argv[0] );
	glutHideWindow();


	context = optix::Context::create();
	context->setRayTypeCount(2);
	context->setEntryPointCount(1);
	//context->setStackSize(4640);

	context["max_depth"]->setInt(100);


}