#include "../../../Headers/World/Light/SpotLight.h"
using namespace lun;

REFLECT_CLASS_NOFACTORY(SpotLight);

SpotLight::SpotLight(vec3 p, f32 h, vec3 d, f32 r, vec3 color, f32 power) : LightObject(color, power), position(p), height(h), direction(d), radius(r) {}

void SpotLight::setPosition(vec3 p) { position = p; onEdit(); }
void SpotLight::move(vec3 dp) { position += dp; onEdit(); }
void SpotLight::setDirection(vec3 d) { direction = d; onEdit(); }
void SpotLight::setHeight(f32 h) { height = h; onEdit(); }
void SpotLight::setRadius(f32 r) { radius = r; onEdit(); }

vec3 SpotLight::getPosition() { return position; }
f32 SpotLight::getHeight() { return height; }
vec3 SpotLight::getDirection() { return direction; }
f32 SpotLight::getRadius() { return radius; }

TSpotLight SpotLight::getData() { return TSpotLight(vec4(position, height), vec4(direction, radius), getColPow()); }

void SpotLight::link(Buffer<SpotLight, TSpotLight> *parent) { daddy = parent; }

void SpotLight::onEdit() {
	if (daddy != nullptr)
		daddy->edit(this);
}