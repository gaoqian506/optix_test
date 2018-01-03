
#include <optix.h>
#include <optixu/optixu_math_namespace.h>
#include <optixu/optixu_aabb_namespace.h>

rtDeclareVariable(float3, box_min, , );
rtDeclareVariable(float3, box_max, , );
rtDeclareVariable(optix::Ray, ray, rtCurrentRay, );
rtDeclareVariable(float3, normal, attribute normal, );

static __device__ float3 box_normal(float t, float3 d0, float3 d1) {

	float3 neg = make_float3(t==d0.x?1:0, t==d0.y?1:0, t==d0.z?1:0);
	float3 pos = make_float3(t==d1.x?1:0, t==d1.y?1:0, t==d1.z?1:0);

	return pos-neg;

}

RT_PROGRAM void box_intersect(int) {

	float3 d0 = (box_min-ray.origin)/ray.direction;
	float3 d1 = (box_max-ray.origin)/ray.direction;

	float3 dmin = fminf(d0, d1);
	float3 dmax = fmaxf(d0, d1);
	float t0 = fmaxf(dmin);
	float t1 = fminf(dmax);
	if (t0 <= t1) {
		bool check_second = true;
		if (rtPotentialIntersection(t0)) {
			normal = box_normal(t0, d0, d1);
			if (rtReportIntersection(0)) {
				check_second = false;
			}
		}
		if (check_second) {
			if (rtPotentialIntersection(t1)) {
				normal = box_normal(t1, d0, d1);
				rtReportIntersection(0);
			}
		}
	}

}

RT_PROGRAM void box_bounds(int, float result[6]) {
	optix::Aabb* aabb = (optix::Aabb*)result;
	aabb->set(box_min, box_max);
}