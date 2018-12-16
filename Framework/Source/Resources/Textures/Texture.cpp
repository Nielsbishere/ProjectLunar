#include "../../../Headers/Resources/Textures/Texture.h"
#include "../../../Headers/Helper/OGLHelper.h"

#include "../../../Headers/Math/Math.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../../../Headers/API/stbi/load.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../../../Headers/API/stbi/write.h"

using namespace lun;

Texture::Texture(GLuint i, int _w, int _h, int _comp) : id(i), w(_w), h(_h), comp(_comp) {}

Texture::~Texture() {
	glDeleteTextures(1, &id);
}

GLuint Texture::getId(){ return id; }

void Texture::bind(ETextureType target, ETextureInput texId) {
	OGLHelper::bindTexture(texId, target, id);
}

void Texture::unbind(ETextureType target, ETextureInput texId) {
	OGLHelper::bindTexture(texId, target, 0);
}

Texture *Texture::load(std::string path) {
	int w, h, comp;
	u8 *dat = stbi_load(path.c_str(), &w, &h, &comp, 4);
	if (dat == nullptr) {
		printf("Failed to load texture \"%s\"\n", path.c_str());
		return nullptr;
	}

	//Switch RGBA image to match BGRA (more efficient)
	for (u32 i = 0; i < (u32)(w * h); ++i) {
		u8 *c = dat + i * 4;
		u8 r = c[0];
		c[0] = c[2];
		c[2] = r;
	}

	GLuint id;
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA_DXT5_S3TC, w, h, 0, GL_BGRA, GL_UNSIGNED_BYTE, dat);
	if (OGLHelper::shoutAny("Texture loading: ")) {
		stbi_image_free(dat);
		glDeleteTextures(1, &id);
		printf("Failed to load texture \"%s\".\n", path.c_str());
		return nullptr;
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	f32 ani = 0;
	#ifdef GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &ani);

	if (ani > 1)
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, ani);
	#endif

	if (OGLHelper::shoutAny("Texture loading: ")) {
		stbi_image_free(dat);
		glDeleteTextures(1, &id);
		printf("Failed to load texture \"%s\"\n", path.c_str());
		return nullptr;
	}

	stbi_image_free(dat);

	Texture *t = new Texture(id, w, h, comp);
	t->unbind(TEXTURE_2D);

	return t;
}
bool Texture::writePNG(std::string path) {
	glGetTextureLevelParameteriv(id, 0, GL_TEXTURE_WIDTH, &w);
	glGetTextureLevelParameteriv(id, 0, GL_TEXTURE_HEIGHT, &h);
	char *dat = new char[4 * w * h];
	bind(TEXTURE_2D);
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, dat);
	stbi_write_png(path.c_str(), w, h, 4, dat, 4 * w);
	delete[] dat;
	return true;
}