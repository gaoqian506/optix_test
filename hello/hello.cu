

#include <optix.h>
#include <optixu/optixu_math_namespace.h>

//using namespace optix;

rtDeclareVariable(uint2, launch_index, rtLaunchIndex, );
//rtBuffer<float4, 2>   result_buffer;
__device__ optix::buffer<float4, 2> result_buffer;

rtDeclareVariable(float3, draw_color, , );

RT_PROGRAM void hello()
{
  //result_buffer[launch_index] = make_float4(draw_color, 0.f);
	result_buffer[launch_index] = make_float4(0.25, 0.36, 0.29, 0.f);
}



/*
#include <optix.h>


using namespace optix;
//RTbuffer result_buffer;
//__device__ optix::buffer<float4, 1> result_buffer;
rtBuffer<float4, 2>   result_buffer;

//rtDeclareVariable(float3,                draw_color, , );

//RT_PROGRAM void draw_solid_color()
//{
 // result_buffer[launch_index] = make_float4(draw_color, 0.f);
//}

RT_PROGRAM void hello()
{
  result_buffer[0] = make_float4(1, 1, 0, 0.f);
}
*/

/*
#include <optix.h>
#include <optixu/optixu_math_namespace.h>

using namespace optix;

rtDeclareVariable(uint2, launch_index, rtLaunchIndex, );
rtBuffer<float4, 2>   result_buffer;

rtDeclareVariable(float3,                draw_color, , );

RT_PROGRAM void draw_solid_color()
{
  result_buffer[launch_index] = make_float4(draw_color, 0.f);
}

*/