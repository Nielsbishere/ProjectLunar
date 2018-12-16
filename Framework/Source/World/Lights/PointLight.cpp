#include "../../../Headers/World/Light/PointLight.h"
using namespace lun;

REFLECT_CLASS_NOFACTORY(PointLight);

PointLight::PointLight(vec3 pos, vec3 color, f32 intensity) : LightObject(color, intensity), position(pos) {}

void PointLight::setPosition(vec3 p) { position = p; onEdit(); }
void PointLight::move(vec3 dp) { position += dp; onEdit(); }

vec3 PointLight::getPosition() { return position; }

f32 PointLight::getRadius() {
	vec3 color;
	f32 power = getIntensity();

	if ((color = getColor()) == vec3())return 0;

	f32 hicoli = color.x > color.y && color.x > color.z ? color.x : (color.y > color.x && color.y > color.z ? color.y : color.z);
	f32 constant = 1.f;
	f32 linear = 0.7f;
	f32 quadratic = 1.8f;

	return (f32)(-linear + std::sqrtf(linear * linear - 4 * quadratic * (constant - (256.f / 5.f) * hicoli * power))) / (2 * quadratic);
}

TPointLight PointLight::getData() { return TPointLight(getPosRadius(), getColPow()); }

void PointLight::link(Buffer<PointLight, TPointLight> *parent) { daddy = parent; }

vec4 PointLight::getPosRadius() { return vec4(position, getRadius()); }

void PointLight::onEdit() {
	if (daddy != nullptr)
		daddy->edit(this);
}