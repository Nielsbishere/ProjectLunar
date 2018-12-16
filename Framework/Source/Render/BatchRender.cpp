#include "../../Headers/Render/BatchRender.h"
#include "../../Headers/Render/RenderObject.h"
#include "../../Headers/Render/Renderer.h"
#include "../../Headers/Helper/OGLHelper.h"
#include "../../Headers/Render/Shader.h"
using namespace lun;

BatchRender::BatchRender(std::vector<RenderObject*> &ros) {
	r = ros[0]->getRenderer();

	vec3 mi = vec3::max(), ma = vec3::min();

	mat4 *matrices = new mat4[size = (u32)ros.size()];
	for (u32 i = 0; i < size; ++i) {
		mat4 m = ros[i]->getTransform().makeModelMatrix();
		matrices[i] = m;
		AABB box = r->getAABB() * m;
		mi = vec3::min(box.getMin(), mi);
		ma = vec3::max(box.getMax(), ma);
	}

	batch = OGLHelper::createVBO((GLubyte*)matrices, sizeof(mat4) * size);
	delete[] matrices;

	boundingBox = AABB(mi, ma);
}
BatchRender::~BatchRender() {
	OGLHelper::destroyVBO(batch);
}
void BatchRender::render(Camera *c) {
	Shader *s = r->getShader();

	s->use();
	s->set("V", c->getView());
	s->set("P", c->getProjection());
	s->set("eye", c->getPosition());
	s->set("instanced", true);

	r->bind();
	OGLHelper::bindVBO(batch);


	u32 vec4Size = sizeof(vec4);
	GLchar *ptr = (GLchar*)0;
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, ptr);
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, ptr + vec4Size);
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, ptr + vec4Size * 2);
	glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, ptr + vec4Size * 3);

	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);
	glVertexAttribDivisor(6, 1);

	//Render pass
	r->instancedRender(size);

	//Unbinding instance
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);
	glDisableVertexAttribArray(5);
	glDisableVertexAttribArray(6);

	OGLHelper::bindVBO(0);
	r->unbind();
}