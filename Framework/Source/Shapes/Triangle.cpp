#include "../../Headers/Shapes/Triangle.h"
#include <iostream>

using namespace lun;

REFLECT_CLASS(Triangle);

Triangle::Triangle(vec3 a, vec3 b, vec3 c): p0(a), p1(b), p2(c) {}

Triangle::Triangle(): Triangle(vec3(), vec3(), vec3()) {}

Triangle Triangle::operator*(mat4 m){ return Triangle(m * vec4(p0, 1), m * vec4(p1, 1), m * vec4(p2, 1)); }

bool Triangle::intersects(Ray r) {
	vec3 i = vec3();
	if (!asPlane().intersects(r, i)) return false;

	vec3 ab = (p1 - p0);
	vec3 cb = (p2 - p0);
	vec3 ia = (i - p0);

	f32 d00 = ab.dot(ab);
	f32 d01 = ab.dot(cb);
	f32 d11 = cb.dot(cb);
	f32 d20 = ia.dot(ab);
	f32 d21 = ia.dot(cb);

	f32 invdenom = 1 / (d00 * d11 - d01 * d01);
	f32 a = (d11 * d20 - d01 * d21) * invdenom;
	f32 b = (d00 * d21 - d01 * d20) * invdenom;

	return a >= 0 && b >= 0 && a <= 1 && b <= 1;
}

bool Triangle::intersects(vec3 point) {
	vec3 e10 = p1 - p0;
	vec3 e20 = p2 - p0;
	f32 a = e10.dot(e10);
	f32 b = e10.dot(e20);
	f32 c = e20.dot(e20);
	f32 ac_bb = (a*c) - (b*b);
	vec3 vp(point.x - p0.x, point.y - p0.y, point.z - p0.z);
	f32 d = vp.dot(e10);
	f32 e = vp.dot(e20);
	f32 x = (d*c) - (e*b);
	f32 y = (e*a) - (d*b);
	f32 z = x + y - ac_bb;
	return z < 0 && !(x < 0 || y < 0);
}

vec3 Triangle::getCenter(){ return p0 / 3 + p1 / 3 + p2 / 3; }

void Triangle::print() {
	printf("Triangle with coords %f,%f,%f, %f,%f,%f and %f,%f,%f. With plane attachment: ", p0.x, p0.y, p0.z, p1.x, p1.y, p1.z, p2.x, p2.y, p2.z);
	asPlane().print();
}

vec3 Triangle::a() { return p0; }
vec3 Triangle::b() { return p1; }
vec3 Triangle::c() { return p2; }
Plane Triangle::asPlane() { return Plane((p1 - p0).cross(p2 - p0).normalize(), getCenter()); }