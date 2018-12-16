#include "../../../Headers/World/Light/LightObject.h"
using namespace lun;

void LightObject::setColor(vec3 c) { color = c; onEdit(); }
void LightObject::setIntensity(f32 i) { intensity = i; onEdit(); }
void LightObject::intensify(f32 mi) { intensity *= mi; onEdit(); }

vec3 LightObject::getColor() { return color; }
f32 LightObject::getIntensity() { return intensity; }

LightObject::LightObject(vec3 c, f32 i) : color(c), intensity(i) {}

vec4 LightObject::getColPow() { return vec4(color, intensity); }