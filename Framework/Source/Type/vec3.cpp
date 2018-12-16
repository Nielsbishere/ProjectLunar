#include "../../Headers/Type/OTypes.h"
#include "../../Headers/Math/Math.h"
#include "../../Headers/Reflection.h"
#include <cmath>
#include <iostream>

using namespace lun;

REFLECT_CLASS(vec3);

vec3::vec3() : vec3(0, 0, 0) {}

vec3::vec3(f32 v) : vec3(v, v, v) {}

vec3::vec3(f32 v0, f32 v1, f32 v2) {
	x = v0;
	y = v1;
	z = v2;
}

vec3::vec3(vec2 v, f32 v3) : vec3(v.x, v.y, v3) {}

vec3::vec3(vec4 v): vec3(v.x, v.y, v.z) {}

f32 &vec3::operator[](const unsigned int j) {
	const unsigned int i = j % 3;
	switch (i) {
	case 1:
		return y;
	case 2:
		return z;
	default:
		return x;
	}
}

vec3 vec3::operator*(const f32 f) {
	vec3 vec;
	for (int i = 0; i < 3; i++)
		vec[i] = f * (*this)[i];
	return vec;
}

vec3 vec3::operator/(const f32 f) {
	vec3 vec;
	for (int i = 0; i < 3; i++)
		vec[i] = (*this)[i] / f;
	return vec;
}

vec3 vec3::operator%(const f32 f) {
	vec3 vec;
	for (int i = 0; i < 3; i++)
		vec[i] = Math<f32>::mod((*this)[i], f);
	return vec;
}

vec3 vec3::operator/(vec3 v) {
	vec3 vec;
	for (int i = 0; i < 3; i++)
		vec[i] = (*this)[i] / v[i];
	return vec;
}

vec3 vec3::operator+(vec3 v) {
	vec3 vec;
	for (int i = 0; i < 3; i++)
		vec[i] = v[i] + (*this)[i];
	return vec;
}

vec3 vec3::operator-(vec3 v) {
	return (*this) + -v;
}

vec3 vec3::operator+(f32 f) {
	vec3 vec;
	for (int i = 0; i < 3; i++)
		vec[i] = f + (*this)[i];
	return vec;
}

vec3 vec3::operator-(f32 f) {
	return (*this) + -f;
}

vec3 vec3::operator-() const {
	return vec3(-x, -y, -z);
}

f32 vec3::dot(vec3 v) {
	f32 r = 0;
	for (int i = 0; i < 3; i++)
		r += v[i] * (*this)[i];
	return r;
}

vec3 vec3::operator*(vec3 v) {
	vec3 cpy = *this;
	cpy *= v;
	return cpy;
}

vec3 &vec3::operator+=(vec3 v) {
	for (int i = 0; i < 3; i++)
		(*this)[i] += v[i];
	return *this;
}

vec3 &vec3::operator-=(vec3 v) {
	for (int i = 0; i < 3; i++)
		(*this)[i] -= v[i];
	return *this;
}

vec3 &vec3::operator*=(f32 f) {
	for (int i = 0; i < 3; i++)
		(*this)[i] *= f;
	return *this;
}

vec3 &vec3::operator*=(vec3 v) {
	for (int i = 0; i < 3; i++)
		(*this)[i] *= v[i];
	return *this;
}

vec3 &vec3::operator/=(f32 f) {
	for (int i = 0; i < 3; i++)
		(*this)[i] /= f;
	return *this;
}

f32 vec3::squareLength() {
	f32 f = 0;
	for (int i = 0; i < 3; i++)
		f += (*this)[i] * (*this)[i];
	return f;
}

f32 vec3::length() {
	return Math<f32>::sqrt(squareLength());
}

f32 vec3::magnitude() {
	return Math<f32>::sqrt(squareLength());
}

vec3 vec3::normalize() {
	vec3 cpy = *this;
	cpy /= length();
	return cpy;
}

