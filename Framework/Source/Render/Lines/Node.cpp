#include "../../../Headers/Render/Line/Node.h"
using namespace lun;

Node::Node() : id(0), position(vec3()) {}
Node::Node(u32 _id, vec3 _position) : id(_id), position(_position) {}
vec3 Node::getPosition() { return position; }
void Node::move(vec3 _position) { position = _position; }
void Node::addPosition(vec3 delta) { position += delta; }
void Node::setId(u32 i) { id = i; }