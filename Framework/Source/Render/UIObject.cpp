#include "../../Headers/Render/UIObject.h"
#include "../../Headers/Render/Shader.h"
#include "../../Headers/Resources/Textures/Texture.h"
#include "../../Headers/Render/Renderer.h"
using namespace lun;

REFLECT_CLASS_NOFACTORY(UIObject);

UIObject::UIObject(Renderer *_r, Texture *_t, vec2 _offset, vec2 _scale, f32 _rotation, f32 _depth, vec2 _uvOffset, vec2 _uvScale, vec4 _colorizer, bool _isHidden) : r(_r), t(_t), offset(_offset), scale(_scale), rotation(_rotation), depth(_depth), uvOffset(_uvOffset), uvScale(_uvScale), colorizer(_colorizer), isHidden(_isHidden){}

bool UIObject::canRender() {
	if (r == nullptr || scale == vec2(0, 0) || colorizer.w == 0 || isHidden || r == nullptr)return false;
	return true;
}

bool UIObject::operator<(const UIObject &uio) {
	return (r == nullptr && uio.r != nullptr) || (r != nullptr && uio.r != nullptr && (depth > uio.depth || (depth == uio.depth && r < uio.r)));
}

void UIObject::render(Shader *s) {
	if (!canRender())return;
	t->bind(TEXTURE_2D);
	s->set("M", mat4::getModelDeg(vec3(offset, 0), vec3(0, 0, rotation), vec3(scale, 1)));
	s->set("uvScaleOffset", vec4(uvScale, uvOffset.x, uvOffset.y));
	s->set("colorizer", colorizer);
	s->set("depth", depth);
	r->bind();
	r->instancedRender(1);
	r->unbind();
}

void UIObject::nobindRender(Shader *s) {
	if (!canRender())return;
	s->set("M", mat4::getModelDeg(vec3(offset, 0), vec3(0, 0, rotation), vec3(scale, 1)));
	s->set("uvScaleOffset", vec4(uvScale, uvOffset.x, uvOffset.y));
	s->set("colorizer", colorizer);
	s->set("depth", depth);
	r->instancedRender(1);
}

void UIObject::setOffset(vec2 _offset) { offset = _offset; }
void UIObject::move(vec2 delta) { offset += delta; }

void UIObject::setRotation(f32 _rotation) { rotation = _rotation; }
void UIObject::rotate(f32 delta) { rotation += delta; }

void UIObject::setColorizer(vec4 col) { colorizer = col; }
void UIObject::colorize(vec4 colorize) { colorizer *= colorize; }

void UIObject::setOpacity(f32 opacity) { colorizer.w = opacity; }
void UIObject::fadeOpacity(f32 percentage) { colorizer.w *= percentage; }

void UIObject::setScale(vec2 _scale) { scale = _scale; }
void UIObject::applyScale(vec2 factor) { scale *= factor; }

void UIObject::setUvOffset(vec2 _uvOffset) { uvOffset = _uvOffset; }
void UIObject::setUvScale(vec2 _uvScale) { uvScale = _uvScale; }

void UIObject::setDepth(f32 _depth) { depth = _depth; }

void UIObject::setVisible(bool visible) { isHidden = !visible; }
void UIObject::hide() { isHidden = true; }
void UIObject::show() { isHidden = false; }
void UIObject::toggle() { isHidden = !isHidden; }

vec2 UIObject::getOffset() { return offset; }
vec2 UIObject::getScale() { return scale; }
vec2 UIObject::getUvOffset() { return uvOffset; }
vec2 UIObject::getUvScale() { return uvScale; }
vec4 UIObject::getColorizer() { return colorizer; }
f32 UIObject::getDepth() { return depth; }
bool UIObject::isVisible() { return !isHidden; }

Renderer *UIObject::getRenderer() { return r; }
Texture *UIObject::getTexture() { return t; }