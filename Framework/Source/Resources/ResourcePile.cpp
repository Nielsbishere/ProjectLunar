#include "../../Headers/Resources/ResourcePile.h"
#include "../../Headers/Helper/StringHelper.h"
#include "../../Headers/Resources/Model/oiRM.h"
#include "../../Headers/Render/Shader.h"
#include <fstream>
using namespace lun;

ResourcePile::ResourcePile(){}
ResourcePile::~ResourcePile(){
	for (u32 i = 0; i < textures.size(); i++)
		delete textures[i];
	for (u32 i = 0; i < renderers.size(); i++)
		delete renderers[i];
	for (u32 i = 0; i < shaders.size(); i++)
		delete shaders[i];
	for (u32 i = 0; i < lines.size(); i++)
		delete lines[i];
	for (u32 i = 0; i < wires.size(); i++)
		delete wires[i];
}
EResourceType ResourcePile::getResourceType(std::string path) {
	if (StringHelper::endsWithIgnoreCase(path, ".oiRM")) return OIRM;
	if (StringHelper::endsWithIgnoreCase(path, ".oiEM")) return OIEM;
	if (StringHelper::endsWithIgnoreCase(path, ".oiOM")) return OIOM;
	if (StringHelper::endsWithIgnoreCase(path, ".oiM")) return OIM;
	if (StringHelper::endsWithIgnoreCase(path, ".oGLSL")) return OGLSL;
	if (StringHelper::endsWithIgnoreCase(path, ".PNG")) return PNG;
	if (StringHelper::endsWithIgnoreCase(path, ".JPG")) return JPG;
	if (StringHelper::endsWithIgnoreCase(path, ".oiCT")) return OICT;
	if (StringHelper::endsWithIgnoreCase(path, ".SVG")) return SVG;
	if (StringHelper::endsWithIgnoreCase(path, ".oiCVI")) return OICVI;
	if (StringHelper::endsWithIgnoreCase(path, ".OGG")) return OGG;
	if (StringHelper::endsWithIgnoreCase(path, ".oiMF")) return OIMF;
	if (StringHelper::endsWithIgnoreCase(path, ".oiVID")) return OIVID;
	if (StringHelper::endsWithIgnoreCase(path, ".oiCL")) return OICL;
	if (StringHelper::endsWithIgnoreCase(path, ".oiCLD")) return OICLD;
	if (StringHelper::endsWithIgnoreCase(path, ".oiLR")) return OILR;
	if (StringHelper::endsWithIgnoreCase(path, ".oiWF")) return OIWF;
	return UNSUPPORTED;
}
EFileType ResourcePile::getFileType(std::string path) {
	return (EFileType)((getResourceType(path) & 0xFF00) >> 8);
}

Renderer *ResourcePile::loadModel(std::string path, std::string name, Shader *s) {
	for (u32 i = 0; i < renderers.size(); i++)
		if (StringHelper::equalsIgnoreCase(path, renderers[i]->getPath()) && StringHelper::equalsIgnoreCase(name, renderers[i]->getName())) 
			return renderers[i]->load();

	std::ifstream in(path, std::ios::in);
	if (!in.good()) {
		in.close();
		printf("Couldn't open file \"%s\"\n", path.c_str());
		return nullptr;
	}
	in.close();
	EFileType ft = getFileType(path);
	if (ft == UNDEF) {
		printf("Couldn't open file \"%s\". File type is not supported by the engine!\n", path.c_str());
		return nullptr;
	}
	if (ft != MODEL) {
		printf("Couldn't open file \"%s\". File is not a model!\n", path.c_str());
		return nullptr;
	}
	if (s == nullptr) {
		printf("Couldn't add model \"%s\". Requested shader is a null pointer!\n", path.c_str());
		return nullptr;
	}
	EResourceType ert = getResourceType(path);
	Renderer *r = nullptr;
	switch (ert) {
	case OIRM:
		r = (Renderer*)oiRM::load(path, s);
		break;
	default:
		printf("Couldn't open file \"%s\". File reading is not yet implemented!\n", path.c_str());
		return nullptr;
	}
	if (r == nullptr) {
		printf("Couldn't open file \"%s\". File couldn't be parsed!\n", path.c_str());
		return nullptr;
	}

	ResourceObject<Renderer> *ro = new ResourceObject<Renderer>(path, name, r);
	ro->daddy = this;
	renderers.push_back(ro);
	return r;
}

void ResourcePile::addRenderer(Renderer *r, std::string name) {
	ResourceObject<Renderer> *ro = new ResourceObject<Renderer>("///temp///::" + name, name, r);
	ro->daddy = this;
	renderers.push_back(ro);
}

