#include "../../Headers/Render/ComputeShader.h"
#include "../../Headers/Helper/OGLHelper.h"
using namespace lun;
void ComputeShader::execute(u32 width, u32 height, u32 length) { OGLHelper::dispatchCompute(width, height, length); }
ComputeShader::ComputeShader(EShaderType shaderType, GLuint id) : Shader(shaderType, id) {}