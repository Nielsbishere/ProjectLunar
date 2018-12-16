#include "../../../Headers/Render/Line/LineRenderer.h"
#include "../../../Headers/CrossPlatform/CrossPlatform.h"
#include "../../../Headers/Helper/OGLHelper.h"
#include "../../../Headers/Render/Shader.h"
#include "../../../Headers/Camera/Camera.h"
#include <algorithm>
using namespace lun;

LineRenderer::LineRenderer(std::vector<Node> _nodeList) {
	nodeList = std::vector<Node>(_nodeList.size());
	for (u32 i = 0; i < _nodeList.size(); ++i) {
		Node &n = _nodeList[i];
		n.setId(i);
		nodeList[i] = n;
	}
	id = 0;
	if (_nodeList.size() != 0)
		generateMesh();
}

LineRenderer::~LineRenderer() {
	if (isRenderable())
		destroyMesh();
}

LineRenderer *LineRenderer::copy() {
	return new LineRenderer(nodeList);
}

void LineRenderer::add(Node n) {
	for (u32 i = 0; i < nodeList.size(); ++i)
		if (nodeList[i].getPosition() == n.getPosition())
			return;

	n.setId((u32)nodeList.size());
	nodeList.push_back(n);
	generateMesh();
}

void LineRenderer::add(std::vector<Node> nodes) {
	for (u32 j = (u32)nodes.size() - 1; j != u32_MAX; --j) {
		for (u32 i = 0; i < nodeList.size(); ++i)
			if (nodeList[i].getPosition() == nodes[j].getPosition()) {
				nodeList.erase(nodeList.begin() + i);
				break;
			}
	}
	if (nodes.size() == 0)
		return;

	u32 size = (u32)nodeList.size();
	nodeList.resize(size + nodes.size());
	for (u32 i = 0; i < nodes.size(); ++i) {
		Node &n = nodes[i];
		n.setId(i);
		nodeList[size + i] = n;
	}
	generateMesh();
}

void LineRenderer::remove(Node n) {
	for (u32 i = 0; i < nodeList.size(); ++i) {
		if (nodeList[i].getPosition() == n.getPosition()) {
			nodeList.erase(nodeList.begin() + i);
			generateMesh();
			return;
		}
	}
}

void LineRenderer::remove(std::vector<Node> nodes) {
	for (u32 i = 0; i < nodes.size(); ++i) {
		for (u32 j = 0; j < nodeList.size(); ++j) {
			if (nodeList[j].getPosition() == nodes[i].getPosition()) {
				nodeList.erase(nodeList.begin() + i);
				break;
			}
		}
	}
	generateMesh();
}

void LineRenderer::remove(u32 i) {
	if (i >= nodeList.size()) return;
	nodeList.erase(nodeList.begin() + i);
	generateMesh();
}

void LineRenderer::remove(std::vector<u32> indices) {
	std::sort(indices.begin(), indices.end());
	for (u32 i = (u32)indices.size() - 1; i != u32_MAX; --i) {
		u32 id = indices[i];
		if (id >= nodeList.size()) continue;
		indices.erase(indices.begin() + id);
	}
	generateMesh();
}

void LineRenderer::destroyMesh() {
	if (!isRenderable()) return;
	OGLHelper::destroyVBO(id);
	OGLHelper::destroyVAO(vao);
	id = 0;
	vao = 0;
}

void LineRenderer::generateMesh() {
	if (isRenderable()) destroyMesh();

	if (nodeList.size() > 1) {
		std::vector<Node> tnodeList((nodeList.size() - 1) * 2);
		for (u32 i = 0; i < nodeList.size() - 1; ++i) {
			tnodeList[i * 2] = nodeList[i];
			tnodeList[i * 2 + 1] = nodeList[i + 1];
		}

		u32 length;
		f32 *data = new f32[length = ((u32)tnodeList.size() * 3)];
		for (u32 i = 0; i < tnodeList.size(); ++i) {
			data[i * 3 + 0] = tnodeList[i].getPosition().x;
			data[i * 3 + 1] = tnodeList[i].getPosition().y;
			data[i * 3 + 2] = tnodeList[i].getPosition().z;
		}
		id = OGLHelper::createVBO((GLubyte*)data, length * 4);

		vao = OGLHelper::createPositionVAO(id);

		vec3 min = vec3::max();
		vec3 max = vec3::min();
		for (u32 i = 0; i < nodeList.size(); ++i) {
			vec3 &pos = nodeList[i].getPosition();
			min = vec3::min(min, pos);
			max = vec3::max(max, pos);
		}
		aabb = AABB(min, max);
	}
	aabb = AABB();
}

bool LineRenderer::isRenderable() { return id != 0; }

void LineRenderer::bind(Shader *s) {
	OGLHelper::bindVAO(vao);
}

void LineRenderer::unbind() {
	OGLHelper::bindVAO(0);
}

void LineRenderer::render(Shader *s, mat4 m, Camera *c) {
	if (!isRenderable()) return;

	s->set("M", m);
	s->set("V", c->getView());
	s->set("P", c->getProjection());
	bind(s);
	OGLHelper::drawLines((u32)(nodeList.size()-1) * 2);
	unbind();
}

void LineRenderer::nobindRender(Shader *s, mat4 m) {
	if (!isRenderable()) return;

	s->set("M", m);
	OGLHelper::drawLines((u32)(nodeList.size()-1)*2);
}

std::vector<Node> LineRenderer::getNodes() { return nodeList; }