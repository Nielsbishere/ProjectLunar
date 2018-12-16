#pragma once
#include "../CrossPlatform/Context.h"
#include "../Type/OTypes.h"
#include <map>
namespace lun {
	//Shader types
	//	DEFERRED; for opaque objects
	//	FORWARD; for transparent objects
	//	COMPUTE; for scripts on the GPU
	enum EShaderType {
		DEFERRED, FORWARD, COMPUTE
	};

	//Sub types for pipeline shaders
	//	VERT; vertex shader; applied on every vertex
	//	FRAG; fragment/pixel shader; applied on every fragment
	//	GEO; geometry shader; applied on every primitive
	enum EShaderSubType {
		VERT, FRAG, GEO
	};

	//Shader baseclass
	//Shader* used for all shaders
	//ComputeShader* used for compute shaders
	class Shader {
		template<class T> friend class ResourceObject;
		friend class ResourcePile;

	public:
		//@return EShaderType shaderType
		EShaderType getType();

		//Use this shader (required when setting attributes)
		void use();

		//Set uniform in shader as float with name "pos" (Case sensitive)
		void set(std::string pos, f32 f);

		//Set uniform in shader as integer with name "pos" (Case sensitive)
		void set(std::string pos, i32 i);

		//Set uniform in shader as unsigned integer with name "pos" (Case sensitive)
		void set(std::string pos, u32 i);

		//Set uniform in shader as boolean (int) with name "pos" (Case sensitive)
		void set(std::string pos, bool b);


		//Set uniform in shader as 4x4 matrix with name "pos" (Case sensitive)
		void set(std::string pos, mat4 m);

		//Set uniform in shader as vec2 with name "pos" (Case sensitive)
		void set(std::string pos, vec2 v);

		//Set uniform in shader as vec3 with name "pos" (Case sensitive)
		void set(std::string pos, vec3 v);

		//Set uniform in shader as vec4 with name "pos" (Case sensitive)
		void set(std::string pos, vec4 v);


		//Set uniform in shader as float array with name "pos" (Case sensitive)
		void set(std::string pos, f32 *f, u32 len);

		//Set uniform in shader as int array with name "pos" (Case sensitive)
		void set(std::string pos, i32 *i, u32 len);

		//Set uniform in shader as uint array with name "pos" (Case sensitive)
		void set(std::string pos, u32 *i, u32 len);

		//Set uniform in shader as vec2 array with name "pos" (Case sensitive)
		void set(std::string pos, vec2 *v, u32 len);

		//Set uniform in shader as vec3 array with name "pos" (Case sensitive)
		void set(std::string pos, vec3 *v, u32 len);

		//Set uniform in shader as vec4 array with name "pos" (Case sensitive)
		void set(std::string pos, vec4 *v, u32 len);

	protected:
		Shader(EShaderType t, GLuint i);
		~Shader();

		static Shader *load(std::string path, bool log = false);

		GLuint getId(std::string pos);

	private:
		std::map<std::string, GLuint> types;

		EShaderType type;
		GLuint id;

		static GLuint shader(GLenum type, const char *shaderSrc);
	};
}