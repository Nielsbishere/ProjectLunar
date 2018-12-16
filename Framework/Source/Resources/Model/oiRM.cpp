#include "../../../Headers/Resources/Model/oiRM.h"
#include "../../../Headers/Render/Mesh.h"
#include "../../../Headers/Helper/OGLHelper.h"
#include "../../../Headers/Render/Shader.h"
#include "../../../Headers/DataStructures/Bitset.h"
#include <iostream>
#include <fstream>
using namespace lun;
using namespace std;

Mesh *oiRM::load(std::string name, Shader *s, bool log) {
	if (s == nullptr) {
		printf("Couldn't read file with path \"%s\". Missing shader\n", name.c_str());
		return nullptr;
	}

	if (s->getType() == EShaderType::COMPUTE) {
		printf("Couldn't read file with path \"%s\". Attached shader is of type 'compute' and can't be attached to an object\n", name.c_str());
		return nullptr;
	}

	Bitset bs = Bitset::readData(name);

	if (bs.getBytes() < sizeof(oiRMHead)) {
		printf("Couldn't read file with path \"%s\". File is an incorrect size!\n", name.c_str());
		return nullptr;
	}

	std::string str = bs.readString(0, 4);

	if (str != "oiRM") {
		printf("Couldn't read file with path \"%s\". File has an incorrect header!\n", name.c_str());
		return nullptr;
	}

	u32 vertices = bs.readUInt(32);
	u32 indices = bs.readUInt(32 + 32);
	u8 perIndex = vertices <= u8_MAX ? 1 : (vertices <= u16_MAX ? 2 : 4);
	u32 vertLength = sizeof(oiRMVertex) * vertices;
	u32 indLength = perIndex * indices;

	if (bs.getBytes() != sizeof(oiRMHead) + vertLength + indLength) {
		printf("Couldn't read file with path \"%s\". Bitset has incorrect size!\n", name.c_str());
		return nullptr;
	}

	f32 *farray = bs.readFloatArray(32 * 3, vertLength / sizeof(f32));
	u8 *barray;
	u32 bitOff = 32 * 3 + vertLength * 8;

	switch (perIndex) {
		case 1:
			barray = (u8*)bs.readUByteArray(bitOff, indices);
			break;
		case 2:
			barray = (u8*)bs.readUShortArray(bitOff, indices);
			break;
		default:
			barray = (u8*)bs.readUIntArray(bitOff, indices);
			break;
	}

	GLuint vbo = OGLHelper::createVBO((GLubyte*)farray, vertLength);
	GLuint ibo = OGLHelper::createIBO((GLubyte*)barray, indLength);
	GLuint vao = OGLHelper::createDefaultVAO(vbo, ibo);

	if (vbo == 0 || ibo == 0 || vao == 0) {

		if (vbo != 0)
			OGLHelper::destroyVBO(vbo);
		if (ibo != 0)
			OGLHelper::destroyIBO(ibo);
		if (vao != 0)
			OGLHelper::destroyVAO(vao);

		printf("Couldn't read file with path \"%s\". Couldn't create VBO, IBO or VAO\n", name.c_str());
		delete[] farray;
		delete[] barray;
		return nullptr;
	}

	if(log)
		printf("Successfully read file with path \"%s\"!\n", name.c_str());

	vec3 mi = vec3::max();
	vec3 ma = vec3::min();

	for (u32 i = 0; i < vertices; ++i) {
		vec3 &v = *(vec3*)(farray + i * sizeof(oiRMVertex) / sizeof(f32));
		if (v.x < mi.x)mi.x = v.x;
		if (v.y < mi.y)mi.y = v.y;
		if (v.z < mi.z)mi.z = v.z;
		if (v.x > ma.x)ma.x = v.x;
		if (v.y > ma.y)ma.y = v.y;
		if (v.z > ma.z)ma.z = v.z;
	}

	Mesh *m = new Mesh(AABB(mi, ma), s, vbo, ibo, vao, indices, vertices, perIndex);

	delete[] farray;
	delete[] barray;

	printf("Loaded model \"%s\"\n", name.c_str());

	return m;
}
void oiRM::write(std::string file, Mesh *m) {
	ofstream out(file, ios::binary | ios::out);
	if (!out.good()) {
		out.close();
		printf("Couldn't write file with path \"%s\"\n", file.c_str());
		return;
	}

	int debug = 0;

	Bitset bits((4 * 3 + m->getVertices() * sizeof(oiRMVertex) + m->inds * m->getIndices()) * 8);
	bits.writeByte('o', 0);
	bits.writeByte('i', 8);
	bits.writeByte('R', 16);
	bits.writeByte('M', 24);
	bits.writeUInt(m->getVertices(), 32);
	bits.writeUInt(m->getIndices(), 64);

	//Vertex array
	u32 len = sizeof(oiRMVertex) * m->getVertices();
	char *dat = new char[len];
	OGLHelper::copyVBO(m->vbo, len, dat);
	for (u32 i = 0; i < len / sizeof(f32); ++i) 
		bits.writeFloat(*(f32*)&dat[i * sizeof(f32)], 32 * 3 + i * 32);
	//Write float array
	delete[] dat;

	//Index array
	len = m->inds * m->getIndices();
	dat = new char[len];
	OGLHelper::copyVBO(m->ibo, len, dat);
	for (u32 i = 0; i < len / m->inds; ++i) {
		if (m->inds == 1)
			bits.writeUByte(*(u8*)&dat[i * m->inds], 32 * 3 + m->getVertices() * sizeof(oiRMVertex) * 8 + m->inds * i * 8);
		else if (m->inds == 2)
			bits.writeUShort(*(u16*)&dat[i * m->inds], 32 * 3 + m->getVertices() * sizeof(oiRMVertex) * 8 + m->inds * i * 8);
		else if (m->inds == 4)
			bits.writeUInt(*(u32*)&dat[i * m->inds], 32 * 3 + m->getVertices() * sizeof(oiRMVertex) * 8 + m->inds * i * 8);
	}
	delete[] dat;

	dat = bits.copyData();
	out.write(dat, bits.getBytes());
	delete[] dat;
	out.close();
	printf("Wrote model to \"%s\"\n", file.c_str());
}