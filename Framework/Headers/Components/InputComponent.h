#pragma once
#include "../GameObjectBehaviour/Component.h"
#include "../Input/InputHandler.h"
#include "../Input/Keys.h"
namespace lun {
	//Component which can be attached to a GameObject to provide key/mouse and controller input
	class InputComponent : public Component {
	public:
		//Basic constructor
		InputComponent(InputHandler *_input = nullptr);

		//Init function
		void start() override;

		//Update function
		void update(f32 delta) override;

		//Called to attach the input handler
		//@setter InputHandler *input
		void attachInput(InputHandler *_ih);

		//@unset returns nullptr
		//@return InputHandler *input
		InputHandler *getInput();

	private:
		InputHandler *input;
	};
}