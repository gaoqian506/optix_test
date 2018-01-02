
#include <optix.h>
#include <optixu/optixu_math_namespace.h>


rtDeclareVariable(uint2, launch_index, rtLaunchIndex, );
rtDeclareVariable(float3, prd_color, rtPayload, );
rtDeclareVariable(rtObject, top_object, , );
__device__ optix::buffer<float4, 2> result_buffer;


RT_PROGRAM void box()
{
	optix::Ray ray(make_float3(0, 0, 0), make_float3(0, 0, 1), 0, 0.1);

	float3 color = make_float3(1, 1, 0);
	//rtTrace(rtObject(), ray, color);
	result_buffer[launch_index] = make_float4(color, 1);
}

RT_PROGRAM void miss() {
	//prd_color = make_float3(1, 0, 0);
}

RT_PROGRAM void exception() {
	//result_buffer[launch_index] = make_float4(0, 0, 1, 1);
}

RT_PROGRAM void intersect(int) {

}

RT_PROGRAM void bounds(int, float result[6]) {

}

RT_PROGRAM void closest_hit() {
	//prd_color = make_float3(0, 1, 0);
}

// RT_PROGRAM void any_hit() {
// 	prd_color = make_float3(1, 1, 0);
// }
