#pragma once
#include "../Type/OTypes.h"
#include "../CrossPlatform/CrossPlatform.h"
#include <string>
#define DEPTH_TEXTURE 420
namespace lun {
	//Argument used for creating buffers;
	//Stream, static & dynamic:
	//	Streaming = content will be modified once and used at most a few times
	//	Static = content will be modified once and used many times
	//	Dynamic = content will be modified repeatedly and used many times
	//	Static is used for normal buffers, dynamic is used for changing buffers (ex. particle buffer, etc.) and streaming isn't used very often
	//Draw, read & copy:
	//	Draw = content will be modified by the application and used as source for GL drawing
	//	Read = content is modified by reading data from the GL and used to return data when queried by the application
	//	Copy = content is modified by reading data from the GL and used as source for GL drawing
	//	Draw is used for regular bufffers, read and copy don't appear frequently and are just used for specific buffers
	enum EDrawType {
		STREAM_DRAW, 
		STREAM_READ, 
		STREAM_COPY,

		STATIC_DRAW, 
		STATIC_READ, 
		STATIC_COPY,

		DYNAMIC_DRAW, 
		DYNAMIC_READ, 
		DYNAMIC_COPY
	};

	//Argument for binding textures
	//Can bind TEXTURE00 -> TEXTURE31 to a shader
	//	Be careful; not all hardware supports the same amount of textures. So try to only use 00->07 to be safe.
	enum ETextureInput {
		TEXTURE00 = 0, TEXTURE01, TEXTURE02, TEXTURE03, TEXTURE04, TEXTURE05, TEXTURE06, TEXTURE07, 
		TEXTURE08, TEXTURE09, TEXTURE10, TEXTURE11, TEXTURE12, TEXTURE13, TEXTURE14, TEXTURE15,
		TEXTURE16, TEXTURE17, TEXTURE18, TEXTURE19, TEXTURE20, TEXTURE21, TEXTURE22, TEXTURE23, 
		TEXTURE24, TEXTURE25, TEXTURE26, TEXTURE27, TEXTURE28, TEXTURE29, TEXTURE30, TEXTURE31
	};

	//The texture types
	//1D is for x textures (line)
	//2D is for xy textures
	//3D is for xyz textures (2D + depth)
	//Rectangle	is for shadowmaps, but depth texture can handle that too
	//Cubemap is for textures that act like cubes (used in skyboxes and reflection)
	//Buffer is for storing data rather than storing pixel colors
	//2D MS is for hq textures that can be converted into smooth 2D textures
	//The following support arrays: (_ARRAY)
	//	1D
	//	2D
	//	Cubemap
	//	2D multisample
	enum ETextureType {
		TEXTURE_1D, 
		TEXTURE_2D, 
		TEXTURE_3D, 
		
		TEXTURE_1D_ARRAY, 
		TEXTURE_2D_ARRAY, 
		
		TEXTURE_RECTANGLE, 
		
		TEXTURE_CUBE_MAP, 
		TEXTURE_CUBE_MAP_ARRAY,

		TEXTURE_BUFFER,

		TEXTURE_2D_MULTISAMPLE,
		TEXTURE_2D_MULTISAMPLE_ARRAY
	};

	//Internal texture format
	//For info on texture formats, check OpenGL
	enum ETextureFormat {
		R8, R8_SNORM,
		RG8, RG8_SNORM,
		RGB8, RGB8_SNORM,
		RGBA8, RGBA8_SNORM,

		R16, R16_SNORM,
		RG16, RG16_SNORM,
		RGB16, RGB16_SNORM,
		RGBA16, RGBA16_SNORM,

		RGB4, RGB5, RGB10, RGB12,
		RGBA2, RGBA4, RGBA12, RGB5_A1, RGB10_A2, RGB10_A2UI,
		R3_G3_B2, 

		SRGB8, SRGB8_ALPHA8,

		R16F, RG16F, RGB16F, RGBA16F,
		R32F, RG32F, RGB32F, RGBA32F,

		R11F_G11F_B10F, RGB9_E5,

		R8I, R8UI, R16I, R16UI, R32I, R32UI,
		RG8I, RG8UI, RG16I, RG16UI, RG32I, RG32UI,
		RGB8I, RGB8UI, RGB16I, RGB16UI, RGB32I, RGB32UI,
		RGBA8I, RGBA8UI, RGBA16I, RGBA16UI, RGBA32I, RGBA32UI
	};

	//Type of depth;
	//Default value is LESS
	enum EDepthType {
		LESS, NEVER, GREATER, EQUAL, NOT_EQUAL, LEQUAL, GEQUAL
	};

