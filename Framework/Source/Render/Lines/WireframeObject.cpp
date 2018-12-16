#pragma once
#include "../../../Headers/Render/Line/WireframeObject.h"
#include "../../../Headers/Render/Line/Wireframe.h"
using namespace lun;

REFLECT_CLASS_NOFACTORY(WireframeObject);

bool WireframeObject::isHidden() { return !isVisible; }
void WireframeObject::toggleVisiblity() { isVisible = !isVisible; }
void WireframeObject::hide() { isVisible = false; }
void WireframeObject::show() { isVisible = true; }

void WireframeObject::setHidden(bool hide) { isVisible = !hide; }
vec3 WireframeObject::getLineColor() { return lineColor; }
f32 WireframeObject::getLineSize() { return lineSize; }

void WireframeObject::setLineColor(vec3 _lineColor) { lineColor = _lineColor; }
void WireframeObject::setLineSize(f32 _lineSize) { lineSize = _lineSize; }

void WireframeObject::colorize(vec3 tint) { lineColor *= tint; }

Transform &WireframeObject::getTransform() { return transform; }
Transform &WireframeObject::getLocalTransform() { return localTransform; }
Wireframe *WireframeObject::getWireframe() { return wires; }

bool WireframeObject::canRender() { return isVisible && lineSize != 0; }

WireframeObject::WireframeObject(bool _visible, Transform _localTransform, Transform &_transform, Wireframe *_wires, vec3 _lineColor, f32 _lineSize) : isVisible(_visible), localTransform(_localTransform), transform(_transform), wires(_wires), lineColor(_lineColor), lineSize(_lineSize), usesDepth(true) {}

AABB WireframeObject::getAABB() { return (wires->getAABB() * localTransform.makeModelMatrix()) * transform.makeModelMatrix(); }

void WireframeObject::setUsesDepth(bool b) { usesDepth = b; }
bool WireframeObject::fakes3D() { return !usesDepth; }