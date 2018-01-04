
#include <optix.h>
#include <optix_math.h>
#include "common.cuh"
//#include <optixu/optixu_math_namespace.h>

rtDeclareVariable(float3, normal, attribute normal, );

RT_PROGRAM void closest_hit() {

	prd_radiance.result = normalize(rtTransformNormal(RT_OBJECT_TO_WORLD, normal))*0.5f + 0.5f;
	//printf("closest_hit");
}