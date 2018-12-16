#pragma once
#include "../Type/oTypes.h"
#include "../Reflection.h"
#include "Plane.h"
#include "AABB.h"
#include <iostream>
namespace lun{
	class Frustum {

	private:

		f32 fov, aspect, far, near;
		vec3 center, direction, up;
		Plane planes[6];

	public:

		//Create frustum from fov, aspect, far, near, eye, center and up
		//@param f32 fov; field of view (degrees)
		//@param f32 aspect; width:height
		//@param f32 far
		//@param f32 near
		//@param vec3 eye (position)
		//@param vec3 center (eye + direction)
		//@param vec3 up
		Frustum(f32 fov, f32 aspect, f32 far, f32 near, vec3 eye, vec3 center, vec3 up);
		
		//@return f32 fov
		f32 getFOV();

		//@return f32 aspect
		f32 getAspect();

		//@return f32 far
		f32 getFar();

		//@return f32 near
		f32 getNear();

		//@return vec3 eye
		vec3 getEye();

		//@return vec3 center
		vec3 getCenter();

		//@return vec3 up
		vec3 getUp();

		//@return Plane (0->5) frustum planes
		Plane operator[](unsigned int i);
	
		//@return mat4 P
		mat4 getProjection();

		//@return mat4 V
		mat4 getView();
		
		//Print contents
		void print();

		//@optional f32 delta (difference in distance for intersection)
		//@return bool intersection with box
		bool intersection(AABB box, f32 delta = 0);

		//@return bool intersection with sphere
		bool intersectionSphere(vec3 center, f32 r);

		//@optional f32 delta (difference in distance for intersection)
		//@return bool intersection with AABB (but converts AABB to sphere)
		bool intersectionSphere(AABB box, f32 delta=0);

		//@return AABB boundingBox
		AABB toAABB();
	};
}