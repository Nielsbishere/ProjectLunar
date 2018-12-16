#pragma once
#include "../../Type/OTypes.h"
#include "../../GameObjectBehaviour/Transform.h"
#include "../../Shapes/AABB.h"
#include <vector>
namespace lun {
	class Camera;
	class LineRenderer;
	class Shader;

	//Struct for storing a wire in the wireframe
	struct Wire {
		Transform wireToModel;
		LineRenderer *line;

		Wire(Transform _wireToModel, LineRenderer *_line);
		bool operator<(const Wire &w);
	};

	class Wireframe {

	public:

		//Create wireframe from wires
		Wireframe();


		//Render wireframe
		void render(Shader *s, mat4 m, Camera *c, vec3 lineColor = vec3(), f32 lineSize = 1.f);

		//Render multiple wireframes
		void render(std::vector<mat4> ms, Shader *s, Camera *c, vec3 lineColor = vec3(), f32 lineSize = 1.f);


		//Add wire
		void add(LineRenderer *line, Transform t);

		//Remove wire
		void remove(u32 wireIndex);

		
		//Get line renderer from wire
		LineRenderer *getLine(const u32 i);

		//@return AABB bounding box
		AABB getAABB();

		//Get wire count
		u32 size();

	protected:
		void refreshAABB();

	private:

		std::vector<Wire> wires;
		AABB aabb;
	};
}