#include "../../Headers/Helper/OGLHelper.h"
using namespace lun;

//Enums to GLenum

GLenum OGLHelper::getDrawType(EDrawType drawType) {
	switch (drawType) {
	case STREAM_READ:
		return GL_STREAM_READ;
	case STREAM_DRAW:
		return GL_STREAM_DRAW;
	case STREAM_COPY:
		return GL_STREAM_COPY;
	case STATIC_READ:
		return GL_STATIC_DRAW;
	case STATIC_DRAW:
		return GL_STATIC_DRAW;
	case STATIC_COPY:
		return GL_STATIC_COPY;
	case DYNAMIC_READ:
		return GL_DYNAMIC_DRAW;
	case DYNAMIC_DRAW:
		return GL_DYNAMIC_DRAW;
	case DYNAMIC_COPY:
		return GL_DYNAMIC_COPY;
	}
	return GL_STATIC_DRAW;
}

GLenum OGLHelper::getTextureTarget(ETextureType textureType) {
	switch (textureType) {
	case TEXTURE_1D:
		return GL_TEXTURE_1D;
	case TEXTURE_2D:
		return GL_TEXTURE_2D;
	case TEXTURE_3D:
		return GL_TEXTURE_3D;
	case TEXTURE_1D_ARRAY:
		return GL_TEXTURE_1D_ARRAY;
	case TEXTURE_2D_ARRAY:
		return GL_TEXTURE_2D_ARRAY;
	case TEXTURE_RECTANGLE:
		return GL_TEXTURE_RECTANGLE;
	case TEXTURE_CUBE_MAP:
		return GL_TEXTURE_CUBE_MAP;
	case TEXTURE_CUBE_MAP_ARRAY:
		return GL_TEXTURE_CUBE_MAP_ARRAY;
	case TEXTURE_BUFFER:
		return GL_TEXTURE_BUFFER;
	case TEXTURE_2D_MULTISAMPLE:
		return GL_TEXTURE_2D_MULTISAMPLE;
	case TEXTURE_2D_MULTISAMPLE_ARRAY:
		return GL_TEXTURE_2D_MULTISAMPLE_ARRAY;
	}
	return GL_TEXTURE_2D;
}

GLenum OGLHelper::getTextureFormat(ETextureFormat textureFormat) {
	switch (textureFormat) {
		//R/RG/RGB/RGBA 8/16 (_SNORM)
		case R8:
			return GL_R8;
		case R8_SNORM:
			return GL_R8_SNORM;
		case RG8:
			return GL_RG8;
		case RG8_SNORM:
			return GL_RG8_SNORM;
		case RGB8:
			return GL_RGB8;
		case RGB8_SNORM:
			return GL_RGB8_SNORM;
		case RGBA8:
			return GL_RGBA8;
		case RGBA8_SNORM:
			return GL_RGBA8_SNORM;

		case R16:
			return GL_R16;
		case R16_SNORM:
			return GL_R16_SNORM;
		case RG16:
			return GL_RG16;
		case RG16_SNORM:
			return GL_RG16_SNORM;
		case RGB16:
			return GL_RGB16;
		case RGB16_SNORM:
			return GL_RGB16_SNORM;
		case RGBA16:
			return GL_RGBA16;
		case RGBA16_SNORM:
			return GL_RGBA16_SNORM;

		//R/RG/RGB/RGBA 8/16/32 U/UI
		case R8I:
			return GL_R8I;
		case R8UI:
			return GL_R8UI;
		case R16I:
			return GL_R16I;
		case R16UI:
			return GL_R16UI;
		case R32I:
			return GL_R32I;
		case R32UI:
			return GL_R32UI;

		case RG8I:
			return GL_RG8I;
		case RG8UI:
			return GL_RG8UI;
		case RG16I:
			return GL_RG16I;
		case RG16UI:
			return GL_RG16UI;
		case RG32I:
			return GL_RG32I;
		case RG32UI:
			return GL_RG32UI;

		case RGB8I:
			return GL_RGB8I;
		case RGB8UI:
			return GL_RGB8UI;
		case RGB16I:
			return GL_RGB16I;
		case RGB16UI:
			return GL_RGB16UI;
		case RGB32I:
			return GL_RGB32I;
		case RGB32UI:
			return GL_RGB32UI;

		case RGBA8I:
			return GL_RGBA8I;
		case RGBA8UI:
			return GL_RGBA8UI;
		case RGBA16I:
			return GL_RGBA16I;
		case RGBA16UI:
			return GL_RGBA16UI;
		case RGBA32I:
			return GL_RGBA32I;
		case RGBA32UI:
			return GL_RGBA32UI;

		//Irregular bit count texture formats
		case RGB4:
			return GL_RGB4;
		case RGB5:
			return GL_RGB5;
		case RGB10:
			return GL_RGB10;
		case RGB12:
			return GL_RGB12;
		case RGBA2:
			return GL_RGBA2;
		case RGBA4:
			return GL_RGBA4;
		case RGBA12:
			return GL_RGBA12;

		//Irregular texture formats
		case R3_G3_B2:
			return GL_R3_G3_B2;
		case R11F_G11F_B10F:
			return GL_R11F_G11F_B10F;
		case RGB5_A1:
			return GL_RGB5_A1;
		case RGB10_A2:
			return GL_RGB10_A2;
		case RGB10_A2UI:
			return GL_RGB10_A2UI;
		case RGB9_E5:
			return GL_RGB9_E5;

		//R/RG/RGB/RGBA 16F/32F
		case R16F:
			return GL_R16F;
		case RG16F:
			return GL_RG16F;
		case RGB16F:
			return GL_RGB16F;
		case RGBA16F:
			return GL_RGBA16F;

		case R32F:
			return GL_R32F;
		case RG32F:
			return GL_RG32F;
		case RGB32F:
			return GL_RGB32F;
		case RGBA32F:
			return GL_RGBA32F;

		//sRGB
		case SRGB8:
			return GL_SRGB8;
		case SRGB8_ALPHA8:
			return GL_SRGB8_ALPHA8;
	}
	return GL_RGBA8;
}

