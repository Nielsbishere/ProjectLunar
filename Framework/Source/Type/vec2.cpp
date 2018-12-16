#include "../../Headers/Type/OTypes.h"
#include "../../Headers/Reflection.h"
#include "../../Headers/Math/Math.h"
#include <cmath>
#include <iostream>

using namespace lun;

REFLECT_CLASS(vec2);

vec2::vec2() : vec2(0, 0) {}

vec2::vec2(f32 v0, f32 v1) {
	x = v0;
	y = v1;
}

vec2::vec2(vec3 v): vec2(v.x, v.y){}

vec2::vec2(vec4 v): vec2(v.x, v.y){}

f32 &vec2::operator[](const unsigned int j) {
	const unsigned int i = j % 2;
	switch (i) {
	case 1:
		return y;
	default:
		return x;
	}
}

vec2 vec2::operator*(const f32 f) {
	vec2 vec;
	for (int i = 0; i < 2; i++)
		vec[i] = f * (*this)[i];
	return vec;
}

vec2 vec2::operator/(const f32 f) {
	vec2 vec;
	for (int i = 0; i < 2; i++)
		vec[i] = (*this)[i] / f;
	return vec;
}

vec2 vec2::operator/(vec2 v) {
	vec2 vec;
	for (int i = 0; i < 2; i++)
		vec[i] = (*this)[i] / v[i];
	return vec;
}

vec2 vec2::operator%(const f32 f) {
	vec2 vec;
	for (int i = 0; i < 2; i++)
		vec[i] = Math<f32>::mod((*this)[i], f);
	return vec;
}

vec2 vec2::operator+(vec2 v) {
	vec2 vec;
	for (int i = 0; i < 2; i++)
		vec[i] = v[i] + (*this)[i];
	return vec;
}

vec2 vec2::operator-(vec2 v) {
	return (*this) + -v;
}

vec2 vec2::operator+(f32 f) {
	vec2 vec;
	for (int i = 0; i < 2; i++)
		vec[i] = f + (*this)[i];
	return vec;
}

vec2 vec2::operator-(f32 f) {
	return (*this) + -f;
}

vec2 vec2::operator-() const{
	return vec2(-x, -y);
}

f32 vec2::dot(vec2 v) {
	f32 r = 0;
	for (int i = 0; i < 2; i++)
		r += v[i] * (*this)[i];
	return r;
}

vec2 vec2::operator*(vec2 v) {
	vec2 cpy = *this;
	cpy *= v;
	return cpy;
}

vec2 &vec2::operator+=(vec2 v) {
	for (int i = 0; i < 2; i++)
		(*this)[i] += v[i];
	return *this;
}

vec2 &vec2::operator-=(vec2 v) {
	for (int i = 0; i < 2; i++)
		(*this)[i] -= v[i];
	return *this;
}

vec2 &vec2::operator*=(f32 f) {
	for (int i = 0; i < 2; i++)
		(*this)[i] *= f;
	return *this;
}

vec2 &vec2::operator*=(vec2 v) {
	for (int i = 0; i < 2; i++)
		(*this)[i] *= v[i];
	return *this;
}

vec2 &vec2::operator/=(f32 f) {
	for (int i = 0; i < 2; i++)
		(*this)[i] /= f;
	return *this;
}

f32 vec2::squareLength() {
	f32 f = 0;
	for (int i = 0; i < 2; i++)
		f += (*this)[i] * (*this)[i];
	return f;
} 

f32 vec2::length(){
	return Math<f32>::sqrt(squareLength());
} 

f32 vec2::magnitude(){
	return Math<f32>::sqrt(squareLength());
}

vec2 vec2::normalize(){
	vec2 cpy = *this;
	cpy /= length();
	return cpy;
}

vec2 vec2::scale(vec2 v) {
	return vec2(x * v.x, y * v.y);
}

bool vec2::operator==(vec2 oth) {
	for (int i = 0; i < 2; i++)
		if ((*this)[i] != oth[i])return false;
	return true;
}

bool vec2::operator!=(vec2 oth){
	return !(*this == oth);
} 

void vec2::print(){
	printf("%f, %f\n", x, y);
}

vec2 vec2::swap() {
	f32 x = y;
	f32 y = this->x;
	return vec2(x, y);
}

vec2 vec2::inverse() {
	return vec2(1 / x, 1 / y);
}

vec2 vec2::zero() {
	return vec2();
}

vec2 vec2::max() { return vec2(f32_MAX, f32_MAX); }
vec2 vec2::min() { return vec2(f32_MIN, f32_MIN); }
vec2 vec2::max(vec2 a, vec2 b) { return vec2(Math<f32>::max(a.x, b.x), Math<f32>::max(a.y, b.y)); }
vec2 vec2::min(vec2 a, vec2 b) { return vec2(Math<f32>::min(a.x, b.x), Math<f32>::min(a.y, b.y)); }

bool vec2::operator>=(f32 f) {
	return x >= f && y >= f;
}

bool vec2::operator<=(f32 f) {
	return x <= f && y <= f;
}

bool vec2::operator>(f32 f) {
	return x > f && y > f;
}

bool vec2::operator<(f32 f) {
	return x < f && y < f;
}

vec2 vec2::floor() { return vec2(Math<f32>::floor(x), Math<f32>::floor(y)); }
vec2 vec2::fract() { return (*this) - this->floor(); }
vec2 vec2::mod(f32 b) { return ((*this) / b).fract() * b; }
vec2 vec2::absf() { return vec2(Math<f32>::absf(x), Math<f32>::absf(y)); }
vec2 vec2::ceil() { return vec2(Math<f32>::ceil(x), Math<f32>::ceil(y)); }
vec2 vec2::clamp(f32 min, f32 max) { return vec2(Math<f32>::clamp(x, min, max), Math<f32>::clamp(y, min, max)); }
vec2 vec2::sqrt() { return vec2(Math<f32>::sqrt(x), Math<f32>::sqrt(y)); }