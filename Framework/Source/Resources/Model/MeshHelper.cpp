#include "../../../Headers/Resources/Model/MeshHelper.h"
#include "../../../Headers/Render/Mesh.h"
#include "../../../Headers/Resources/ResourcePile.h"
#include "../../../Headers/Render/Shader.h"
#include "../../../Headers/DataStructures/Grid2D.h"
using namespace lun;

void setValue(u32 index, u32 val, u8 *arr, u32 bytes) {
	switch (bytes) {
	case 2:
		((u16*)arr)[index] = val;
		return;
	case 4:
		((u32*)arr)[index] = val;
		return;
	default:
		arr[index] = val;
		return;
	}
}

Mesh *MeshHelper::createTopDown(ResourcePile *pile, std::string name, Shader *s, Grid2D *grid) {
	if (grid == nullptr) {
		printf("Couldn't generate mesh from NULL grid!\n");
		return nullptr;
	}

	if (pile == nullptr) {
		printf("Couldn't generate mesh into NULL ResourcePile\n");
		return nullptr;
	}

	if (s == nullptr) {
		printf("Couldn't generate mesh with NULL shader!\n");
		return nullptr;
	}

	if (s->getType() == COMPUTE) {
		printf("Couldn't generate mesh with compute shader!\n");
		return nullptr;
	}

	//TODO: Multi thread?

	u32 ps = grid->getPoints();
	u32 w = grid->getWidth();
	u32 h = grid->getHeight();

	if (w <= 1 || h <= 1) {
		printf("Grid doesn't have enough data to generate mesh!\n");
		return nullptr;
	}

	u32 ilen = (w - 1) * (h - 1) * 6;
	u32 vlen = 8 * ps;

	f32 min = f32_MAX;
	f32 max = f32_MIN;

	f32 *vertex = new f32[vlen];
	u32 perIndex = ps <= 256 ? 1 : (ps <= 65536 ? 2 : 4);
	u8 *indices = perIndex == 1 ? new u8[ilen] : (perIndex == 2 ? (u8*)new u16[ilen] : (u8*)new u32[ilen]);

	for (u32 l = 0; l < ps; ++l) {
		u32 i = l % w, j = l / w;
		vec2 uv = vec2((f32)i, (f32)j) / vec2((f32)w - 1.f, (f32)h - 1.f);
		vec2 dir = grid->getDelta(i, j);

		f32 y = 0;

		vec3 tpos = *(vec3*)&vertex[8 * l] = vec3(uv.x * 2 - 1, y = grid->get(i, j) * 2 - 1, uv.y * 2 - 1);
		*(vec2*)&vertex[8 * l + 3] = uv;
		vec3 tnorm = *(vec3*)&vertex[8 * l + 5] = vec3(dir.x, 1, dir.y).normalize();

		if (i < w - 1 && j < h - 1) {
			u32 m = j * (w - 1) + i;
			setValue(m * 6, l, indices, perIndex); setValue(m * 6 + 5, l, indices, perIndex);
			setValue(m * 6 + 4, l + 1, indices, perIndex);
			setValue(m * 6 + 2, l + 1 + w, indices, perIndex); setValue(m * 6 + 3, l + 1 + w, indices, perIndex);
			setValue(m * 6 + 1, l + w, indices, perIndex);
		}

		if (y < min)
			min = y;
		if (y > max)
			max = y;
	}

	GLuint vbo = OGLHelper::createVBO((GLubyte*)vertex, vlen * 4);
	GLuint ibo = OGLHelper::createIBO((GLubyte*)indices, ilen * perIndex);
	GLuint vao = OGLHelper::createDefaultVAO(vbo, ibo);

	Mesh *m = new Mesh(AABB(vec3(-1, min, -1), vec3(1, max, 1)), s, vbo, ibo, vao, vlen * 4, ilen * perIndex, perIndex);
	pile->addRenderer(m, name);

	delete[] vertex;

	if (perIndex == 1)
		delete[] indices;
	else if (perIndex == 2)
		delete[](u16*)indices;
	else
		delete[](u32*)indices;

	return m;
}