GLenum OGLHelper::getDepthType(EDepthType depthType) {
	switch (depthType) {
	case LESS:
		return GL_LESS;
	case GREATER:
		return GL_GREATER;
	case EQUAL:
		return GL_EQUAL;
	case NOT_EQUAL:
		return GL_NOTEQUAL;
	case NEVER:
		return GL_NEVER;
	case LEQUAL:
		return GL_LEQUAL;
	case GEQUAL:
		return GL_GEQUAL;
	}
	return LESS;
}

//Create GL object
GLuint OGLHelper::createVBO(GLubyte *data, u32 bufferLength, EDrawType drawType) {
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, bufferLength, data, getDrawType(drawType));
	if (shoutAny("VBO: "))
		return 0;
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return vbo;
}

GLuint OGLHelper::createSSBO(GLubyte *data, u32 bufferLength, EDrawType drawType) {
	GLuint ssbo;
	glGenBuffers(1, &ssbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
	glBufferData(GL_SHADER_STORAGE_BUFFER, bufferLength, data, getDrawType(drawType));
	if (shoutAny("SSBO: "))
		return 0;
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	return ssbo;
}

GLuint OGLHelper::createIBO(GLubyte *data, u32 bufferLength) {
	GLuint ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferLength, data, GL_STATIC_DRAW);
	if (shoutAny("IBO: ")) 
		return 0;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	return ibo;
}

GLuint OGLHelper::createDefaultVAO(GLuint vbo, GLuint ibo) {
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	GLuint v1 = sizeof(GLfloat) * 3;
	GLuint v2 = sizeof(GLfloat) * 5;
	GLuint stride = sizeof(GLfloat) * 8;


	GLchar *ptr = (GLchar*)0;
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, ptr);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, ptr + v1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, ptr + v2);

	if (shoutAny("VAO: ")) 
		return 0;

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return vao;
}

GLuint OGLHelper::createPositionVAO(GLuint vbo) {
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	GLuint v1 = sizeof(GLfloat) * 3;

	GLchar *ptr = (GLchar*)0;

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, v1, ptr);

	if (shoutAny("VAO: "))
		return 0;

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return vao;
}

GLuint OGLHelper::createFBO() {
	GLuint fbo;
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	if (shoutAny("FBO: "))
		return 0;
	return fbo;
}

GLuint OGLHelper::createTexture(u32 width, u32 height, bool linearFiltering) {
	GLuint t;
	glGenTextures(1, &t);
	glBindTexture(GL_TEXTURE_2D, t);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, linearFiltering ? GL_LINEAR : GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, linearFiltering ? GL_LINEAR : GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	if (shoutAny("Texture: "))
		return 0;

	return t;
}

GLuint OGLHelper::createDepthTexture(u32 width, u32 height, bool linearFiltering) {
	GLuint t;
	glGenTextures(1, &t);
	glBindTexture(GL_TEXTURE_2D, t);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, linearFiltering ? GL_LINEAR : GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, linearFiltering ? GL_LINEAR : GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	if (shoutAny("Depth texture: "))
		return 0;

	return t;
}

GLuint OGLHelper::createDepthBuffer(u32 width, u32 height) {
	GLuint RBO;
	glGenRenderbuffers(1, &RBO);
	glBindRenderbuffer(GL_RENDERBUFFER, RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, width, height);

	if (shoutAny("RBO: "))
		return 0;

	return RBO;
}

