#pragma once
#include "../Reflection.h"
#include "../Type/OTypes.h"
namespace lun {
	class vec3;
	class vec4;

	class vec2 {

	public:

		f32 x, y;

		REFLECTION(vec2) {
			EXPOSEVAR(vec2, x);
			EXPOSEVAR(vec2, y);
		}

		//Create NULL vec2
		vec2();

		//Create vec2 from two f32s
		vec2(f32 v0, f32 v1);

		//Create vec2 from vec3.xy
		vec2(vec3 v);

		//Create vec2 from vec4.xy
		vec2(vec4 v);


		//@return reference to the element at i
		//@behaviour automatically loops (element 2 = 0, element 3 = 1, element 4 = 0)
		f32 &operator[](const unsigned int i);

		vec2 operator*(const f32 f);
		vec2 operator/(const f32 f);
		vec2 operator%(const f32 f);
		vec2 operator/(vec2 v);
		vec2 operator+(vec2 v);
		vec2 operator-(vec2 v);
		vec2 operator+(f32 f);
		vec2 operator-(f32 f);
		vec2 operator-() const;
		f32 dot(vec2 v);
		vec2 operator*(vec2 v);
		vec2 &operator+=(vec2 v);
		vec2 &operator-=(vec2 v);
		vec2 &operator*=(f32 f);
		vec2 &operator*=(vec2 v);
		vec2 &operator/=(f32 f);
		f32 squareLength();
		f32 length();
		f32 magnitude();
		vec2 normalize();
		bool operator==(vec2 oth);
		bool operator!=(vec2 oth);
		
		bool operator>=(f32 f);
		bool operator<=(f32 f);
		bool operator>(f32 f);
		bool operator<(f32 f);

		//Print vector contents
		void print();

		vec2 scale(vec2 v);
		vec2 floor();
		vec2 fract();
		vec2 mod(f32 f);
		vec2 absf();
		vec2 ceil();
		vec2 clamp(f32 min, f32 max);
		vec2 sqrt();

		//Swap x and y
		vec2 swap();

		//Invert copy of this vector
		vec2 inverse();

		//@return null vector
		static vec2 zero();

		//@return maximum vector (x,y are f32_MAX)
		static vec2 max();

		//@return minimum vector (x,y are f32_MIN)
		static vec2 min();

		//@return maximum vector; it picks the highest values from two vectors
		static vec2 max(vec2 a, vec2 b);

		//@return minimum vector; it picks the lowest values from two vectors
		static vec2 min(vec2 a, vec2 b);
	};
}
