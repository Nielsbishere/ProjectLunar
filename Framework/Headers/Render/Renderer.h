#pragma once
#include "../Type/OTypes.h"
#include "../Shapes/AABB.h"
#include "../Camera/Camera.h"
#include <string>
namespace lun {
	class Shader;

	//Types of renderers
	//	MESH; 1 material applied to a mesh
	enum ERenderer {
		MESH
	};

	//Class responsible for rendering everything
	class Renderer {
		template<class T> friend class ResourceObject;
		friend class RenderComponent;
		friend struct RCHolder;
		friend class RenderEngine;
		friend class BatchRender;
		friend class UIObject;

	public:
		//Render via camera
		//@param mat4 model matrix
		//@param Camera *c
		void render(mat4 model, Camera *camera);

		//@return AABB boundingBox
		AABB getAABB();

		//@return ERenderer renderType
		ERenderer getType();

		//@return Shader *shader
		Shader *getShader();

	protected:
		//Shared variables along all render types
		Renderer(AABB aabb, Shader *s, ERenderer type);

		//Get rid of renderer
		virtual ~Renderer();

		//Virtual function for binding buffers
		virtual void bind() = 0;

		//Virtual function for rendering without binding buffers
		virtual void nobindRender(mat4 m, mat4 v, mat4 p, vec3 eye) = 0;

		//Virtual function for rendering without binding and sending matrices
		virtual void instancedRender(u32 amount) = 0;

		//Virtual function for unbinding buffers
		virtual void unbind() = 0;

		//Function for rendering to camera
		void nobindRender(mat4 m, Camera *c);

		//Virtual function for rendering with binding
		virtual void render(mat4 m, mat4 v, mat4 p, vec3 eye) = 0;

	private:
		AABB aabb;
		Shader *s;
		ERenderer type;
	};
}