#include "../../Headers/Type/OTypes.h"
#include "../../Headers/Reflection.h"
#include "../../Headers/Math/Math.h"
#include <cmath>
#include <iostream>

using namespace lun;

REFLECT_CLASS(vec4);

vec4::vec4() : vec4(0, 0, 0, 0) {}

vec4::vec4(f32 v0, f32 v1, f32 v2, f32 v3) {
	x = v0;
	y = v1;
	z = v2;
	w = v3;
}

vec4::vec4(vec2 v, f32 v3, f32 v4) : vec4(v.x, v.y, v3, v4) {}

vec4::vec4(vec3 v, f32 v4) : vec4(v.x, v.y, v.z, v4) {}

f32 &vec4::operator[](const unsigned int j) {
	const unsigned int i = j % 4;
	switch (i) {
	case 1:
		return y;
	case 2:
		return z;
	case 3:
		return w;
	default:
		return x;
	}
}

vec4 vec4::operator*(const f32 f) {
	vec4 vec;
	for (int i = 0; i < 4; i++)
		vec[i] = f * (*this)[i];
	return vec;
}

vec4 vec4::operator/(const f32 f) {
	vec4 vec;
	for (int i = 0; i < 4; i++)
		vec[i] = (*this)[i] / f;
	return vec;
}

vec4 vec4::operator%(const f32 f) {
	vec4 vec;
	for (int i = 0; i < 4; i++)
		vec[i] = Math<f32>::mod((*this)[i], f);
	return vec;
}

vec4 vec4::operator/(vec4 v) {
	vec4 vec;
	for (int i = 0; i < 4; i++)
		vec[i] = (*this)[i] / v[i];
	return vec;
}

vec4 vec4::operator+(vec4 v) {
	vec4 vec;
	for (int i = 0; i < 4; i++)
		vec[i] = v[i] + (*this)[i];
	return vec;
}

vec4 vec4::operator-(vec4 v) {
	return (*this) + -v;
}

vec4 vec4::operator+(f32 f) {
	vec4 vec;
	for (int i = 0; i < 4; i++)
		vec[i] = f + (*this)[i];
	return vec;
}

vec4 vec4::operator-(f32 f) {
	return (*this) + -f;
}

vec4 vec4::operator-() const {
	return vec4(-x, -y, -z, -w);
}

f32 vec4::dot(vec4 v) {
	f32 r = 0;
	for (int i = 0; i < 4; i++)
		r += v[i] * (*this)[i];
	return r;
}

vec4 vec4::operator*(vec4 v) {
	vec4 cpy = *this;
	cpy *= v;
	return cpy;
}

vec4 &vec4::operator+=(vec4 v) {
	for (int i = 0; i < 4; i++)
		(*this)[i] += v[i];
	return *this;
}

vec4 &vec4::operator-=(vec4 v) {
	for (int i = 0; i < 4; i++)
		(*this)[i] -= v[i];
	return *this;
}

vec4 &vec4::operator*=(f32 f) {
	for (int i = 0; i < 4; i++)
		(*this)[i] *= f;
	return *this;
}

vec4 &vec4::operator*=(vec4 v) {
	for (int i = 0; i < 4; i++)
		(*this)[i] *= v[i];
	return *this;
}

vec4 &vec4::operator/=(f32 f) {
	for (int i = 0; i < 4; i++)
		(*this)[i] /= f;
	return *this;
}

f32 vec4::squareLength() {
	f32 f = 0;
	for (int i = 0; i < 4; i++)
		f += (*this)[i] * (*this)[i];
	return f;
}

f32 vec4::length() {
	return sqrt(squareLength());
}

f32 vec4::magnitude() {
	return sqrt(squareLength());
}

vec4 vec4::normalize() {
	vec4 cpy = *this;
	cpy /= length();
	return cpy;
}

vec4 vec4::scale(vec4 v) {
	return vec4(x * v.x, y * v.y, z * v.z, w * v.w);
}

bool vec4::operator==(vec4 oth) {
	for (int i = 0; i < 4; i++)
		if ((*this)[i] != oth[i])return false;
	return true;
}

bool vec4::operator!=(vec4 oth) {
	return !(*this == oth);
}

void vec4::print() {
	printf("%f, %f, %f, %f\n", x, y, z, w);
}

vec4 vec4::inverse() {
	return vec4(1 / x, 1 / y, 1 / z, 1 / w);
}

vec4 vec4::zero() {
	return vec4();
}

bool vec4::operator>=(f32 f) {
	return x >= f && y >= f && z >= f && w >= f;
}

bool vec4::operator<=(f32 f) {
	return x <= f && y <= f && z <= f && w <= f;
}

bool vec4::operator>(f32 f) {
	return x > f && y > f && z > f && w > f;
}

bool vec4::operator<(f32 f) {
	return x < f && y < f && z < f && w < f;
}