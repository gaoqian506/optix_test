
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

	optix::Buffer buffer = context->createBuffer( RT_BUFFER_OUTPUT, RT_FORMAT_FLOAT4, width, height );
	context["result_buffer"]->set( buffer );	
	optix::Program ray_gen_program = context->createProgramFromPTXFile( "box/box.ptx", "box" );
	context->setRayGenerationProgram( 0, ray_gen_program );
	optix::Program exception_program = context->createProgramFromPTXFile( "box/box.ptx", "exception" );
	context->setExceptionProgram( 0, exception_program );	
	optix::Program miss_program = context->createProgramFromPTXFile( "box/box.ptx", "miss" );
	context->setMissProgram( 0, miss_program );		

	optix::Geometry box = context->createGeometry();
	box->setPrimitiveCount(1);
	optix::Program intersect_program = context->createProgramFromPTXFile("box/box.ptx", "intersect");
	box->setIntersectionProgram(intersect_program);
	optix::Program bounds_program = context->createProgramFromPTXFile("box/box.ptx", "bounds");
	box->setBoundingBoxProgram(bounds_program);

	optix::Material material = context->createMaterial();
	optix::Program closest_hit_program = context->createProgramFromPTXFile("box/box.ptx", "closest_hit");
	//optix::Program any_hit_program = context->createProgramFromPTXFile("box/box.ptx", "any_hit");
	material->setClosestHitProgram(0, closest_hit_program);

	optix::GeometryInstance geometry_instance = context->createGeometryInstance();
	geometry_instance->setGeometry(box);
	geometry_instance->addMaterial(material);

	optix::GeometryGroup geometry_group = context->createGeometryGroup();
	geometry_group->addChild(geometry_instance);
	geometry_group->setAcceleration(context->createAcceleration("NoAccel"));

	context["top_object"]->set(geometry_group);


	context->validate();
	context->launch( 0, width, height );

	void* image_data = buffer->map( );
	cv::Mat mat = cv::Mat(height, width, CV_32FC4, image_data);
	cv::imwrite("output.png", mat * 255.0f);
	buffer->unmap();

    buffer->destroy();
    ray_gen_program->destroy();
    exception_program->destroy();
    miss_program->destroy();
    context->destroy();




	//context["max_depth"]->setInt(100);


}