Texture *ResourcePile::loadTexture(std::string path, std::string name){
	for (u32 i = 0; i < textures.size(); i++)
		if (StringHelper::equalsIgnoreCase(path, textures[i]->getPath()) && StringHelper::equalsIgnoreCase(name, textures[i]->getName()))
			return textures[i]->load();

	std::ifstream in(path, std::ios::in);
	if (!in.good()) {
		in.close();
		printf("Couldn't open file \"%s\"\n", path.c_str());
		return nullptr;
	}
	in.close();
	EFileType ft = getFileType(path);
	if (ft == UNDEF) {
		printf("Couldn't open file \"%s\". File type is not supported by the engine!\n", path.c_str());
		return nullptr;
	}
	if (ft != TEXTURE) {
		printf("Couldn't open file \"%s\". File is not a texture (pixel)!\n", path.c_str());
		return nullptr;
	}
	EResourceType ert = getResourceType(path);
	Texture *t = nullptr;
	switch (ert) {
	case PNG:
		t = Texture::load(path);
		break;
	case JPG:
		t = Texture::load(path);
		break;
	default:
		printf("Couldn't open file \"%s\". File reading is not yet implemented!\n", path.c_str());
		return nullptr;
	}
	if (t == nullptr) {
		printf("Couldn't open file \"%s\". File couldn't be parsed!\n", path.c_str());
		return nullptr;
	}

	ResourceObject<Texture> *ro = new ResourceObject<Texture>(path, name, t);
	ro->daddy = this;
	textures.push_back(ro);
	return t;
}
Shader *ResourcePile::loadShader(std::string path, std::string name){
	for (u32 i = 0; i < shaders.size(); i++)
		if (StringHelper::equalsIgnoreCase(path, shaders[i]->getPath()) && StringHelper::equalsIgnoreCase(name, shaders[i]->getName()))
			return shaders[i]->load();

	std::ifstream in(path, std::ios::in);
	if (!in.good()) {
		in.close();
		printf("Couldn't open file \"%s\"\n", path.c_str());
		return nullptr;
	}
	in.close();
	EFileType ft = getFileType(path);
	if (ft == UNDEF) {
		printf("Couldn't open file \"%s\". File type is not supported by the engine!\n", path.c_str());
		return nullptr;
	}
	if (ft != SHADER) {
		printf("Couldn't open file \"%s\". File is not a shader!\n", path.c_str());
		return nullptr;
	}
	EResourceType ert = getResourceType(path);
	Shader *s = nullptr;
	switch (ert) {
	case OGLSL:
		s = Shader::load(path);
		break;
	default:
		printf("Couldn't open file \"%s\". File reading is not yet implemented!\n", path.c_str());
		return nullptr;
	}
	if (s == nullptr) {
		printf("Couldn't open file \"%s\". File couldn't be parsed!\n", path.c_str());
		return nullptr;
	}

	ResourceObject<Shader> *ro = new ResourceObject<Shader>(path, name, s);
	ro->daddy = this;
	shaders.push_back(ro);
	return s;
}

LineRenderer *ResourcePile::loadLine(std::vector<Node> nodes, std::string name) {
	for (u32 i = 0; i < lines.size(); i++)
		if (StringHelper::equalsIgnoreCase(name, lines[i]->getName()))
			return lines[i]->load();
	
	LineRenderer *lr = new LineRenderer(nodes);
	ResourceObject<LineRenderer> *ro = new ResourceObject<LineRenderer>("null", name, lr);
	ro->daddy = this;
	lines.push_back(ro);

	return lr;
}
Wireframe *ResourcePile::loadWireframe(Wireframe frames, std::string name) {
	for (u32 i = 0; i < wires.size(); i++)
		if (StringHelper::equalsIgnoreCase(name, wires[i]->getName()))
			return wires[i]->load();

	Wireframe *wire = new Wireframe(frames);
	ResourceObject<Wireframe> *ro = new ResourceObject<Wireframe>("null", name, wire);
	ro->daddy = this;
	wires.push_back(ro);

	return wire;
}

