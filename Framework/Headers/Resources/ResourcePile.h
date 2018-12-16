#pragma once
#include "Textures/Texture.h"
#include "../Render/Renderer.h"
#include "../Render/Line/LineRenderer.h"
#include "../Render/Line/Wireframe.h"
#include "ResourceObject.h"
#include "ResourceType.h"
#include <vector>
#include <string>
namespace lun {
	class ResourcePile {

		friend class MeshHelper;

	private:

		std::vector<ResourceObject<Texture>*> textures;
		std::vector<ResourceObject<Renderer>*> renderers;
		std::vector<ResourceObject<Shader>*> shaders;
		std::vector<ResourceObject<LineRenderer>*> lines;
		std::vector<ResourceObject<Wireframe>*> wires;

	protected:

		///(Runtime mesh)
		void addRenderer(Renderer *ro, std::string name);

	public:

		ResourcePile();
		~ResourcePile();

		EResourceType getResourceType(std::string path);
		EFileType getFileType(std::string path);

		Renderer *loadModel(std::string path, std::string name, Shader *s);
		Texture *loadTexture(std::string path, std::string name);
		Shader *loadShader(std::string path, std::string name);
		LineRenderer *loadLine(std::vector<Node> nodes, std::string name);
		Wireframe *loadWireframe(Wireframe wire, std::string name);

		bool hasTexture(std::string name);
		bool hasModel(std::string name);
		bool hasShader(std::string name);
		bool hasLine(std::string name);
		bool hasWireframe(std::string name);

		Texture *fetchTexture(std::string name);
		Renderer *fetchModel(std::string name);
		Shader *fetchShader(std::string name);
		LineRenderer *fetchLine(std::string name);
		Wireframe *fetchWireframe(std::string name);

		bool unloadTexture(std::string name);
		bool unloadModel(std::string name);
		bool unloadShader(std::string name);
		bool unloadLine(std::string name);
		bool unloadWireframe(std::string name);

		void printTextures();
		void printModels();
		void printShaders();
		void printLines();
		void printWireframes();
		void printAll();

		bool writeModel(std::string newPath, std::string name);
		bool writeTexture(std::string newPath, std::string name);
		//bool writeLine(std::string newPath, std::string name);		//TODO:
		//bool writeWireframe(std::string newPath, std::string name);	//TODO:
	};
}