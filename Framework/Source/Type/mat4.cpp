#include "../../Headers/Type/OTypes.h"
#include "../../Headers/Reflection.h"
#include <iostream>
#include <cmath>

using namespace lun;

REFLECT_CLASS(mat4);

mat4::mat4(f32 m00, f32 m01, f32 m02, f32 m03, f32 m10, f32 m11, f32 m12, f32 m13, f32 m20, f32 m21, f32 m22, f32 m23, f32 m30, f32 m31, f32 m32, f32 m33) {
	m[0][0] = m00; m[1][0] = m01; m[2][0] = m02; m[3][0] = m03;
	m[0][1] = m10; m[1][1] = m11; m[2][1] = m12; m[3][1] = m13;
	m[0][2] = m20; m[1][2] = m21; m[2][2] = m22; m[3][2] = m23;
	m[0][3] = m30; m[1][3] = m31; m[2][3] = m32; m[3][3] = m33;
}

mat4::mat4(vec4 v0, vec4 v1, vec4 v2, vec4 v3) : mat4(v0.x, v0.y, v0.z, v0.w, v1.x, v1.y, v1.z, v1.w, v2.x, v2.y, v2.z, v2.w, v3.x, v3.y, v3.z, v3.w) {}

mat4::mat4() : mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1) {}

mat4::arr &mat4::operator[](const unsigned int i) {
	return m[i];
}

mat4 &mat4::operator=(mat4 m) {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			this->m[i][j] = m[i][j];
	return *this;
}

mat4 mat4::operator*(mat4 m) {
	mat4 mm;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			mm[i][j] = (*this).horizontal(j).dot(m.vertical(i));
	return mm;
}

mat4 mat4::operator*(f32 f) {
	mat4 mm;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			mm[i][j] = (*this)[i][j] * f;
	return mm;
}

mat4 &mat4::operator*=(f32 f) {
	(*this) = (*this) * f;
	return *this;
}

vec4 mat4::operator*(vec4 v) {
	vec4 res;
	for (int i = 0; i < 4; i++)
		res[i] = (*this).horizontal(i).dot(v);
	return res;
}

mat4 mat4::operator+(mat4 m) {
	mat4 returned = mat4::zero();
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			returned.m[i][j] = this->m[i][j] + m.m[i][j];
	return returned;
}

mat4 mat4::operator-(mat4 m) {
	mat4 returned = mat4::zero();
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			returned.m[i][j] = this->m[i][j] - m.m[i][j];
	return returned;
}

vec4 mat4::horizontal(const unsigned int j) {
	return vec4(m[0][j], m[1][j], m[2][j], m[3][j]);
} 

vec4 mat4::vertical(const unsigned int i) {
	return vec4(m[i][0], m[i][1], m[i][2], m[i][3]);
}

