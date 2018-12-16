#include "../../Headers/GameObjectBehaviour/Component.h"
using namespace lun;

Component::Component(){}
Component::~Component(){}

void Component::onAttach() {}
GameObject *Component::getOwner() { return owner; }
void Component::attachOwner(GameObject *_owner) { if(owner == nullptr) owner = _owner; }