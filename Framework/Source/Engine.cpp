#include "../Headers/Engine.h"
#include "../Headers/CrossPlatform/Context.h"
#include "../Headers/Input/InputHandler.h"
#include "../Headers/Reflection.h"
#include "../Headers/Helper/OGLHelper.h"
#include "../Headers/Camera/Camera.h"
#include "../Headers/Resources/ResourcePile.h"
#include "../Headers/RenderEngine.h"
#include "../Headers/World/World.h"
#include "../Headers/Settings/Settings.h"
#include "../Headers/State/State.h"
#include <chrono>

//Temp
#include "../Headers/GameObjectBehaviour/GameObject.h"
#include "../Headers/Components/RenderComponent.h"
#include "../Headers/Components/WireframeComponent.h"
#include "../Headers/Render/UIObject.h"
#include "../Headers/World/Light/PointLight.h"

using namespace lun;


bool Engine::hasEngine = false;


#ifdef __DESKTOP__

bool Engine::shouldClose() {
	return glfwWindowShouldClose(context->window) == GLFW_TRUE;
}

void Engine::swapBuffers() {
	glfwSwapBuffers(context->window);
}

void Engine::pollEvents() {
	glfwPollEvents();
}

void Engine::fetchWindowSize(int &w, int &h) {
	glfwGetWindowSize(context->window, &w, &h);
}

#endif


void Engine::updateSize() {
	int w, h;
	fetchWindowSize(w, h);
	state->internalSize((f32)w / h);
	renderer->resize(w, h);
}

typedef std::chrono::high_resolution_clock::time_point TP;

TP now() {
	return std::chrono::high_resolution_clock::now();
}

double count(TP a, TP b) {
	return std::chrono::duration_cast<std::chrono::duration<double>>(a - b).count();
}

void Engine::begin() {
	TP t0 = now();
	TP t = t0;
	double dt;

	init();

	while (!shouldClose()) {
		updateSize();

		TP t1 = now();
		dt = count(t1, t);

		update(dt);

		#ifdef FPS_LOG
		printf("%f FPS at %f\n", 1 / dt, count(t1, t0));
		#endif

		t = now();

		render();

		#ifdef FRAMETIME_LOG
		TP t2 = now();

		printf("Time taken; update: %fs, render: %fs, total: %fs\n", count(t, t1), count(t2, t), count(t2, t1));
		#endif

		swapBuffers();
		pollEvents();
	}
}

Engine *Engine::create(std::string name, State *state) {
	Context *c = Context::create(name);
	if (c == nullptr)return nullptr;

	Engine *e = new Engine();
	e->context = c;
	e->state = state;

	#ifdef __DESKTOP__
	glfwSetWindowUserPointer(c->window, e);
	e->input = InputHandler::create(c->window);
	#endif

	if (e->input == nullptr) {
		delete e;
		printf("Couldn't get input!\n");
		return nullptr;
	}
	
	return e;
}

Engine::~Engine() {
	delete context;
	delete input;
	delete state;
	delete renderer;
	delete resources;
}

int Engine::getWidth() {
	return renderer->getWidth();
}

int Engine::getHeight() {
	return renderer->getHeight();
}

InputHandler *Engine::getInput() {
	return input;
}

void Engine::init() {
	reflo::Reflection::exportReflectionData("Data/Reflection.xml");

	resources = new ResourcePile();
	renderer = new RenderEngine(resources);

	state->staticResources = resources;
	state->internalInit(input, renderer);
	state->init();

	updateSize();
	renderer->init();
}

void Engine::update(double dt) {
	state->internalUpdate(dt);
	state->update(dt);

	renderer->update();
	input->update();
}

void Engine::render() {
	renderer->render(state->getWorld()->getMainCamera());
}
