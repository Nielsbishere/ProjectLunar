#include "../../Headers/Shapes/Ray.h"
#include <iostream>

using namespace lun;

REFLECT_CLASS_NOFACTORY(Ray);

vec3 Ray::pointOnRay(f32 T) {
	return p0 + d * T;
}

void Ray::print() {
	printf("Ray starting at %f,%f,%f heading towards %f,%f,%f\n", p0.x, p0.y, p0.z, d.x, d.y, d.z);
}

Ray::Ray(vec3 a, vec3 delta) : p0(a), d(delta) {}

vec3 Ray::getOrigin() { return p0; }
vec3 Ray::getDirection() { return d; }