#pragma once
#include "../Type/OTypes.h"
#include "../Reflection.h"
namespace lun{
	class AABB {

	private:

		vec3 min, max;

	public:

		REFLECTION(AABB) {
			EXPOSEVAR(AABB, min);
			EXPOSEVAR(AABB, max);
		}

		//Turn two points into an AABB
		AABB(vec3 p0, vec3 p1);

		AABB();

		//i % 2 == 0 ? min : max
		vec3 operator[](unsigned int i);
		
		//@return vec3 min
		vec3 getMin();

		//@return vec3 max
		vec3 getMax();

		//@return half size (NOT FULL SIZE)
		vec3 getSize();

		//@return f32 maxRadius
		f32 maxRadius();

		//@return vec3 center
		vec3 getCenter();
		
		//Print min/max of this AABB
		void print();
		
		//Transform this AABB
		AABB operator*(mat4 m);

		//Move this AABB
		AABB operator+(vec3 v);
		
		//Create AABB that contains both AABBs
		static AABB encapsulate(AABB a0, AABB a1);
		
		//@param AABB box
		//@return bool intersects
		bool intersect(AABB &b);

		//@param vec3 point
		//@return bool intersects
		bool intersect(vec3 point);
		
		//Returns a subsection of this AABB using a min/max percentage		(example; 0,0,0->0.1,0.1,0.1 will return min + 0,0,0 to min + 10% * size)
		//@param AABB percentage
		//@return AABB subsection
		AABB within(AABB b);
	};
}