vec3 vec3::scale(vec3 v) {
	return vec3(x * v.x, y * v.y, z * v.z);
}

bool vec3::operator==(vec3 oth) {
	for (int i = 0; i < 3; i++)
		if ((*this)[i] != oth[i])return false;
	return true;
}

bool vec3::operator!=(vec3 oth) {
	return !(*this == oth);
}

void vec3::print() {
	printf("%f, %f, %f\n", x, y, z);
}

vec3 vec3::cross(vec3 v) {
	return vec3(y*v.z - v.y*z, z*v.x - v.z*x, x*v.y - v.x*y);
}

vec3 vec3::abs(){
	return vec3(Math<f32>::absf(x), Math<f32>::absf(y), Math<f32>::absf(z));
}

vec3 vec3::inverse() {
	return vec3(1 / x, 1 / y, 1 / z);
}

vec3 vec3::zero() {
	return vec3();
}

vec3 vec3::min(){
	unsigned int fmin = 0xff7fffff;
	f32 mi = *((f32*)&fmin);
	return vec3(mi, mi, mi);
}

vec3 vec3::max() {
	unsigned int fmax = 0x7f7fffff;
	f32 ma = *((f32*)&fmax);
	return vec3(ma, ma, ma);
}

vec3 vec3::min(vec3 a, vec3 b){
	return vec3(a.x < b.x ? a.x : b.x, a.y < b.y ? a.y : b.y, a.z < b.z ? a.z : b.z);
}

vec3 vec3::max(vec3 a, vec3 b) {
	return vec3(a.x > b.x ? a.x : b.x, a.y > b.y ? a.y : b.y, a.z > b.z ? a.z : b.z);
}

bool vec3::operator>=(f32 f){
	return x >= f && y >= f && z >= f;
}

bool vec3::operator<=(f32 f){
	return x <= f && y <= f && z <= f;
}

bool vec3::operator>(f32 f){
	return x > f && y > f && z > f;
}

bool vec3::operator<(f32 f){
	return x < f && y < f && z < f;
}

bool vec3::operator<(const vec3 &oth) {
	return x < oth.x || (x == oth.x && y < oth.y) || (x == oth.x && y == oth.y && z < oth.z);
}

vec3 vec3::floor() { return vec3(Math<f32>::floor(x), Math<f32>::floor(y), Math<f32>::floor(z)); }
vec3 vec3::fract() { return (*this) - this->floor(); }
vec3 vec3::mod(f32 b) { return ((*this) / b).fract() * b; }
vec3 vec3::absf() { return vec3(Math<f32>::absf(x), Math<f32>::absf(y), Math<f32>::absf(z)); }
vec3 vec3::ceil() { return vec3(Math<f32>::ceil(x), Math<f32>::ceil(y), Math<f32>::ceil(z)); }
vec3 vec3::clamp(f32 min, f32 max) { return vec3(Math<f32>::clamp(x, min, max), Math<f32>::clamp(y, min, max), Math<f32>::clamp(z, min, max)); }
vec3 vec3::sqrt() { return vec3(Math<f32>::sqrt(x), Math<f32>::sqrt(y), Math<f32>::sqrt(z)); }


vec2 vec3::xy() { return vec2(x, y); }
vec2 vec3::xz() { return vec2(x, z); }

vec2 vec3::yz() { return vec2(y, z); }
vec2 vec3::yx() { return vec2(y, x); }

vec2 vec3::zx() { return vec2(z, x); }
vec2 vec3::zy() { return vec2(z, y); }


void vec3::xy(vec2 v) { x = v.x; y = v.y; }
void vec3::xz(vec2 v) { x = v.x; z = v.y; }

void vec3::yz(vec2 v) { y = v.x; z = v.y; }
void vec3::yx(vec2 v) { y = v.x, x = v.y; }

void vec3::zx(vec2 v) { z = v.x; x = v.y; }
void vec3::zy(vec2 v) { z = v.x; y = v.y; }