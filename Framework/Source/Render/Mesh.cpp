#include "../../Headers/Render/Mesh.h"
#include "../../Headers/CrossPlatform/Context.h"
#include "../../Headers/Render/Shader.h"
#include "../../Headers/Helper/OGLHelper.h"
using namespace lun;

//Constructor
Mesh::Mesh(AABB _aabb, Shader *_s, GLuint _vbo, GLuint _ibo, GLuint _vao, u32 len, u32 vert, u32 ind) : Renderer(_aabb, _s, MESH), vbo(_vbo), ibo(_ibo), vao(_vao), ilen(len), verts(vert), inds(ind) {}
Mesh::~Mesh() {
	OGLHelper::destroyVBO(vbo);
	OGLHelper::destroyIBO(ibo);
	OGLHelper::destroyVAO(vao);
}

//Binding
void Mesh::bind(){
	OGLHelper::bindVAO(vao);
}

void Mesh::unbind() {
	OGLHelper::bindVAO(0);
}


//Render calls
void Mesh::nobindRender(mat4 m, mat4 v, mat4 p, vec3 eye){
	getShader()->set("MVP", p * v * m);
	getShader()->set("M", m);
	OGLHelper::drawElements(ilen, inds);
}

void Mesh::instancedRender(u32 amount) {
	OGLHelper::drawElementsInstanced(ilen, inds, amount);
}

void Mesh::render(mat4 m, mat4 v, mat4 p, vec3 eye){
	getShader()->use();
	bind(); 
	getShader()->set("V", v);
	getShader()->set("P", p);
	getShader()->set("eye", eye);
	nobindRender(m, v, p, eye);
	unbind();
}

//Getters

u32 Mesh::getIndices() { return ilen; }
u32 Mesh::getVertices() { return verts; }