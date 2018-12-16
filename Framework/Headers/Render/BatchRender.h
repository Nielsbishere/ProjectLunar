#pragma once
#include "../Shapes/AABB.h"
#include "../CrossPlatform/Context.h"
#include <vector>
namespace lun {
	class RenderObject;
	class Renderer;
	class Camera;

	//Efficiently render a lot of objects
	//Stores a bunch of model matrices on the GPU and waits to draw them
	class BatchRender {
		friend class RenderEngine;
		friend class RenderData;
	protected:
		//Create batch render from RenderObjects
		BatchRender(std::vector<RenderObject*> &ros);

		//Remove data from GPU
		~BatchRender();

		//Render the instances
		void render(Camera *c);

	private:
		GLuint batch;
		AABB boundingBox;
		Renderer *r;
		u32 size;
	};
}