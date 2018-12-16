#pragma once

#ifndef M_PI
#define M_PI 3.141592f
#endif

#include "../Reflection.h"

namespace lun {
	class vec3;
	class vec4;
	class vec2;

	class mat4 {
		friend class reflo::Reflection;

	public:

		REFLECTION(mat4) {
			EXPOSEVAR(mat4, m);
		}

		//Main constructor of mat4
		//@param m01 item at [1][0] (0y1x)
		mat4(f32 m00, f32 m01, f32 m02, f32 m03, f32 m10, f32 m11, f32 m12, f32 m13, f32 m20, f32 m21, f32 m22, f32 m23, f32 m30, f32 m31, f32 m32, f32 m33);

		//Vec4 constructor of mat4
		//Takes in 4 rows
		mat4(vec4 v0, vec4 v1, vec4 v2, vec4 v3);

		//Identity matrix
		mat4();


		//A column in the matrix
		typedef f32 arr[4];

		//@param unsigned int i, col number
		//@return column in the matrix
		arr& operator[](const unsigned int i);

		//@param unsigned int j, the row number
		//@return row
		vec4 horizontal(const unsigned int j);

		//@param unsigned int i, col number
		//@return row in the matrix
		vec4 vertical(const unsigned int i);

		//@param mat4 m, matrix to copy
		mat4 &operator=(mat4 m);

		//@param mat4 m, matrix to multiply by
		mat4 operator*(mat4 m);

		//@param f32 f, scale fator
		mat4 operator*(f32 f);

		//@param f32 f, scale factor
		mat4 &operator*=(f32 f);

		//@param vec4 v, vector to multiply by
		vec4 operator*(vec4 v);

		//@param mat4 m, matrix to add
		mat4 operator+(mat4 m);

		//@param mat4 m, matrix to subtract
		mat4 operator-(mat4 m);


		//@return translate, offset of the matrix
		vec3 getTranslate();

		//@param vec3 v, translate
		//@return mat4 this
		mat4 &setTranslate(vec3 v);

		//@return vec3 x
		vec3 getXAxis();

		//@return vec3 y
		vec3 getYAxis();

		//@return vec3 z
		vec3 getZAxis();

		//@return vec3 forward
		vec3 getForward();

		//@return vec3 up
		vec3 getUp();

		//@return vec3 right
		vec3 getRight();
		
		//@return mat4 orientation part (no translation)
		mat4 getOrientation();
		
		//@return vec3 scale
		vec3 getScale();
		
		//@return f32 determinant
		f32 determinant();

		//@return mat4 cofactors
		mat4 getCofactor();

		//Inverses self if possible
		//@return bool is inversable
		bool inverse();

		//Inverses self if possible
		//@return mat4::zero() if invalid
		mat4 forceInverse();

		//@setter mat4 orientation
		mat4 &setOrientation(vec3 x, vec3 y, vec3 z);
		
		//@setter mat4 orientation
		mat4 &setOrientation(mat4 m);
		
		//@setter vec3 scale
		mat4 &setScale(vec3 sc);

		//Returns copied transposed matrix
		//@return mat4 transposed
		mat4 transpose();

		//Prints the contents of this matrix
		void print();


		//@return mat4 null
		static mat4 zero();

		//@return mat4 identity
		static mat4 identity();

		//@return mat4 translation matrix
		static mat4 translate(vec3 v);

		//@return mat4 scale matrix
		static mat4 scale(vec3 v);

		//@return mat4 rotation matrix (in radians)
		static mat4 rotate(vec3 rot);

		//@return mat4 rotation matrix (in degrees)
		static mat4 rotateDeg(vec3 rot);

		//@param vec3 translate
		//@param vec3 rotation (radians)
		//@param vec3 scale
		//@return mat4 model matrix
		static mat4 getModel(vec3 t, vec3 rot, vec3 s);

		//@param vec3 translate
		//@param vec3 rotation (degrees)
		//@param vec3 scale
		//@return mat4 model matrix
		static mat4 getModelDeg(vec3 t, vec3 rot, vec3 s);

		//@return mat4 ortho matrix (projection)
		static mat4 ortho(f32 l, f32 r, f32 b, f32 t, f32 n, f32 f);

		//@return mat4 perspective matrix (projection)
		static mat4 perspective(f32 fov, f32 asp, f32 n, f32 f);

		//@return mat4 view matrix
		static mat4 lookat(vec3 eye, vec3 center, vec3 up);

		//@return mat4 rotation matrix around x axis
		static mat4 rotateX(f32 x);

		//@return mat4 rotation matrix around y axis
		static mat4 rotateY(f32 y);

		//@return mat4 rotation matrix around z axis
		static mat4 rotateZ(f32 z);

	private:

		f32 m[4][4];

		f32 det33();
	};
}