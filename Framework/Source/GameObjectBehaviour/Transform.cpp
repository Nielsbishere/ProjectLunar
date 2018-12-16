#include "..\..\Headers\GameObjectBehaviour\Transform.h"
using namespace lun;

REFLECT_CLASS(Transform);

//Constructor
Transform::Transform(vec3 _position, vec3 _rotation, vec3 _scale): position(_position), rotation(_rotation), scale(_scale), readOnly(false), edit(true) {}

//Model matrix
mat4 Transform::makeModelMatrix(){ return (edit ? !(edit = false) : false) ? m = mat4::getModelDeg(position, rotation, scale) : m; }

//Read only
void Transform::setReadOnly() { readOnly = true; }

//Position
vec3 Transform::getPosition() { return position; }
void Transform::setPosition(vec3 _position) { if (!readOnly) { position = _position; edit = true; } }
void Transform::addPosition(vec3 delta) { if (!readOnly) { position += delta; edit = true; } }

void Transform::addLocal(vec3 delta) {
	mat4 M = makeModelMatrix();
	vec3 dpos = M.getRight() * delta.x + M.getUp() * delta.y + M.getForward() * delta.z;
	addPosition(dpos);
}

//Rotation
vec3 Transform::getRotation() { return rotation; }
void Transform::setRotation(vec3 _rotation) { if (!readOnly){ rotation = _rotation; edit = true; } }
void Transform::addRotation(vec3 delta) { if (!readOnly){ rotation += delta; edit = true; } }

//Scale
vec3 Transform::getScale() { return scale; }
void Transform::setScale(vec3 _scale) { if (!readOnly){ scale = _scale; edit = true; } }