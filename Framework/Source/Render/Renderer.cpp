#include "../../Headers/Render/Renderer.h"
using namespace lun;

Renderer::Renderer(AABB _aabb, Shader *_s, ERenderer _type) : aabb(_aabb), s(_s), type(_type) {}
Renderer::~Renderer() {}

void Renderer::nobindRender(mat4 m, Camera *c) { nobindRender(m, c->getView(), c->getProjection(), c->getPosition()); }

AABB Renderer::getAABB() { return aabb; }
ERenderer Renderer::getType() { return type; }

Shader *Renderer::getShader() { return s; }

void Renderer::render(mat4 model, Camera *camera) { this->render(model, camera->getView(), camera->getProjection(), camera->getPosition()); }