bool ResourcePile::hasTexture(std::string name){
	for (u32 i = 0; i < textures.size(); i++)
		if (StringHelper::equalsIgnoreCase(name, textures[i]->getPath()) || StringHelper::equalsIgnoreCase(name, textures[i]->getName()))
			return true;
	return false;
}
bool ResourcePile::hasModel(std::string name){
	for (u32 i = 0; i < renderers.size(); i++)
		if (StringHelper::equalsIgnoreCase(name, renderers[i]->getPath()) || StringHelper::equalsIgnoreCase(name, renderers[i]->getName()))
			return true;
	return false;
}
bool ResourcePile::hasShader(std::string name){
	for (u32 i = 0; i < shaders.size(); i++)
		if (StringHelper::equalsIgnoreCase(name, shaders[i]->getPath()) || StringHelper::equalsIgnoreCase(name, shaders[i]->getName()))
			return true;
	return false;
}
bool ResourcePile::hasLine(std::string name) {
	for (u32 i = 0; i < lines.size(); i++)
		if (StringHelper::equalsIgnoreCase(name, lines[i]->getName()))
			return true;
	return false;
}
bool ResourcePile::hasWireframe(std::string name) {
	for (u32 i = 0; i < wires.size(); i++)
		if (StringHelper::equalsIgnoreCase(name, wires[i]->getName()))
			return true;
	return false;
}

Texture *ResourcePile::fetchTexture(std::string name) {
	for (u32 i = 0; i < textures.size(); i++)
		if (StringHelper::equalsIgnoreCase(name, textures[i]->getPath()) || StringHelper::equalsIgnoreCase(name, textures[i]->getName()))
			return textures[i]->getResource();
	return nullptr;
}
Renderer *ResourcePile::fetchModel(std::string name) {
	for (u32 i = 0; i < renderers.size(); i++)
		if (StringHelper::equalsIgnoreCase(name, renderers[i]->getPath()) || StringHelper::equalsIgnoreCase(name, renderers[i]->getName()))
			return renderers[i]->getResource();
	return nullptr;
}
Shader *ResourcePile::fetchShader(std::string name) {
	for (u32 i = 0; i < shaders.size(); i++)
		if (StringHelper::equalsIgnoreCase(name, shaders[i]->getPath()) || StringHelper::equalsIgnoreCase(name, shaders[i]->getName()))
			return shaders[i]->getResource();
	return nullptr;
}
LineRenderer *ResourcePile::fetchLine(std::string name) {
	for (u32 i = 0; i < lines.size(); i++)
		if (StringHelper::equalsIgnoreCase(name, lines[i]->getName()))
			return lines[i]->getResource();
	return nullptr;
}
Wireframe *ResourcePile::fetchWireframe(std::string name) {
	for (u32 i = 0; i < wires.size(); i++)
		if (StringHelper::equalsIgnoreCase(name, wires[i]->getName()))
			return wires[i]->getResource();
	return nullptr;
}

bool ResourcePile::unloadTexture(std::string name){
	for (u32 i = 0; i < textures.size(); i++)
		if (StringHelper::equalsIgnoreCase(name, textures[i]->getPath()) || StringHelper::equalsIgnoreCase(name, textures[i]->getName())) {
			bool del = textures[i]->destroy();
			if (del) {
				delete textures[i];
				textures.erase(textures.begin() + i);
			}
			return true;
		}
	return false;
}
bool ResourcePile::unloadModel(std::string name){
	for (u32 i = 0; i < renderers.size(); i++)
		if (StringHelper::equalsIgnoreCase(name, renderers[i]->getPath()) || StringHelper::equalsIgnoreCase(name, renderers[i]->getName())) {
			bool del = renderers[i]->destroy();
			if (del) {
				delete renderers[i];
				renderers.erase(renderers.begin() + i);
			}
			return true;
		}
	return false;
}
bool ResourcePile::unloadShader(std::string name){
	for (u32 i = 0; i < shaders.size(); i++)
		if (StringHelper::equalsIgnoreCase(name, shaders[i]->getPath()) || StringHelper::equalsIgnoreCase(name, shaders[i]->getName())) {
			bool del = shaders[i]->destroy();
			if (del) {
				delete shaders[i];
				shaders.erase(shaders.begin() + i);
			}
			return true;
		}
	return false;
}
bool ResourcePile::unloadLine(std::string name) {
	for (u32 i = 0; i < lines.size(); i++)
		if (StringHelper::equalsIgnoreCase(name, lines[i]->getName())) {
			bool del = lines[i]->destroy();
			if (del) {
				delete lines[i];
				lines.erase(lines.begin() + i);
			}
			return true;
		}
	return false;
}
bool ResourcePile::unloadWireframe(std::string name) {
	for (u32 i = 0; i < wires.size(); i++)
		if (StringHelper::equalsIgnoreCase(name, wires[i]->getName())) {
			bool del = wires[i]->destroy();
			if (del) {
				delete wires[i];
				wires.erase(wires.begin() + i);
			}
			return true;
		}
	return false;
}