//Destroy GL object

bool OGLHelper::destroyVBO(GLuint vbo){
	if (vbo == 0)return false;
	glDeleteBuffers(1, &vbo);
	if (shoutAny("delete VBO: "))
		return 0;
	return true;
}

bool OGLHelper::destroySSBO(GLuint ssbo) {
	if (ssbo == 0)return false;
	glDeleteBuffers(1, &ssbo);
	if (shoutAny("delete SSBO: "))
		return 0;
	return true;
}

bool OGLHelper::destroyVAO(GLuint vao){
	if (vao == 0)return false;
	glDeleteVertexArrays(1, &vao);
	if (shoutAny("delete VAO: "))
		return 0;
	return true;
}

bool OGLHelper::destroyIBO(GLuint ibo){
	if (ibo == 0)return false;
	glDeleteBuffers(1, &ibo);
	if (shoutAny("delete IBO: "))
		return 0;
	return true;
}

bool OGLHelper::destroyFBO(GLuint fbo) {
	if (fbo == 0)return false;
	glDeleteFramebuffers(1, &fbo);
	if (shoutAny("delete FBO: "))
		return 0;
	return true;
}

bool OGLHelper::destroyTexture(GLuint texture) {
	if (texture == 0)return false;
	glDeleteTextures(1, &texture);
	if (shoutAny("delete texture: "))
		return 0;
	return true;
}

bool OGLHelper::destroyRBO(GLuint rbo) {
	if (rbo == 0)return false;
	glDeleteRenderbuffers(1, &rbo);
	if (shoutAny("delete RBO: "))
		return 0;
	return true;
}

bool OGLHelper::destroyShader(GLuint shader) {
	if (shader == 0)return false;
	glDeleteShader(shader);
	if (shoutAny("delete Shader: "))
		return 0;
	return true;
}

//Bind GL objects

void OGLHelper::bindVBO(GLuint vbo) {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void OGLHelper::bindSSBO(GLuint ssbo, u32 binding) {
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, binding, ssbo);
}

void OGLHelper::bindVAO(GLuint vao) {
	glBindVertexArray(vao);
}

void OGLHelper::bindFBO(GLuint fbo) {
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void OGLHelper::bindRBO(GLuint rbo) {
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
}

void OGLHelper::bindIBO(GLuint ibo) {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
}

void OGLHelper::bindTexture(GLuint texture) {
	bindTexture(TEXTURE_2D, texture);
}

void OGLHelper::bindTexture(ETextureType target, GLuint texture) {
	glBindTexture(getTextureTarget(target), texture);
}

void OGLHelper::bindTexture(ETextureInput targetId, ETextureType target, GLuint texture) {
	glActiveTexture(GL_TEXTURE0 + targetId);
	bindTexture(target, texture);
}

void OGLHelper::bindWriteTexture(u8 offset, GLuint texture, ETextureFormat textureFormat) {
	glBindImageTexture(offset, texture, 0, GL_FALSE, 0, GL_WRITE_ONLY, getTextureFormat(textureFormat));
}

//Draw calls

void OGLHelper::drawElements(u32 indices, u32 perIndex) {
	GLenum e = perIndex == 1 ? GL_UNSIGNED_BYTE : (perIndex == 2 ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT);
	glDrawElements(GL_TRIANGLES, indices, e, 0);
}

void OGLHelper::drawLines(u32 length) {
	glDrawArrays(GL_LINES, 0, length);
}

void OGLHelper::setLineSize(f32 lineSize) {
	glLineWidth(lineSize);
}

void OGLHelper::drawElementsInstanced(u32 indices, u32 perIndex, u32 amount) {
	GLenum e = perIndex == 1 ? GL_UNSIGNED_BYTE : (perIndex == 2 ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT);
	glDrawElementsInstanced(GL_TRIANGLES, indices, e, 0, amount);
}

//FBO related

void OGLHelper::attachDepthBuffer(GLuint fbo, GLuint depth) {
	bindFBO(fbo);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth);
}
void OGLHelper::attachment(GLuint fbo, u32 id, GLuint texture) {
	bindFBO(fbo);
	glFramebufferTexture(GL_FRAMEBUFFER, id == DEPTH_TEXTURE ? GL_DEPTH_ATTACHMENT : GL_COLOR_ATTACHMENT0 + id, texture, 0);
}

void OGLHelper::attachments(GLuint fbo, u32 *attachmentArray, u32 attachments) {
	bindFBO(fbo);
	GLenum *draw = new GLenum[attachments];
	for (u32 i = 0; i < attachments; i++) draw[i] = attachmentArray[i] + GL_COLOR_ATTACHMENT0;
	glDrawBuffers(attachments, draw);
	delete[] draw;
}

//Error handling

