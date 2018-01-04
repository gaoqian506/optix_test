
#include <optix.h>
#include <optix_math.h>
//#include "common.cuh"

rtBuffer<float4, 2> output_buffer;


rtDeclareVariable(float3, eye, , );
//rtDeclareVariable(float3, roll_pitch_yaw, , );
//rtDeclareVariable(float3, fovy_cx_cy, , );
rtDeclareVariable(float3, target, , );
rtDeclareVariable(float, roll_angle, , );
rtDeclareVariable(float3, intrisics, , ); // [fovy, cx, cy]



rtDeclareVariable(uint2, launch_index, rtLaunchIndex, );


RT_PROGRAM void pinhole_camera() {

	optix::size_t2 screen = output_buffer.size();
	float2 d = make_float2(launch_index) / make_float2(screen);
	float3 dir = make_float3(d, 1)-0.5;
	optix::Ray ray(eye, dir, 0, 0.01);

	output_buffer[launch_index] = make_float4(d, 0, 1);
}


