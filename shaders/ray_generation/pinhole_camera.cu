
#include <optix.h>
#include <optix_math.h>
#include "common.cuh"




rtDeclareVariable(float3, eye, , );
//rtDeclareVariable(float3, roll_pitch_yaw, , );
//rtDeclareVariable(float3, fovy_cx_cy, , );
rtDeclareVariable(float3, target, , );
rtDeclareVariable(float, roll_angle, , );
rtDeclareVariable(float3, intrisics, , ); // [fovy, cx, cy]





RT_PROGRAM void pinhole_camera() {

	optix::size_t2 screen = output_buffer.size();
	float2 d = make_float2(launch_index) / make_float2(screen);
	float3 dir = make_float3(d-0.5, 1);
	optix::Ray ray(eye, dir, 0, 0.01);

	PerRayData_radiance prd;
	prd.result = make_float3(1, 0, 0);

	rtTrace(top_object, ray, prd);

	output_buffer[launch_index] = make_float4(prd.result, 1);

	//rtPrintf("hello");
}


