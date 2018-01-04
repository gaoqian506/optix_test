
#include <GL/glew.h>
#include <GL/glut.h>
#include <optixu/optixpp_namespace.h>
#include <fstream>
#include <assert.h>



int width = 512;
int height = 512;

optix::Context context;

int main(int argc, char** argv) {



	context = optix::Context::create( );
	context->setRayTypeCount( 1 );
	context->setEntryPointCount( 1 );
	context->setPrintEnabled(true);
	//context->setStackSize(4640);

	optix::Buffer buffer = context->createBuffer( RT_BUFFER_OUTPUT, RT_FORMAT_FLOAT4, width, height );
	optix::Program ray_gen_program = context->createProgramFromPTXFile( "shaders/ray_generation/pinhole_camera.ptx", "pinhole_camera" );
	context->setRayGenerationProgram( 0, ray_gen_program );
	context["output_buffer"]->set( buffer );
	context["eye"]->setFloat(0, 0, -10);
	optix::Program exception_program = context->createProgramFromPTXFile( "shaders/ray_exception/print_exception.ptx", "exception" );
	context->setExceptionProgram( 0, exception_program );	
	//optix::Program miss_program = context->createProgramFromPTXFile( "box/box.ptx", "miss" );
	//context->setMissProgram( 0, miss_program );		

	optix::Geometry box = context->createGeometry();
	box->setPrimitiveCount(1);
	optix::Program intersect_program = context->createProgramFromPTXFile("shaders/geometries/geo_box.ptx", "intersect");
	box->setIntersectionProgram(intersect_program);
	optix::Program bounds_program = context->createProgramFromPTXFile("shaders/geometries/geo_box.ptx", "bounds");
	box->setBoundingBoxProgram(bounds_program);
	box["box_min"]->setFloat(-1, -1, -1);
	box["box_max"]->setFloat(+1, +1, +1);

	optix::Material material = context->createMaterial();
	optix::Program closest_hit_program = context->createProgramFromPTXFile("shaders/materials/mat_normal.ptx", "closest_hit");
	// //optix::Program any_hit_program = context->createProgramFromPTXFile("box/box.ptx", "any_hit");
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

	float* image_data = (float*)buffer->map( );
	unsigned char* rgb_data = (unsigned char*)malloc(width*height*3);
	int total = width * height;
	for (int i = 0; i < total; i++) {
		rgb_data[i*3+0] = image_data[i*4+0]*255;
		rgb_data[i*3+1] = image_data[i*4+1]*255;
		rgb_data[i*3+2] = image_data[i*4+2]*255;
	}
	
	std::ofstream out_file("output.ppm", std::ios::out | std::ios::binary);
	assert(out_file.is_open());
	out_file << "P6";
	out_file << width << " " << height << std::endl << 255 << std::endl;
	out_file.write((char*)rgb_data , width * height * 3);
	out_file.close();
	buffer->unmap();
	
	free(rgb_data);
	buffer->destroy();
	ray_gen_program->destroy();
	//exception_program->destroy();
	//miss_program->destroy();
	context->destroy();




	//context["max_depth"]->setInt(100);


}
