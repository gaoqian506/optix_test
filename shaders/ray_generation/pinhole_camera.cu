
#include <optix.h>
#include "common.cuh"


rtDeclareVariable(float3, eye, , );
//rtDeclareVariable(float3, roll_pitch_yaw, , );
//rtDeclareVariable(float3, fovy_cx_cy, , );
rtDeclareVariable(float3, target, , );
rtDeclareVariable(float, roll_angle, , );
rtDeclareVariable(float3, intrisics, , ); // [fovy, cx, cy]



rtDeclareVariable(uint2, launch_index, rtLaunchIndex, );


RT_PROGRAM void pinhole_camera() {

	//output_buffer[launch_index] = make_float4(1, 1, 0, 1);
}