bool OGLHelper::shoutAny(std::string prefix) {
	#ifdef __DEBUG__
	GLenum ge = glGetError();
	if (ge == GL_NO_ERROR)return false;
	switch (ge) {
	case GL_INVALID_ENUM:
		printf("%s: Invalid enum!\n", prefix.c_str());
		break;
	case GL_INVALID_VALUE:
		printf("%s: Invalid value!\n", prefix.c_str());
		break;
	case GL_INVALID_OPERATION:
		printf("%s: Invalid operation!\n", prefix.c_str());
		break;
	case GL_STACK_OVERFLOW:
		printf("%s: Stack overflow!\n", prefix.c_str());
		break;
	case GL_OUT_OF_MEMORY:
		printf("%s: Out of memory!\n", prefix.c_str());
		break;
	case GL_TABLE_TOO_LARGE:
		printf("%s: Table to large!\n", prefix.c_str());
		break;
	default:
		printf("%s: Unknown error! (%u)\n", prefix.c_str(), ge);
		break;
	}
	return true;
	#endif
	return false;
}

bool OGLHelper::checkFBO(GLuint fbo) {
	#ifdef __DEBUG__
	GLenum err = GL_FRAMEBUFFER_COMPLETE;
	if ((err = glCheckFramebufferStatus(GL_FRAMEBUFFER)) != GL_FRAMEBUFFER_COMPLETE) {
		switch (err) {
		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
			printf("Framebuffer: Incomplete attachment!\n");
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
			printf("Framebuffer: Missing attachment!\n");
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
			printf("Framebuffer: Incomplete draw buffer!\n");
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
			printf("Framebuffer: Incomplete read buffer!\n");
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
			printf("Framebuffer: Incomplete dimensions!\n");
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
			printf("Framebuffer: Incomplete formats!\n");
			break;
		case GL_FRAMEBUFFER_UNSUPPORTED:
			printf("Framebuffer: Not supported!\n");
			break;
		default:
			printf("Framebuffer: Unknown failure!\n");
			break;
		}
		if (err == GL_INVALID_ENUM)printf("Framebuffer: Invalid enum!\n");
		shoutAny("Framebuffer: ");
		return false;
	}
	#endif
	return true;
}

//GL settings (depth & culling & clear color)

void OGLHelper::depthWrite(bool turnedOn) {
	glDepthMask((GLboolean)turnedOn);
}

void OGLHelper::depthTest(bool turnedOn) {
	if(turnedOn)
		glEnable(GL_DEPTH_TEST);
	else 
		glDisable(GL_DEPTH_TEST);
}

void OGLHelper::depth() {
	depthWrite(true);
	depthTest(true);
}

void OGLHelper::noDepth() {
	depthWrite(false);
	depthTest(false);
}

void OGLHelper::setCulling(bool turnedOn) {
	if (turnedOn)
		glEnable(GL_CULL_FACE);
	else 
		glDisable(GL_CULL_FACE);
}

void OGLHelper::clearColor(RGBA color) {
	glClearColor(color.x, color.y, color.z, color.w);
}

void OGLHelper::depthFunc(EDepthType depthType) {
	glDepthFunc(getDepthType(depthType));
}

void OGLHelper::alphaBlend() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void OGLHelper::noBlend() {
	glDisable(GL_BLEND);
}

//Copying buffers

void OGLHelper::copyVBO(GLuint vbo, u32 bufferLength, char *outputBuffer) {
	bindVBO(vbo);
	glGetBufferSubData(GL_ARRAY_BUFFER, 0, bufferLength, outputBuffer);
	bindVBO(0);
}

void OGLHelper::copyIBO(GLuint ibo, u32 bufferLength, char *outputBuffer) {
	bindIBO(ibo);
	glGetBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, bufferLength, outputBuffer);
	bindIBO(0);
}

void OGLHelper::copyDepth(GLuint source, GLuint target, u32 width, u32 height) {
	glBindFramebuffer(GL_FRAMEBUFFER, source);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, source);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, target);
	glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

//Clearing buffers

void OGLHelper::clearFBO() {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}
void OGLHelper::clearDepth() {
	glClear(GL_DEPTH_BUFFER_BIT);
}
void OGLHelper::clearColor() {
	glClear(GL_COLOR_BUFFER_BIT);
}


//Update buffers

void OGLHelper::updateVBO(GLuint vbo, u32 offset, u32 length, GLubyte *data) {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, offset, length, data);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void OGLHelper::updateSSBO(GLuint ssbo, u32 offset, u32 length, GLubyte *data) {
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
	glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, length, data);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

//Shader

void OGLHelper::dispatchCompute(u32 width, u32 height, u32 length) { glDispatchCompute(width, height, length); }
void OGLHelper::useShader(GLuint shader) { glUseProgram(shader); }