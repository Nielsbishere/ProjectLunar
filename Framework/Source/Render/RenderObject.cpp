#include "../../Headers/Render/RenderObject.h"
using namespace lun;

REFLECT_CLASS_NOFACTORY(RenderObject);

bool RenderObject::isHidden() { return !isVisible; }
void RenderObject::toggleVisiblity() { if (!isStatic) isVisible = !isVisible; }
void RenderObject::hide() { if (!isStatic) isVisible = false; }
void RenderObject::show() { if (!isStatic) isVisible = true; }
void RenderObject::setHidden(bool hide) { if (!isStatic) isVisible = !hide; }

bool RenderObject::isDynamic() { return !isStatic; }

Transform &RenderObject::getTransform() { return transform; }
Renderer *RenderObject::getRenderer() { return r; }

RenderObject::RenderObject(bool _visible, bool &_static, Transform &_transform, Renderer *_r) : isVisible(_visible), isStatic(_static), transform(_transform), r(_r) {}