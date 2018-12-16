#pragma once
#include "../Reflection.h"
#include "../Type/OTypes.h"
namespace lun {
	class vec2;
	class vec4;

	class vec3 {

	public:

		f32 x, y, z;

		REFLECTION(vec3) {
			EXPOSEVAR(vec3, x);
			EXPOSEVAR(vec3, y);
			EXPOSEVAR(vec3, z);
		}

		//Create NULL vec3
		vec3();

		//Create vec3 with just 1 value repeated 3 times
		vec3(f32 v);

		//Create vec3 from 3 f32s
		vec3(f32 v0, f32 v1, f32 v2);

		//Create vec3 from vec2 & f32
		vec3(vec2 v, f32 v3);

		//Create vec3 from vec4.xyz
		vec3(vec4 v);


		//@return reference to the element at i
		//@behaviour automatically loops (element 3 = 0, element 5 = 2, element 6 = 0)
		f32 &operator[](const unsigned int i);
		vec3 operator*(const f32 f);
		vec3 operator/(const f32 f);
		vec3 operator%(const f32 f);
		vec3 operator/(vec3 v);
		vec3 operator+(vec3 v);
		vec3 operator-(vec3 v);
		vec3 operator+(f32 f);
		vec3 operator-(f32 f);
		vec3 operator-() const;
		f32 dot(vec3 v);
		vec3 operator*(vec3 v);
		vec3 &operator+=(vec3 v);
		vec3 &operator-=(vec3 v);
		vec3 &operator*=(f32 f);
		vec3 &operator*=(vec3 v);
		vec3 &operator/=(f32 f);
		f32 squareLength();
		f32 length();
		f32 magnitude();
		vec3 normalize();
		bool operator==(vec3 oth);
		bool operator!=(vec3 oth);
		
		bool operator>=(f32 f);
		bool operator<=(f32 f);
		bool operator>(f32 f);
		bool operator<(f32 f);

		//@return bool < for sorting (x < x2 || (x == x2 && y < y2) || (x == x && y == y2 && z < z2)
		bool operator<(const vec3 &oth);

		//Print vector contents
		void print();

		vec3 cross(vec3 v);
		vec3 abs();

		vec3 scale(vec3 v);
		vec3 floor();
		vec3 fract();
		vec3 mod(f32 f);
		vec3 absf();
		vec3 ceil();
		vec3 clamp(f32 min, f32 max);
		vec3 sqrt();

		///Shortcuts to getting part of the vector
		vec2 xy();
		vec2 xz();

		vec2 yz();
		vec2 yx();

		vec2 zx();
		vec2 zy();

		///Shortcuts to setting part of the vector
		void xy(vec2 v);
		void xz(vec2 v);

		void yz(vec2 v);
		void yx(vec2 v);

		void zx(vec2 v);
		void zy(vec2 v);


		//Invert copy of this vector
		vec3 inverse();

		//@return null vector
		static vec3 zero();
		
		//@return maximum vector (x,y,z are f32_MAX)
		static vec3 max();
		
		//@return minimum vector (x,y,z are f32_MIN)
		static vec3 min();
		
		//@return maximum vector; it picks the highest values from two vectors
		static vec3 max(vec3 a, vec3 b);
		
		//@return minimum vector; it picks the lowest values from two vectors
		static vec3 min(vec3 a, vec3 b);
	};
}
