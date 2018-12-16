#pragma once
#include "../Reflection.h"
#include "../Type/OTypes.h"
namespace lun {
	class vec2;
	class vec3;

	class vec4 {

	public:

		f32 x, y, z, w;

		REFLECTION(vec4) {
			EXPOSEVAR(vec4, x);
			EXPOSEVAR(vec4, y);
			EXPOSEVAR(vec4, z);
			EXPOSEVAR(vec4, w);
		}

		//Create NULL vec4
		vec4();

		//Create vec4 from 4 f32
		vec4(f32 v0, f32 v1, f32 v2, f32 v3);

		//Create vec4 from vec2 and 2 f32
		vec4(vec2 v, f32 v3, f32 v4);

		//Create vec4 from vec3 and 1 f32
		vec4(vec3 v, f32 v4);

		//@return reference to the element at i
		//@behaviour automatically loops (element 4 = 0, element 7 = 3, element 8 = 0)
		f32 &operator[](const unsigned int i);
		vec4 operator*(const f32 f);
		vec4 operator/(const f32 f);
		vec4 operator%(const f32 f);
		vec4 operator/(vec4 v);
		vec4 operator+(vec4 v);
		vec4 operator-(vec4 v);
		vec4 operator+(f32 f);
		vec4 operator-(f32 f);
		vec4 operator-() const;
		f32 dot(vec4 v);
		vec4 operator*(vec4 v);
		vec4 &operator+=(vec4 v);
		vec4 &operator-=(vec4 v);
		vec4 &operator*=(f32 f);
		vec4 &operator*=(vec4 v);
		vec4 &operator/=(f32 f);
		f32 squareLength();
		f32 length();
		f32 magnitude();
		vec4 normalize();
		bool operator==(vec4 oth);
		bool operator!=(vec4 oth);
		
		bool operator>=(f32 f);
		bool operator<=(f32 f);
		bool operator>(f32 f);
		bool operator<(f32 f);

		//Print vector contents
		vec4 scale(vec4 v);

		void print();

		//Invert copy of this vector
		vec4 inverse();

		//@return null vector
		static vec4 zero();
	};
}