//f32 mat4::det33() {
//	f32 a = m[0][0], b = m[1][0]/*, c = m[2][0]*/, d = m[0][1], e = m[1][1], f = m[2][1], g = m[0][2], h = m[1][2], i = m[2][2];
//	f32 m1 = e * i - f * h;
//	f32 m2 = d * i - f * g;
//	f32 m3 = d * h - e * g;
//	return a * m1 - b * m2 + b * m3;
//}
//f32 mat4::determinant() {
//	f32 a = m[0][0]; f32 b = m[1][0]; f32 c = m[2][0]; f32 d = m[3][0];
//	f32 e = m[0][1]; f32 f = m[1][1]; f32 g = m[2][1]; f32 h = m[3][1];
//	f32 i = m[0][2]; f32 j = m[1][2]; f32 k = m[2][2]; f32 l = m[3][2];
//	f32 n = m[1][3]; f32 o = m[2][3]; f32 p = m[3][3]; f32 m = this->m[0][3];
//
//	f32 m00 = k * p - o * l;
//	f32 m01 = j * p - n * l;
//	f32 m02 = j * o - n * k;
//
//	f32 m10 = k * p - o * l;
//	f32 m11 = i * p - m * l;
//	f32 m12 = i * o - m * k;
//
//	f32 m20 = j * p - n * l;
//	f32 m21 = i * p - m * l;
//	f32 m22 = i * n - m * j;
//
//	f32 m30 = j * o - n * k;
//	f32 m31 = i * o - m * k;
//	f32 m32 = i * n - m * j;
//
//	f32 m0 = f * m00 - g * m01 + h * m02;
//	f32 m1 = e * m10 - g * m11 + h * m12;
//	f32 m2 = e * m20 - f * m21 + h * m22;
//	f32 m3 = e * m30 - f * m31 + g * m32;
//
//	return a * m0 - b * m1 + c * m2 - d * m3;
//}
//mat4 mat4::getCofactor() {
//	mat4 m00 = mat4(m[1][1], m[2][1], m[3][1], 0, m[1][2], m[2][2], m[3][2], 0, m[1][3], m[2][3], m[3][3], 0, 0, 0, 0, 0);
//	mat4 m01 = mat4(m[1][0], m[2][0], m[3][0], 0, m[1][2], m[2][2], m[3][2], 0, m[1][3], m[2][3], m[3][3], 0, 0, 0, 0, 0);
//	mat4 m02 = mat4(m[1][0], m[2][0], m[3][0], 0, m[1][1], m[2][1], m[3][1], 0, m[1][3], m[2][3], m[3][3], 0, 0, 0, 0, 0);
//	mat4 m03 = mat4(m[1][0], m[2][0], m[3][0], 0, m[1][1], m[2][1], m[3][1], 0, m[1][2], m[2][2], m[3][2], 0, 0, 0, 0, 0);
//
//	mat4 m10 = mat4(m[0][1], m[2][1], m[3][1], 0, m[0][2], m[2][2], m[3][2], 0, m[0][3], m[2][3], m[3][3], 0, 0, 0, 0, 0);
//	mat4 m11 = mat4(m[0][0], m[2][0], m[3][0], 0, m[0][2], m[2][2], m[3][2], 0, m[0][3], m[2][3], m[3][3], 0, 0, 0, 0, 0);
//	mat4 m12 = mat4(m[0][0], m[2][0], m[3][0], 0, m[0][1], m[2][1], m[3][1], 0, m[0][3], m[2][3], m[3][3], 0, 0, 0, 0, 0);
//	mat4 m13 = mat4(m[0][0], m[2][0], m[3][0], 0, m[0][1], m[2][1], m[3][1], 0, m[0][2], m[2][2], m[3][2], 0, 0, 0, 0, 0);
//
//	mat4 m20 = mat4(m[0][1], m[1][1], m[3][1], 0, m[0][2], m[1][2], m[3][2], 0, m[0][3], m[1][3], m[3][3], 0, 0, 0, 0, 0);
//	mat4 m21 = mat4(m[0][0], m[1][0], m[3][0], 0, m[0][2], m[1][2], m[3][2], 0, m[0][3], m[1][3], m[3][3], 0, 0, 0, 0, 0);
//	mat4 m22 = mat4(m[0][0], m[1][0], m[3][0], 0, m[0][1], m[1][1], m[3][1], 0, m[0][3], m[1][3], m[3][3], 0, 0, 0, 0, 0);
//	mat4 m23 = mat4(m[0][0], m[1][0], m[3][0], 0, m[0][1], m[1][1], m[3][1], 0, m[0][2], m[1][2], m[3][2], 0, 0, 0, 0, 0);
//
//	mat4 m30 = mat4(m[0][1], m[1][1], m[2][1], 0, m[0][2], m[1][2], m[2][2], 0, m[0][3], m[1][3], m[2][3], 0, 0, 0, 0, 0);
//	mat4 m31 = mat4(m[0][0], m[1][0], m[2][0], 0, m[0][2], m[1][2], m[2][2], 0, m[0][3], m[1][3], m[2][3], 0, 0, 0, 0, 0);
//	mat4 m32 = mat4(m[0][0], m[1][0], m[2][0], 0, m[0][1], m[1][1], m[2][1], 0, m[0][3], m[1][3], m[2][3], 0, 0, 0, 0, 0);
//	mat4 m33 = mat4(m[0][0], m[1][0], m[2][0], 0, m[0][1], m[1][1], m[2][1], 0, m[0][2], m[1][2], m[2][2], 0, 0, 0, 0, 0);
//	return mat4(m00.det33(), m01.det33(), m02.det33(), m03.det33(), m10.det33(), m11.det33(), m12.det33(), m13.det33(), m20.det33(), m21.det33(), m22.det33(), m23.det33(), m30.det33(), m31.det33(), m32.det33(), m33.det33());
//}
//bool mat4::inverse() {
//	f32 det;
//	if ((det = determinant()) == 0)return false;
//	mat4 cofactor = getCofactor();
//	mat4 adjoint = cofactor.transpose();
//	(*this) = adjoint * (1 / det);
//	return true;
//}
//mat4 mat4::forceInverse() {
//	mat4 copy = *this;
//	if (copy.inverse())return copy;
//	return mat4::zero();
//}

mat4 mat4::identity() {
	return mat4();
}

