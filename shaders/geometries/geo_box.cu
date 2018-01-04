
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

RT_PROGRAM void intersect(int) {

	float3 c0 = box_min-ray.origin;
	float3 c1 = box_max-ray.origin;
	float3 d0 = c0/ray.direction;
	float3 d1 = c1/ray.direction;

	// printf("c0:%f %f %f\nc1:%f %f %f\n", 
	// 		c0.x, c0.y, c0.z,
	// 		c1.x, c1.y, c1.z);


	// printf("box_min:%f %f %f, box_max:%f, %f, %f\n", 
	// 	box_min.x, box_min.y, box_min.z,
	// 	box_max.x, box_max.y, box_max.z);

	// printf("ray.origin:%f %f %f\n", 
	// 	ray.origin.x, ray.origin.y, ray.origin.z);
	// printf("ray.direction:%f %f %f\n", 
	// 	ray.direction.x, ray.direction.y, ray.direction.z);	

	//printf("d0:%f %f %f\n", d0.x, d0.y, d0.z);		

	float3 dmin = fminf(d0, d1);
	float3 dmax = fmaxf(d0, d1);
	float t0 = fmaxf(dmin);
	float t1 = fminf(dmax);
	if (t0 <= t1) {
		bool check_second = true;
		if (rtPotentialIntersection(t0)) {
			//printf("rtPotentialIntersection0");
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

RT_PROGRAM void bounds(int, float result[6]) {
	optix::Aabb* aabb = (optix::Aabb*)result;
	aabb->set(box_min, box_max);
}