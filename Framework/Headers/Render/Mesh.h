#pragma once
#include "Renderer.h"
#include "../CrossPlatform/CrossPlatform.h"
namespace lun {
	class Mesh : public Renderer {
		friend class oiRM;
		friend class MeshHelper;
		template<class T> friend class ResourceObject;

	private:

		GLuint vbo, ibo, vao;
		u32 ilen, inds, verts;

	protected:

		//Save mesh buffers and AABB
		Mesh(AABB aabb, Shader *s, GLuint vbo, GLuint ibo, GLuint vao, u32 len, u32 vert, u32 ind);

		//Remove mesh buffers
		~Mesh();

		//Bind buffers
		void bind() override;

		//Render without binding & unbinding
		void nobindRender(mat4 m, mat4 v, mat4 p, vec3 eye) override;

		//Render without sending matrices (since they are already at the GPU)
		void instancedRender(u32 amount) override;

		//Unbind buffers
		void unbind() override;

		//Get number of indices
		u32 getIndices();

		//Get number of vertices
		u32 getVertices();

	public:

		void render(mat4 m, mat4 v, mat4 p, vec3 eye) override;
	};
}