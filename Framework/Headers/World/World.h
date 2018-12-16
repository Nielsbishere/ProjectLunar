#pragma once
#include <vector>
#include "../../Headers/Type/OTypes.h"
namespace lun {
	class GameObject;
	class Camera;
	class RenderComponent;
	class InputHandler;
	class RenderEngine;
	class RenderObject;

	class World {
		friend class Engine;
		friend class State;

	private:

		std::vector<GameObject*> objects;
		bool contains(GameObject *go, u32 &u);

		Camera *camera;
		InputHandler *input;
		RenderEngine *render;

	protected:

		~World();
		World(InputHandler *ih, RenderEngine *_re);

	public:

		//Whether or not a GameObject is already spawned
		bool contains(GameObject *go);

		//Spawn a GameObject
		bool spawn(GameObject *go);

		//Spawn all GameObjects
		void spawnAll(std::vector<GameObject*> &objects);

		//Destroy GameObject
		bool destroy(GameObject *go);

		//Update all GameObjects
		void update(double delta);

		//Update aspect of main camera
		void updateAspect(f32 asp);

		//@return Camera *mainCamera
		Camera *getMainCamera();

		//@return RenderEngine *renderEngine
		RenderEngine *getRenderEngine();
	};
}