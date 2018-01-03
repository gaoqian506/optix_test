#include <optix.h>

rtBuffer<float4, 2> output_buffer;


struct PerRayData_radiance {
	
	float3 result;
	float  importance;
	int depth;
};



