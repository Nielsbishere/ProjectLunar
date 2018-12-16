#pragma once
#pragma once
#include "../Type/OTypes.h"
#include "Plane.h"

namespace lun{
	class Triangle {

	private:

		vec3 p0, p1, p2;

	public:

		REFLECTION(Triangle) {
			EXPOSEVAR(Triangle, p0);
			EXPOSEVAR(Triangle, p1);
			EXPOSEVAR(Triangle, p2);
		}

		//Create NULL triangle
		Triangle();

		//Create triangle from 3 points
		Triangle(vec3 a, vec3 b, vec3 c);

		//@return vec3 p0
		vec3 a();

		//@return vec3 p1
		vec3 b();

		//@return vec3 p2
		vec3 c();

		//@return Plane plane
		Plane asPlane();
		
		//Transform triangle
		Triangle operator*(mat4 m);
		
		//Whether or not the ray intersects with this triangle
		bool intersects(Ray r);

		//Whether or not a point is on the triangle
		bool intersects(vec3 point);

		//@return vec3 center
		vec3 getCenter();

		//Print contents
		void print();
	};
}