
#include <optix.h>
#include <optix_math.h>
//#include "common.cuh"

struct PerRayData_radiance
{
	float3 result;
	float  importance;
	int depth;
};

rtBuffer<float4, 2> output_buffer;


rtDeclareVariable(float3, eye, , );
//rtDeclareVariable(float3, roll_pitch_yaw, , );
//rtDeclareVariable(float3, fovy_cx_cy, , );
rtDeclareVariable(float3, target, , );
rtDeclareVariable(float, roll_angle, , );
rtDeclareVariable(float3, intrisics, , ); // [fovy, cx, cy]

rtDeclareVariable(uint2, launch_index, rtLaunchIndex, );
rtDeclareVariable(rtObject, top_object, , );



rtDeclareVariable(PerRayData_radiance, prd_radiance, rtPayload, );


RT_PROGRAM void pinhole_camera() {

	optix::size_t2 screen = output_buffer.size();
	float2 d = make_float2(launch_index) / make_float2(screen);
	float3 dir = make_float3(d, 1)-0.5;
	optix::Ray ray(eye, dir, 0, 0.01);

	PerRayData_radiance prd;
	prd.result = make_float3(1, 0, 0);

	rtTrace(top_object, ray, prd);

	output_buffer[launch_index] = make_float4(prd.result, 1);

	//rtPrintf("hello");
}


