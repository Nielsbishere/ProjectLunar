#include "../../Headers/Components/InputComponent.h"
using namespace lun;

InputComponent::InputComponent(InputHandler *_input) : input(_input) {}

void InputComponent::start() {}
void InputComponent::update(f32 delta) {}

InputHandler *InputComponent::getInput() { return input; }

void InputComponent::attachInput(InputHandler *_input) {
	if (input == nullptr) 
		input = _input; 
}
