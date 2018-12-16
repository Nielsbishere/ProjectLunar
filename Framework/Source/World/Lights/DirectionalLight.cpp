#include "../../../Headers/World/Light/DirectionalLight.h"
using namespace lun;

REFLECT_CLASS_NOFACTORY(DirectionalLight);

DirectionalLight::DirectionalLight(vec3 dir, vec3 color, f32 intensity) : LightObject(color, intensity), direction(dir) {}

void DirectionalLight::setDirection(vec3 d) { direction = d; onEdit(); }
vec3 DirectionalLight::getDirection() { return direction; }
vec3 DirectionalLight::getPosition(vec3 camPos, f32 delta) { return camPos + -direction * delta; }

TDirectionalLight DirectionalLight::getData() { return TDirectionalLight(direction, getColPow()); }

void DirectionalLight::link(Buffer<DirectionalLight, TDirectionalLight> *parent) { daddy = parent; }

void DirectionalLight::onEdit() {
	if (daddy != nullptr)
		daddy->edit(this);
}