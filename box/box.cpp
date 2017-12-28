
#include <GL/glew.h>
#include <GL/glut.h>
#include <optixu/optixpp_namespace.h>
#include <fstream>
#include <assert.h>
#include <opencv2/highgui/highgui.hpp>

int width = 512;
int height = 512;

optix::Context context;

int main(int argc, char** argv) {



	context = optix::Context::create( );
	context->setRayTypeCount( 1 );
	context->setEntryPointCount( 1 );
	//context->setStackSize(4640);

	optix::Buffer buffer = context->createBuffer( RT_BUFFER_OUTPUT, RT_FORMAT_UNSIGNED_BYTE4, width, height );
	context["result_buffer"]->set( buffer );	
	optix::Program ray_gen_program = context->createProgramFromPTXFile( "box/box.ptx", "box" );
	context->setRayGenerationProgram( 0, ray_gen_program );


	context->validate();
	context->launch( 0, width, height );

	void* image_data = buffer->map( );
	cv::Mat mat = cv::Mat(height, width, CV_8UC4, image_data);
	cv::imwrite("output.png", mat);
	buffer->unmap();

    buffer->destroy();
    ray_gen_program->destroy();
    context->destroy();




	//context["max_depth"]->setInt(100);


}