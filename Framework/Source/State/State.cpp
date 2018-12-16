#include "../../Headers/State/State.h"
using namespace lun;

World *State::getWorld() { return world; }
InputHandler *State::getInput() { return input; }
RenderEngine *State::getRenderer() { return renderer; }
ResourcePile *State::getPile() { return resources; }
ResourcePile *State::getGlobalPile() { return staticResources; }		//TODO: Read/write, read, write resource pile

State::~State() {
	if (hasInit) {
		delete world;
		delete resources;
	}
}

void State::internalInit(InputHandler *_input, RenderEngine *_renderer) { 
	renderer = _renderer;
	input = _input; 
	resources = new ResourcePile(); 
	world = new World(_input, _renderer);
	hasInit = true; 
}

void State::internalUpdate(f64 delta) { world->update(delta); }
void State::internalSize(f32 aspect) { world->updateAspect(aspect); }