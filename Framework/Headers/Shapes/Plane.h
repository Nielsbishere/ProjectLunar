#pragma once

#include "../Type/OTypes.h"
#include "../Reflection.h"
#include "Ray.h"

namespace lun{
	class Plane {

	private:

		vec3 n, p0;
		f32 D;

	public:

		REFLECTION(Plane) {
			EXPOSEVAR(Plane, n);
			EXPOSEVAR(Plane, p0);
			EXPOSEVAR(Plane, D);
		}

		//Create plane from normal and point
		Plane(vec3 n, vec3 p0);

		//Create plane from 3 points
		//@optional bool inverseNormal
		Plane(vec3 p0, vec3 p1, vec3 p2, bool inverseNormal = false);

		//Create NULL plane
		Plane();

		//@return vec3 normal
		vec3 getNormal();

		//@return vec3 center point
		vec3 getPoint();

		//@return f32 distance from plane
		f32 getD();
		
		//Print contents
		void print();

		//Get distance from point to this plane
		f32 distance(vec3 p0);

		//Whether or not a ray collides with this plane
		//@param vec3 &intersection point
		//@return bool intersects
		bool intersects(Ray r, vec3 &i);
	};
}