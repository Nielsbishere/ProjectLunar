#pragma once
#include <vector>
#include "Node.h"
#include "../../CrossPlatform/CrossPlatform.h"
#include "../../Shapes/AABB.h"
namespace lun {
	class Shader;
	class Camera;
	class LineRenderer {

		friend class RenderEngine;
		friend class Wireframe;

	public:

		//Create line mesh from node array
		LineRenderer(std::vector<Node> _nodeList);

		//Remove line renderer
		~LineRenderer();

		//Copy a line as a base for adding new nodes
		LineRenderer *copy();

		//Add node to array and refresh the mesh
		void add(Node n);

		//Add nodes to array and refresh the mesh
		void add(std::vector<Node> nodes);

		//Remove node from array and refresh the mesh (by node (position))
		void remove(Node n);

		//Remove nodes from array and refresh the mesh (by node (position))
		void remove(std::vector<Node> nodes);

		//Remove node from array and refresh the mesh (by id)
		void remove(u32 i);

		//Remove nodes from array and refresh the mesh (by id)
		void remove(std::vector<u32> indices);

		//Destroy mesh
		void destroyMesh();

		//Generate mesh
		void generateMesh();

		//@return bool isRenderable
		bool isRenderable();

		//@return std::vector<Node> nodeList
		std::vector<Node> getNodes();

	protected:

		void bind(Shader *s);
		void unbind();
		void render(Shader *s, mat4 m, Camera *c);
		void nobindRender(Shader *s, mat4 m);

	private:

		AABB aabb;
		std::vector<Node> nodeList;
		GLuint id, vao;
	};
}