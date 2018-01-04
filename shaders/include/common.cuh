#include <optix.h>


struct PerRayData_radiance
{
	float3 result;
	float  importance;
	int depth;
};

rtBuffer<float4, 2> output_buffer;

rtDeclareVariable(uint2, launch_index, rtLaunchIndex, );
rtDeclareVariable(rtObject, top_object, , );
rtDeclareVariable(PerRayData_radiance, prd_radiance, rtPayload, );



