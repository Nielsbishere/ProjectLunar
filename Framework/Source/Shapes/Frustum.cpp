#include "../../Headers/Shapes/Frustum.h"

using namespace lun;

Frustum::Frustum(f32 pov, f32 spct, f32 f, f32 n, vec3 eye, vec3 cnter, vec3 u): fov(pov), aspect(spct), far(f), near(n), up(u.normalize()), center(eye), direction((cnter - eye).normalize()) {
	vec3 right = up.cross(direction);
	f32 nearH = near * 2 * tan(fov / 2), nearW = nearH * aspect;
	f32 farH = far * 2 * tan(fov / 2), farW = farH * aspect;

	vec3 nc = center + direction * near;
	vec3 ntl = nc + (up * nearH / 2) - (right * nearW / 2);
	vec3 ntr = ntl + right * nearW;
	vec3 nbl = ntl - up * nearH;
	vec3 nbr = nbl + right * nearW;

	vec3 fc = center + direction * far;
	vec3 ftl = fc + (up * farH / 2) - (right * farW / 2);
	vec3 ftr = ftl + right * farW;
	vec3 fbl = ftl - up * farH;
	vec3 fbr = fbl + right * farW;

	planes[0] = Plane(ftl, ftr, fbr);
	planes[1] = Plane(ntl, nbl, nbr);
	planes[2] = Plane(ftl, fbl, nbl);
	planes[3] = Plane(ftr, ntr, nbr);
	planes[4] = Plane(ftr, ftl, ntl);
	planes[5] = Plane(fbr, nbr, nbl);
}

AABB Frustum::toAABB() {
	vec3 right = up.cross(direction);
	f32 nearH = near * 2 * tan(fov / 2), nearW = nearH * aspect;
	f32 farH = far * 2 * tan(fov / 2), farW = farH * aspect;

	vec3 nc = center + direction * near;
	vec3 ntl = nc + (up * nearH / 2) - (right * nearW / 2);
	vec3 ntr = ntl + right * nearW;
	vec3 nbl = ntl - up * nearH;
	vec3 nbr = nbl + right * nearW;

	vec3 fc = center + direction * far;
	vec3 ftl = fc + (up * farH / 2) - (right * farW / 2);
	vec3 ftr = ftl + right * farW;
	vec3 fbl = ftl - up * farH;
	vec3 fbr = fbl + right * farW;

	vec3 ma = vec3::max(ftr, nbl);
	vec3 mi = ma == ftr ? nbl : ftr;

	return AABB(mi, ma);
}

void Frustum::print() {
	printf("Frustum with fov %f, aspect %f, far and near plane %f,%f, eye position %f,%f,%f, direction %f,%f,%f, up %f,%f,%f and planes:\n", fov, aspect, far, near, center.x, center.y, center.z, direction.x, direction.y, direction.z, up.x, up.y, up.z);
	for (int i = 0; i < 6; i++)
		planes[i].print();
}

bool Frustum::intersection(AABB box, f32 delta) {
	for (int i = 0; i < 6; i++) {
		f32 dp = (planes[i].getNormal().x * box[planes[i].getNormal().x > 0].x) + (planes[i].getNormal().y * box[planes[i].getNormal().y > 0].y) + (planes[i].getNormal().z * box[planes[i].getNormal().z > 0].z);
		if (dp < -(planes[i].getD() + delta))
			return false;
	}
	return true;
}

bool Frustum::intersectionSphere(vec3 center, f32 r) {
	for (int i = 0; i < 6; i++) 
		if (planes[i].distance(center) < -r)return false;
	return true;
}

bool Frustum::intersectionSphere(AABB box, f32 r) {
	return intersectionSphere(box.getCenter(), box.maxRadius() + r);
}

f32 Frustum::getFOV() { return fov; }
f32 Frustum::getAspect() { return aspect; }
f32 Frustum::getFar() { return far; }
f32 Frustum::getNear() { return near; }
vec3 Frustum::getEye() { return center; }
vec3 Frustum::getCenter() { return direction + center; }
vec3 Frustum::getUp() { return up; }
Plane Frustum::operator[](unsigned int i) { return planes[i]; }

mat4 Frustum::getProjection() { return mat4::perspective(fov / M_PI * 180, aspect, near, far); }
mat4 Frustum::getView() { return mat4::lookat(center, center + direction, up); }