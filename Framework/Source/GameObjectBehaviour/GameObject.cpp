#include "../../Headers/GameObjectBehaviour/GameObject.h"
#include "../../Headers/GameObjectBehaviour/Component.h"
#include "../../Headers/World/World.h"
using namespace lun;

REFLECT_CLASS(GameObject);

GameObject::GameObject(): transform(Transform()), notDynamic(false) {
	components = std::vector<ComponentHolder>();
	world = nullptr;
}
GameObject::GameObject(vec3 p) : transform(Transform(p)), notDynamic(false) {
	components = std::vector<ComponentHolder>();
	world = nullptr;
}
GameObject::GameObject(vec3 p, vec3 r) : transform(Transform(p, r)), notDynamic(false) {
	components = std::vector<ComponentHolder>();
	world = nullptr;
}
GameObject::GameObject(vec3 p, vec3 r, vec3 s) : transform(Transform(p, r, s)), notDynamic(false) {
	components = std::vector<ComponentHolder>();
	world = nullptr;
}

GameObject::~GameObject(){}

void GameObject::start(){
	for (u32 i = 0; i < components.size(); ++i)
		components[i].component->start();
}

void GameObject::update(f32 deltaTime){
	for (u32 i = 0; i < components.size(); ++i)
		components[i].component->update(deltaTime);
}

Component * GameObject::getComponent(std::string name){
	for (auto it = components.begin(); it != components.end(); it++){
		if (it->name == name)
			return it->component;
	}
	return nullptr;
}
bool GameObject::hasComponent(std::string name) {
	for (auto it = components.begin(); it != components.end(); it++) 
		if (it->name == name)
			return true;

	return false;
}

void GameObject::addComponent(Component * newComponent, std::string name){
	ComponentHolder push;
	push.component = newComponent;
	push.name = name;
	components.push_back(push);
	push.component->attachOwner(this);
	push.component->start();
}

void GameObject::removeComponent(Component * component){
	for (auto it = components.begin(); it != components.end(); it++){
		if (it->component == component){
			components.erase(it);
			return;
		}
	}
}

void GameObject::removeComponent(std::string name){
	for (auto it = components.begin(); it != components.end(); it++){
		if (it->name == name){
			components.erase(it);
			return;
		}
	}
}


//template<typename T>
//inline T * GameObject::spawnObject()
//{
//	return nullptr;
//}

//template<typename T>
//Component * GameObject::getComponent()
//{
//	for (auto it = components.begin(); it != components.end(); it++)
//	{
//		if (typeid(*it->component) == typeid(T))
//			return (T*)it->component;
//	}
//	return nullptr;
//}