mat4 mat4::zero() {
	return mat4(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}

mat4 mat4::translate(vec3 v) {
	return identity().setTranslate(v);
}

mat4 mat4::scale(vec3 v) {
	return mat4(v.x, 0, 0, 0, 0, v.y, 0, 0, 0, 0, v.z, 0, 0, 0, 0, 1);
}

mat4 mat4::rotateX(f32 x) {
	mat4 m;
	m[1][1] = m[2][2] = cos(x);
	m[2][1] = -sin(x);
	m[1][2] = sin(x);
	return m;
}

mat4 mat4::rotateY(f32 y) {
	mat4 m;
	m[0][0] = m[2][2] = cos(y);
	m[0][2] = -sin(y);
	m[2][0] = sin(y);
	return m;
}

mat4 mat4::rotateZ(f32 z) {
	mat4 m;
	m[0][0] = m[1][1] = cos(z);
	m[1][0] = -sin(z);
	m[0][1] = sin(z);
	return m;
}

mat4 mat4::rotate(vec3 rot) {
	return rotateX(rot.x) * rotateY(rot.y) * rotateZ(rot.z);
}

mat4 mat4::rotateDeg(vec3 rot) {
	return rotateX(rot.x / 180 * M_PI) * rotateY(rot.y / 180 * M_PI) * rotateZ(rot.z / 180 * M_PI);
}

mat4 mat4::getModel(vec3 t, vec3 rot, vec3 s) {
	return translate(t) * rotate(rot) * scale(s);
}

mat4 mat4::getModelDeg(vec3 t, vec3 rot, vec3 s) {
	return translate(t) * rotateDeg(rot) * scale(s);
}

mat4 mat4::ortho(f32 l, f32 r, f32 b, f32 t, f32 n, f32 f) {
	f32 w = r - l;
	f32 h = t - b;
	mat4 m;
	m[0][0] = 2 / w;
	m[1][1] = 2 / h;
	m[2][2] = 1 / (f - n);
	m[3][2] = -n / (f - n);
	return m;
}

mat4 mat4::perspective(f32 fov, f32 asp, f32 n, f32 f) {
	mat4 m;
	f32 scale = 1 / tan(fov * 0.5f / 180 * M_PI);
	m[0][0] = scale / asp;
	m[1][1] = scale;
	m[2][2] = -((f + n) / (f - n));
	m[3][3] = 0;
	m[2][3] = -1;
	m[3][2] = -(2 * f * n / (f - n));
	return m;
}

mat4 mat4::lookat(vec3 eye, vec3 center, vec3 up) {
	vec3 z = (eye - center).normalize();
	vec3 x = (up.cross(z)).normalize();
	vec3 y = (z.cross(x)).normalize();
	mat4 m = identity().setOrientation(x, y, z);
	return m * translate(-eye);
}

mat4 mat4::transpose() {
	mat4 r;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			r[j][i] = m[i][j];
	return r;
}

mat4 &mat4::setOrientation(vec3 x, vec3 y, vec3 z) {
	m[0][0] = x.x; m[1][0] = x.y; m[2][0] = x.z;
	m[0][1] = y.x; m[1][1] = y.y; m[2][1] = y.z;
	m[0][2] = z.x; m[1][2] = z.y; m[2][2] = z.z;
	return *this;
}

mat4 &mat4::setOrientation(mat4 _){
	m[0][0] = _[0][0]; m[0][1] = _[0][1]; m[0][2] = _[0][2];
	m[1][0] = _[1][0]; m[1][1] = _[1][1]; m[1][2] = _[1][2];
	m[2][0] = _[2][0]; m[2][1] = _[2][1]; m[2][2] = _[2][2];
	return *this;
}

mat4 mat4::getOrientation(){
	mat4 _;
	_[0][0] = m[0][0]; _[0][1] = m[0][1]; _[0][2] = m[0][2];
	_[1][0] = m[1][0]; _[1][1] = m[1][1]; _[1][2] = m[1][2];
	_[2][0] = m[2][0]; _[2][1] = m[2][1]; _[2][2] = m[2][2];
	return _;
}

vec3 mat4::getScale(){
	return vec3(m[0][0], m[1][1], m[2][2]);
}

mat4 &mat4::setScale(vec3 sc){
	m[0][0] = sc.x;
	m[1][1] = sc.y;
	m[2][2] = sc.z;
	return *this;
}

vec3 mat4::getTranslate() {
	return vec3(m[3][0], m[3][1], m[3][2]);
}

mat4 &mat4::setTranslate(vec3 v) {
	m[3][0] = v.x;
	m[3][1] = v.y;
	m[3][2] = v.z;
	return *this;
}

vec3 mat4::getXAxis() {
	return vec3(m[0][0], m[1][0], m[2][0]);
}

vec3 mat4::getYAxis() {
	return vec3(m[0][1], m[1][1], m[2][1]);
}

vec3 mat4::getZAxis() {
	return vec3(m[0][2], m[1][2], m[2][2]);
}

vec3 mat4::getForward() {
	return getZAxis();
}

vec3 mat4::getRight() {
	return getXAxis();
}

vec3 mat4::getUp() {
	return getYAxis();
}

void mat4::print() {
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++) printf("%f\t", m[i][j]);
		printf("\n");
	}
	printf("\n");
}