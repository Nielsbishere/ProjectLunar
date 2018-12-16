#pragma once

#include "../Type/OTypes.h"
#include "../Reflection.h"

namespace lun{
	class Ray {

	private:

		vec3 p0, d;

	public:

		REFLECTION(Ray) {
			EXPOSEVAR(Ray, p0);
			EXPOSEVAR(Ray, d);
		}

		//Create ray from origin and direction
		Ray(vec3 origin, vec3 direction);
		
		//@return vec3 origin
		vec3 getOrigin();

		//@return vec3 direction
		vec3 getDirection();
		
		//Print contents
		void print();

		//Get point on ray
		vec3 pointOnRay(f32 T);
	};
}