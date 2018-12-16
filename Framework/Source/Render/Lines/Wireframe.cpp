#include "../../../Headers/Render/Line/Wireframe.h"
#include "../../../Headers/Camera/Camera.h"
#include "../../../Headers/Render/Shader.h"
#include "../../../Headers/Render/Line/LineRenderer.h"
#include "../../../Headers/Helper/OGLHelper.h"
#include <algorithm>
using namespace lun;

Wire::Wire(Transform _wireToModel, LineRenderer *_line) : wireToModel(_wireToModel), line(_line) { }
bool Wire::operator<(const Wire &w) { return line < w.line; }

Wireframe::Wireframe() : wires(std::vector<Wire>()) { }


void Wireframe::render(Shader *s, mat4 m, Camera *c, vec3 lineColor, f32 lineSize) {
	s->set("lineColor", lineColor);

	std::vector<Wire> _wires = wires;
	sort(_wires.begin(), _wires.end());

	OGLHelper::setLineSize(lineSize);
	LineRenderer *prev = nullptr;
	for (u32 i = 0; i < size(); ++i) {
		LineRenderer *lr = _wires[i].line;
		if (prev != lr) {
			if (prev != nullptr)
				lr->unbind();

			lr->bind(s);
			prev = lr;
		}
		mat4 M = m * _wires[i].wireToModel.makeModelMatrix();
		lr->nobindRender(s, M);
	}

	if (prev != nullptr)
		prev->unbind();
}

void Wireframe::render(std::vector<mat4> ms, Shader *s, Camera *c, vec3 lineColor, f32 lineSize) {
	s->set("lineColor", lineColor);

	std::vector<Wire> _wires = wires;
	sort(_wires.begin(), _wires.end());

	OGLHelper::setLineSize(lineSize);
	LineRenderer *prev = nullptr;
	for (u32 i = 0; i < size(); ++i) {
		LineRenderer *lr = _wires[i].line;
		if (prev != lr) {
			if (prev != nullptr)
				lr->unbind();

			lr->bind(s);
			prev = lr;
		}
		for (u32 j = 0; j < ms.size(); ++j) {
			mat4 M = ms[j] * _wires[i].wireToModel.makeModelMatrix();
			lr->nobindRender(s, M);
		}
	}

	if (prev != nullptr)
		prev->unbind();
}

void Wireframe::add(LineRenderer *line, Transform t) {
	if (line == nullptr) return;
	wires.push_back(Wire(t, line));
	refreshAABB();
}

void Wireframe::remove(u32 wireIndex) {
	if (wireIndex >= wires.size()) return;
	wires.erase(wires.begin() + wireIndex);
	refreshAABB();
}

LineRenderer *Wireframe::getLine(const u32 i) {
	if (i >= wires.size()) return nullptr;
	return wires[i].line;
}

void Wireframe::refreshAABB() {
	if (wires.size() == 0) {
		aabb = AABB();
		return;
	}
	vec3 min = vec3::max();
	vec3 max = vec3::min();

	for (u32 i = 0; i < wires.size(); ++i) {
		LineRenderer *lr = wires[i].line;
		std::vector<Node> pts = lr->getNodes();

		for (u32 j = 0; j < pts.size(); ++j) {
			vec3 p = wires[i].wireToModel.makeModelMatrix() * vec4(pts[j].getPosition(), 1);
			min = vec3::min(min, p);
			max = vec3::max(max, p);
		}
	}

	aabb = AABB(min, max);
}
AABB Wireframe::getAABB() { return aabb; }

u32 Wireframe::size() { return (u32)wires.size(); }
