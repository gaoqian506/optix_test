
#include <optix.h>
#include <optixu/optixu_math_namespace.h>


rtDeclareVariable(uint2, launch_index, rtLaunchIndex, );
__device__ optix::buffer<uchar4, 2> result_buffer;

RT_PROGRAM void box()
{
  	result_buffer[launch_index] = make_uchar4(0, 255, 255, 255);
}