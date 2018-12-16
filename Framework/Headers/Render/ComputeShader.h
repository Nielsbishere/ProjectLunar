#pragma once
#include "Shader.h"
namespace lun {
	class ComputeShader : public Shader {
		friend class Shader;
	public:
		//Execute ComputeShader
		//How many groups the GPU has to dispatch; so (3, 5, 3) would dispatch 3 x-axis, 5 y-axis and 3 z-axis.
		//ComputeShader on texture would often use length=1 and split the texture into a few threads
		//@param u32 width
		//@param u32 height
		//@param u32 length
		void execute(u32 width, u32 height, u32 length);

	protected:
		ComputeShader(EShaderType shaderType, GLuint id);
	};
}