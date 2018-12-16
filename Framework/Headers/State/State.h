#pragma once
#include "../World/World.h"
#include "../Resources/ResourcePile.h"
namespace lun {
	class State {
		friend class Engine;

	public:

		virtual void init() = 0;
		virtual void update(f64 delta) = 0;

	protected:

		World *getWorld();
		InputHandler *getInput();
		RenderEngine *getRenderer();
		ResourcePile *getPile();
		ResourcePile *getGlobalPile();

		virtual ~State();

	private:

		World *world;
		ResourcePile *resources;
		InputHandler *input;
		RenderEngine *renderer;

		ResourcePile *staticResources;

		bool hasInit;

		void internalInit(InputHandler *_input, RenderEngine *_renderer);
		void internalUpdate(f64 delta);
		void internalSize(f32 aspect);
	};
}