#include "../../Headers/World/World.h"
#include "../../Headers/GameObjectBehaviour/GameObject.h"
#include "../../Headers/Render/Renderer.h"
#include "../../Headers/Camera/Camera.h"
#include "../../Headers/Components/RenderComponent.h"
#include "../../Headers/Components/InputComponent.h"
#include "../../Headers/Render/Shader.h"
#include "../../Headers/Render/RenderObject.h"
#include "../../Headers/Components/MovementInputComponent.h"
using namespace lun;

World::~World() {
	for (u32 i = 0; i < objects.size(); ++i)
		delete objects[i];
}
World::World(InputHandler *_ih, RenderEngine *_re): render(_re), input(_ih) {
	camera = Camera::create(vec3(0, 0, 15), 16.f / 9.f, 45.f, -vec3(0, 0, 15).normalize());
	camera->addComponent<InputComponent>();
	camera->addComponent<MovementInputComponent>();
	camera->getComponent<MovementInputComponent>()->setSpeed(vec3(30, 25, 60));
	spawn(camera);
}

bool World::contains(GameObject *go, u32 &i) {
	if (go == nullptr) {
		i = (u32)objects.size();
		return false;
	}
	for (u32 j = 0; j < objects.size(); ++j) {
		if (objects[j] == go) {
			i = j;
			return true;
		}
	}
	i = (u32)objects.size();
	return false;
}

bool World::contains(GameObject *go) {
	u32 i = 0;
	return contains(go, i);
}

bool World::spawn(GameObject *go) {
	if (go == nullptr || contains(go))return false;
	go->world = this;

	if (go->hasComponent<InputComponent>())						//Instanceof InputComponent
		go->getComponent<InputComponent>()->attachInput(input);

	//go->onSpawn();
	go->start();

	objects.push_back(go);
	return true;
}

void World::spawnAll(std::vector<GameObject*> &all) {
	u32 prevSize = (u32)objects.size();
	objects.resize(prevSize + all.size());

	u32 j = 0;
	for (u32 i = 0; i < all.size(); ++i) {
		GameObject *go = all[i];
		if (go == nullptr || contains(go)) continue;

		go->world = this;

		if (go->hasComponent<InputComponent>())
			go->getComponent<InputComponent>()->attachInput(input);

		go->start();

		objects[prevSize + j] = go;
		j++;
	}
	
	objects.resize(prevSize + j);
}

bool World::destroy(GameObject *go) {
	u32 i = 0;
	if (go == nullptr || !contains(go, i))return false;
	delete objects[i];
	objects.erase(objects.begin() + i);
	return true;
}

void World::update(double delta) {
	for (u32 i = 0; i < objects.size(); ++i)
		objects[i]->update((f32)delta);
}

void World::updateAspect(f32 asp) {
	camera->updateAspect(asp);
}

Camera *World::getMainCamera() { return camera; }
RenderEngine *World::getRenderEngine() { return render; }