	//A wrapper around GLs like OpenGL and D3D
	class OGLHelper {
	public:
		//Sends the vertex data to the GPU
		//@param GLubyte *data
		//@param u32 buffer length
		//@optional GLenum drawType; default:	GL_STATIC_DRAW
		//@return GLuint bufferId
		static GLuint createVBO(GLubyte *data, u32 bufferLength, EDrawType drawType = STATIC_DRAW);

		//Sends the shader data of the GPU
		//Used as shader storage buffer object
		//@return GLuint bufferId
		static GLuint createSSBO(GLubyte *data, u32 bufferLength, EDrawType drawType = STATIC_DRAW);

		//Sends the index data to the GPU
		//@return GLuint bufferId
		static GLuint createIBO(GLubyte *data, u32 bufferLength);

		//Creates the default VAO
		//vec3 position, vec2 uv, vec3 normal
		//@return GLuint vaoId
		static GLuint createDefaultVAO(GLuint vbo, GLuint ibo);

		//Creates the position VAO (mainly used for line rendering)
		//vec3 position
		//@return GLuint vaoId
		static GLuint createPositionVAO(GLuint vbo);

		//Creates an empty FBO
		//@return GLuint fbo
		static GLuint createFBO();

		//Creates a texture with specified width and height
		//@param u32 width
		//@param u32 height
		//@optional bool uses linear filtering;	default: false
		//@return GLuint texture id
		static GLuint createTexture(u32 width, u32 height, bool linearFiltering = false);

		//Creates a depth texture with specified width and height
		//@param u32 width
		//@param u32 height
		//@optional bool uses linear filtering;	default: false
		//@return GLuint texture id
		static GLuint createDepthTexture(u32 width, u32 height, bool linearFiltering = false);

		//Creates a render buffer with specified width and height
		//@param u32 width
		//@param u32 height
		//@return GLuint render buffer id
		static GLuint createDepthBuffer(u32 width, u32 height);


		//Destroy a VBO
		//@param GLuint vbo
		//@return true if completed without errors
		static bool destroyVBO(GLuint vbo);

		//Destroy a SSBO
		//@param GLuint ssbo
		//@return true if completed without errors
		static bool destroySSBO(GLuint ssbo);

		//Destroy a VAO
		//@param GLuint vao
		//@return true if completed without errors
		static bool destroyVAO(GLuint vao);

		//Destroy an IBO
		//@param GLuint ibo
		//@return true if completed without errors
		static bool destroyIBO(GLuint ibo);

		//Destroy a FBO
		//@param GLuint fbo
		//@return true if completed without errors
		static bool destroyFBO(GLuint fbo);

		//Destroy a texture
		//@param GLuint texture
		//@return true if completed without errors
		static bool destroyTexture(GLuint texture);

		//Destroy a render buffer
		//@param GLuint rbo
		//@return true if completed without errors
		static bool destroyRBO(GLuint rbo);

		//Destroy a shader
		//@param GLuint shader
		//@return true if completed
		static bool destroyShader(GLuint shader);


		//Bind a VBO
		//@param GLuint vbo
		static void bindVBO(GLuint vbo);

		//Bind a SSBO
		//@param GLuint ssbo
		static void bindSSBO(GLuint ssbo, u32 binding);

		//Bind a VAO
		//@param GLuint vao
		static void bindVAO(GLuint vao);

		//Bind an IBO
		//@param GLuint ibo
		static void bindIBO(GLuint ibo);

		//Bind a texture
		//@param GLuint texture
		static void bindTexture(GLuint texture);

		//Bind a texture
		//@param ETextureType target;	which target to bind to (bindTexture(GLuint id) uses TEXTURE_2D)
		//@param GLuint texture
		static void bindTexture(ETextureType target, GLuint texture);

		//Bind a texture
		//@param ETextureInput targetId;	which target id to bind to (texture input 0,1,2,...,31)
		//@param ETextureType target;	which target to bind to (bindTexture(GLuint id) uses TEXTURE_2D)
		//@param GLuint vbo
		static void bindTexture(ETextureInput targetId, ETextureType target, GLuint texture);

		//Bind a FBO
		//@param GLuint fbo
		static void bindFBO(GLuint fbo);

		//Bind a render buffer
		//@param GLuint rbo
		static void bindRBO(GLuint rbo);

		//Bind a 'write texture' aka writeable image2D
		//@param u8 offset	(texture offset)
		//@param GLuint texture
		//@optional ETextureFormat textureFormat; GL_RGBA8 by default
		static void bindWriteTexture(u8 offset, GLuint texture, ETextureFormat textureFormat = RGBA8);


