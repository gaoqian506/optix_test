
#include <optix.h>
#include <optix_math.h>
//#include <optixu/optixu_math_namespace.h>

rtDeclareVariable(float3, normal, attribute normal, );
rtDeclareVariable(float3, prd_color, rtPayload, );

RT_PROGRAM void closest_hit() {
	prd_color = normalize(normal)*0.5f+0.5f;
}