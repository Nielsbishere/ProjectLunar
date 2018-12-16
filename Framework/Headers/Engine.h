#pragma once
#include "Type/OTypes.h"
#include "CrossPlatform/Context.h"
#include <string>
#include <vector>

namespace lun {
	class Context;
	class InputHandler;
	class Camera;
	class ResourcePile;
	class World;
	class GameObject;
	class RenderEngine;
	enum EShaderType;
	class State;

	class Engine {

	private:

		static bool hasEngine;

		Context *context;
		ResourcePile *resources;
		InputHandler *input;
		RenderEngine *renderer;
		State *state;

		Engine(){}

		void update(double dt);
		void render();
		void init();

		bool shouldClose();
		void swapBuffers();
		void pollEvents();
		void updateSize();

		void fetchWindowSize(int &w, int &h);

		void begin();
		~Engine();

		static Engine *create(std::string name, State *state);

	public:

		//Start engine with name

		template<typename T, class = typename std::enable_if<std::is_base_of<State, T>::value>::type>
		static bool start(std::string name) {
			if (hasEngine) {
				printf("There can only be one... muahah hah hah\n");
				return false;
			}

			Engine *en = Engine::create(name, new T());

			if (en == nullptr) {
				printf("Engine creation failed\n");
				return false;
			}

			hasEngine = true;
			en->begin();
			delete en;
			return true;
		}

		//@return int width
		int getWidth();

		//@return int height
		int getHeight();

		//@return InputHandler *input
		InputHandler *getInput();


		template<typename T, class = typename std::enable_if<std::is_base_of<State, T>::value>::type>
		void setState() {
			delete state;
			state = new T();
			renderer->reset();
			state->internalInit(input, renderer);
			state->init();
			renderer->init();
		}
	};
}