		//Draw call
		//@param u32 indices;	number of indices to draw
		//@param u32 perIndex;	number of bytes per index
		static void drawElements(u32 indices, u32 perIndex);

		//Draw call (instanced)
		//@param u32 indices;	number of indices to draw
		//@param u32 perIndex;	number of bytes per index
		//@param u32 amount;	number of instanced elements to draw
		static void drawElementsInstanced(u32 indices, u32 perIndex, u32 amount);

		//Draw lines
		//@param u32 pointCount
		static void drawLines(u32 pointCount);

		//Set line size
		//@param f32 lineSize
		static void setLineSize(f32 lineSize);


		//Attach render buffer to FBO
		//@param GLuint fbo
		//@param GLuint rbo
		//@binds fbo
		static void attachDepthBuffer(GLuint fbo, GLuint depth);

		//Attach a texture output to FBO
		//@param GLuint fbo
		//@param u32 attachment id;		when id = DEPTH_TEXTURE it will be used as the depth texture
		//@param GLuint texture
		//@binds fbo
		static void attachment(GLuint fbo, u32 id, GLuint texture);

		//Attaches x attachments to the FBO (excluding depth texture/buffer)
		//@param GLuint fbo
		//@param u32 attachmentArray[]
		//@param u32 attachments
		//@binds fbo
		static void attachments(GLuint fbo, u32 *attachmentArray, u32 attachments);


		//Turn on/off depth write
		//@param bool turnedOn
		static void depthWrite(bool turnedOn);

		//Turn on/off depth testing
		//@param bool turnedOn
		static void depthTest(bool turnedOn);

		//Turn off depth write & test
		static void noDepth();

		//Turn on depth write & test
		static void depth();

		//Turn on/off culling
		//@param bool turnedOn
		static void setCulling(bool turnedOn);

		//Set the clear color
		//@param RGBA color
		//@warning; color != RGBA() will result in problems with deferred rendering
		static void clearColor(RGBA color);

		//Set the depth function
		//@optional EDepthType depthType; default = LESS
		static void depthFunc(EDepthType depthType = LESS);

		//Set the blending to alpha blend
		static void alphaBlend();

		//Turn off the blending
		static void noBlend();


		//Copy the vbo into the output buffer
		//@param GLuint vbo
		//@param u32 bufferLength
		//@param char outputBuffer[bufferLength]
		static void copyVBO(GLuint vbo, u32 bufferLength, char *outputBuffer);

		//Copy the ibo into the output buffer
		//@param GLuint ibo
		//@param u32 bufferLength
		//@param char outputBuffer[bufferLength]
		static void copyIBO(GLuint ibo, u32 bufferLength, char *outputBuffer);

		//Copy the depth buffer from the source FBO to the target FBO
		//@param GLuint source
		//@param GLuint target
		//@param u32 width
		//@param u32 height
		static void copyDepth(GLuint source, GLuint target, u32 width, u32 height);


		//Clear the bound FBO (depth & color)
		static void clearFBO();

		//Clear the bound FBO's depth
		static void clearDepth();

		//Clear the bound FBO's color
		static void clearColor();


		//Use the shader for further drawing, shading and sending of attributes
		static void useShader(GLuint shader);

		//Dispatch compute shader with width & height & length
		//Uses workgroups; the threads dispatched per workgroup are set in compute shader
		static void dispatchCompute(u32 width, u32 height, u32 length);


		//Update the data in the vbo
		//@param GLuint vbo
		//@param u32 offset;			offset of the element in the buffer
		//@param u32 length;			length to update
		//@param GLubyte data[length]	data to replace
		static void updateVBO(GLuint vbo, u32 offset, u32 length, GLubyte *data);

		//Update the data in the ssbo
		//@param GLuint ssbo
		//@param u32 offset;			offset of the element in the buffer
		//@param u32 length;			length to update
		//@param GLubyte data[length];	data to replace
		static void updateSSBO(GLuint ssbo, u32 offset, u32 length, GLubyte *data);


		//Log any errors reported by GL
		//@optional std::string prefix;	default = ""
		static bool shoutAny(std::string prefix = "");

		//Log any errors when creating the FBO
		//@param GLuint fbo
		static bool checkFBO(GLuint fbo);

	private:
		static GLenum getDrawType(EDrawType drawType);
		static GLenum getTextureTarget(ETextureType textureType);
		static GLenum getTextureFormat(ETextureFormat textureFormat);
		static GLenum getDepthType(EDepthType depthType);
	};
}