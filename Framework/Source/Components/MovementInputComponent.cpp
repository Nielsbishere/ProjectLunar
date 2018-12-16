#include "../../Headers/Components/MovementInputComponent.h"
#include "../../Headers/Components/InputComponent.h"
using namespace lun;

REFLECT_CLASS(MovementInputComponent);

MovementInputComponent::MovementInputComponent(vec3 _speed) : speed(_speed), activated(false) {}

vec3 MovementInputComponent::getSpeed() { return speed; }
void MovementInputComponent::setSpeed(vec3 sp) { speed = sp; }

void MovementInputComponent::start() {
	activated = getOwner()->hasComponent<InputComponent>();
	if (!activated)
		printf("Couldn't activate MovementInputComponent. Missing InputComponent\n");
}

void MovementInputComponent::update(f32 dt) {
	if (!activated)return;
	InputHandler *ih = getOwner()->getComponent<InputComponent>()->getInput();
	if (ih == nullptr)return;
	i8 x = (i8)(ih->isKeyDown(CODE_A) || ih->isKeyDown(CODE_LEFT)) - (i8)(ih->isKeyDown(CODE_D) || ih->isKeyDown(CODE_RIGHT));
	i8 y = (i8)ih->isKeyDown(CODE_E) - (i8)ih->isKeyDown(CODE_Q);
	i8 z = (i8)(ih->isKeyDown(CODE_W) || ih->isKeyDown(CODE_UP)) - (i8)(ih->isKeyDown(CODE_S) || ih->isKeyDown(CODE_DOWN));
	getOwner()->getTransform().addLocal(vec3(x, y, z) * vec3(-speed.x, speed.y, -speed.z) * dt);
}