#pragma once
#include "../../Helper/OGLHelper.h"
namespace lun {
	class Texture {
		template<class T> friend class ResourceObject;
		friend class ResourcePile;

	public:

		//Bind this texture to target with texId as id.
		void bind(ETextureType target, ETextureInput texId = TEXTURE00);

		//Unbind this texture from texId.
		void unbind(ETextureType target, ETextureInput texId = TEXTURE00);

	protected:

		//Create texture
		Texture(GLuint i, int w, int h, int comp);

		//Get id
		GLuint getId();

		//Destroy texture
		~Texture();

		//Load texture from file
		static Texture *load(std::string path);

		//Write texture to PNG
		bool writePNG(std::string path);

	private:

		GLuint id;
		int w, h, comp;
	};
}