bool ResourcePile::writeModel(std::string path, std::string name){
	bool contains = false;
	Renderer *r = nullptr;
	for (u32 i = 0; i < renderers.size(); i++)
		if (StringHelper::equalsIgnoreCase(name, renderers[i]->getName())) {
			contains = true;
			r = renderers[i]->getResource();
			break;
		}

	if (!contains) {
		printf("Couldn't write to \"%s\". There was no such object to write with name \"%s\"\n", path.c_str(), name.c_str());
		return false;
	}

	std::ofstream out(path, std::ios::out);
	if (!out.good()) {
		out.close();
		printf("Couldn't open file \"%s\"\n", path.c_str());
		return false;
	}
	out.close();
	EFileType ft = getFileType(path);
	if (ft == UNDEF) {
		printf("Couldn't open file \"%s\". File type is not supported by the engine!\n", path.c_str());
		return false;
	}
	if (ft != MODEL) {
		printf("Couldn't open file \"%s\". File is not a model!\n", path.c_str());
		return false;
	}
	EResourceType ert = getResourceType(path);
	switch (ert) {
	case OIRM:
		if (r->getType() != MESH) {
			printf("Couldn't open file \"%s\". File is not a static mesh (or requires materials) and can't be used for export to oiRM!\n", path.c_str());
			return false;
		}
		oiRM::write(path, (Mesh*)r);
		return true;
	default:
		printf("Couldn't open file \"%s\". File writing for file is not yet implemented!\n", path.c_str());
		return false;
	}
}
bool ResourcePile::writeTexture(std::string path, std::string name){
	bool contains = false;
	Texture *t = nullptr;
	for (u32 i = 0; i < textures.size(); i++)
		if (StringHelper::equalsIgnoreCase(name, textures[i]->getName())) {
			contains = true;
			t = textures[i]->getResource();
			break;
		}

	if (!contains) {
		printf("Couldn't write to \"%s\". There was no such object to write with name \"%s\"\n", path.c_str(), name.c_str());
		return false;
	}

	std::ofstream out(path, std::ios::out);
	if (!out.good()) {
		out.close();
		printf("Couldn't open file \"%s\"\n", path.c_str());
		return false;
	}
	out.close();
	EFileType ft = getFileType(path);
	if (ft == UNDEF) {
		printf("Couldn't open file \"%s\". File type is not supported by the engine!\n", path.c_str());
		return false;
	}
	if (ft != TEXTURE) {
		printf("Couldn't open file \"%s\". File is not a texture!\n", path.c_str());
		return false;
	}
	EResourceType ert = getResourceType(path);
	switch (ert) {
	case PNG:
		return t->writePNG(path);
	default:
		printf("Couldn't open file \"%s\". File writing for file is not yet implemented!\n", path.c_str());
		return false;
	}
}


void ResourcePile::printTextures(){
	for (u32 i = 0; i < textures.size(); ++i)
		printf("%s (path: %s, oid: %u, oglid: %u)\n", textures[i]->getName().c_str(), textures[i]->getPath().c_str(), i, textures[i]->getResource()->getId());
}

void ResourcePile::printModels(){
	for (u32 i = 0; i < renderers.size(); ++i) {
		printf("%s (path: %s, oid: %u, render type: %u), AABB: ", renderers[i]->getName().c_str(), renderers[i]->getPath().c_str(), i, renderers[i]->getResource()->getType());
		renderers[i]->getResource()->getAABB().print();
	}
}

void ResourcePile::printShaders(){
	for (u32 i = 0; i < shaders.size(); ++i)
		printf("%s (path: %s, oid: %u, oglid: %u, type: %u)\n", shaders[i]->getName().c_str(), shaders[i]->getPath().c_str(), i, shaders[i]->getResource()->id, shaders[i]->getResource()->getType());
}

void ResourcePile::printLines(){
	for (u32 i = 0; i < lines.size(); ++i)
		printf("%s (oid: %u)\n", lines[i]->getName().c_str(), i);
}

void ResourcePile::printWireframes(){
	for (u32 i = 0; i < wires.size(); ++i)
		printf("%s (oid: %u, lineCount: %u)\n", wires[i]->getName().c_str(), i, wires[i]->getResource()->size());
}

void ResourcePile::printAll(){
	printf("Textures:\n---------------------------\n");
	printTextures();
	printf("---------------------------\n");
	printf("Models:\n---------------------------\n");
	printModels();
	printf("---------------------------\n");
	printf("Shaders:\n---------------------------\n");
	printShaders();
	printf("---------------------------\n");
	printf("Lines:\n---------------------------\n");
	printLines();
	printf("---------------------------\n");
	printf("Wireframes:\n---------------------------\n");
	printWireframes();
	printf("---------------------------\n");
}