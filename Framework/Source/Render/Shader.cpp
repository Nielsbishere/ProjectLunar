#include "../../Headers/Render/Shader.h"
#include "../../Headers/Render/ComputeShader.h"
#include "../../Headers/Helper/StringHelper.h"
#include "../../Headers/Helper/OGLHelper.h"
#include <fstream>
using namespace lun;
using namespace std;

GLuint Shader::shader(GLenum type, const char *shaderSrc) {
	GLuint sh = glCreateShader(type);

	if (sh == 0) return GL_FALSE;

	glShaderSource(sh, 1, &shaderSrc, nullptr);
	glCompileShader(sh);

	GLint hasErrors;

	glGetShaderiv(sh, GL_COMPILE_STATUS, &hasErrors);
	if (!hasErrors) {
		GLint RetinfoLen = 0;
		glGetShaderiv(sh, GL_INFO_LOG_LENGTH, &RetinfoLen);
		if (RetinfoLen > 1) {
			char* infoLog = (char*)malloc(sizeof(char) * RetinfoLen);
			glGetShaderInfoLog(sh, RetinfoLen, NULL, infoLog);
			fprintf(stderr, "Error compiling this shader:\n%s\n", infoLog);
			free(infoLog);
		}
		glDeleteShader(sh);
		return GL_FALSE;
	}
	return sh;
}

GLuint Shader::getId(std::string pos) { return types[pos]; }

void Shader::set(string pos, f32 f) {
	GLuint l = getId(pos);
	glUniform1f(l, f);
}
void Shader::set(string pos, i32 i) {
	GLuint l = getId(pos);
	glUniform1i(l, i);
}
void Shader::set(string pos, u32 i) {
	GLuint l = getId(pos);
	glUniform1ui(l, i);
}
void Shader::set(string pos, bool b) {
	GLuint l = getId(pos);
	glUniform1i(l, b);
}
void Shader::set(string pos, mat4 m) {
	GLuint l = getId(pos);
	glUniformMatrix4fv(l, 1, GL_FALSE, &m[0][0]);
}
void Shader::set(string pos, vec2 v) {
	GLuint l = getId(pos);
	glUniform2fv(l, 1, &v.x);
}
void Shader::set(string pos, vec3 v) {
	GLuint l = getId(pos);
	glUniform3fv(l, 1, &v.x);
}
void Shader::set(string pos, vec4 v) {
	GLuint l = getId(pos);
	glUniform4fv(l, 1, &v.x);
}

void Shader::set(string pos, f32 *f, u32 len) {
	GLuint l = getId(pos);
	glUniform1fv(l, len, f);
}
void Shader::set(string pos, i32 *i, u32 len) {
	GLuint l = getId(pos);
	glUniform1iv(l, len, i);
}
void Shader::set(string pos, u32 *i, u32 len) {
	GLuint l = getId(pos);
	glUniform1uiv(l, len, i);
}
void Shader::set(string pos, vec2 *v, u32 len) {
	GLuint l = getId(pos);
	glUniform2fv(l, len, (GLfloat*)v);
}
void Shader::set(string pos, vec3 *v, u32 len) {
	GLuint l = getId(pos);
	glUniform3fv(l, len, (GLfloat*)v);
}
void Shader::set(string pos, vec4 *v, u32 len) {
	GLuint l = getId(pos);
	glUniform4fv(l, len, (GLfloat*)v);
}
vector<string> parseFunc(vector<u32> vlocationsn, vector<string> vlines, string s, string s1) {
	u32 len = (u32)vlocationsn.size() / 2;
	for (u32 i = len - 1; i != 0xFFFFFFFF; i--) {
		u32 start = vlocationsn[i * 2];
		u32 end = vlocationsn[i * 2 + 1];
		for (u32 j = end; j >= start && j != 0xFFFFFFFF; j--)
			vlines.erase(vlines.begin() + j);
	}
	vector<string> toErase;
	toErase.push_back(s);
	toErase.push_back(s1);

	vlines = StringHelper::erase(vlines, toErase, true);

	return vlines;
}

vector<string> parse(vector<string> lines, string s1, string s2, string s3, string s4) {
	vector<u32> vlocationsn;
	StringHelper::find(lines, s3, s4, vlocationsn, true);

	if (vlocationsn.size() != 0)
		return parseFunc(vlocationsn, lines, s1, s2);
	return lines;

}

Shader *Shader::load(string name, bool log) {
	ifstream in(name, ios::in);
	if (!in.good()) {
		printf("Couldn't read file with path \"%s\"\n", name.c_str());
		return nullptr;
	}
	EShaderType est = EShaderType::COMPUTE;
	bool b = false;

	u32 lines = 0;
	string line;

	vector<string> file = vector<string>();

	while (getline(in, line)) {
		string curr;
		if (line == "" || (curr = StringHelper::trim(line)) == "" || StringHelper::startsWith(curr, "//"))continue;

		//Determine type of shader
		if (StringHelper::startsWith(curr, "UseDeferred")) {
			if (lines == 0) {
				est = EShaderType::DEFERRED;
				b = true;
				continue;
			}
			else {
				printf("Couldn't read file with path \"%s\". The type of the shader should be mentioned at the first line!\n", name.c_str());
				return nullptr;
			}
		}
		else if (StringHelper::startsWith(curr, "UseForward")) {
			if (lines == 0) {
				est = EShaderType::FORWARD;
				b = true;
				continue;
			}
			else {
				printf("Couldn't read file with path \"%s\". The type of the shader should be mentioned at the first line!\n", name.c_str());
				return nullptr;
			}
		}
		else if (StringHelper::startsWith(curr, "UseCompute")) {
			if (lines == 0) {
				est = EShaderType::COMPUTE;
				b = true;
				continue;
			}
			else {
				printf("Couldn't read file with path \"%s\". The type of the shader should be mentioned at the first line!\n", name.c_str());
				return nullptr;
			}
		}

		//Make sure the type is mentioned
		if (lines != 0 && (StringHelper::startsWith(curr, "UseCompute") || StringHelper::startsWith(curr, "UseForward") || StringHelper::startsWith(curr, "UseDeferred") || !b)) {
			printf("Couldn't read file with path \"%s\". The type of the shader should be mentioned at the first line!\n", name.c_str());
			return nullptr;
		}

		file.push_back(curr);
		lines++;
	}

	if (est != EShaderType::COMPUTE) {
		//Check if it contains at least 1 vert & frag line and decide whether or not to compile the geo shader
		std::vector<u32> vloc;
		StringHelper::find(file, "Vert", "EndVert", vloc);
		std::vector<u32> floc;
		StringHelper::find(file, "Frag", "EndFrag", floc);
		std::vector<u32> gloc;
		StringHelper::find(file, "Geo", "EndGeo", gloc);

		if (vloc.size() == 0 || floc.size() == 0) {
			printf("Couldn't read file with path \"%s\". Doesn't contain at least one line of Vert/Frag shader. This is a requirement for a shader!\n", name.c_str());
			return nullptr;
		}

		//Vert shader
		std::vector<std::string> v = parse(file, "Vert", "EndVert", "Frag", "EndFrag");
		v = parse(v, "Vert", "EndVert", "Geo", "EndGeo");
		std::string vert = "#version 430 core" + StringHelper::lineEnd() + StringHelper::combine(v, StringHelper::lineEnd());
		const char *vsh = vert.c_str();

		//Geo shader
		std::vector<std::string> g = parse(file, "Geo", "EndGeo", "Vert", "EndVert");
		g = parse(g, "Geo", "EndGeo", "Frag", "EndFrag");
		std::string geo = "#version 430 core" + StringHelper::lineEnd() + StringHelper::combine(g, StringHelper::lineEnd());
		const char *gsh = geo.c_str();

		//Frag shader
		std::vector<std::string> f = parse(file, "Frag", "EndFrag", "Vert", "EndVert");
		f = parse(f, "Frag", "EndFrag", "Geo", "EndGeo");
		std::string frag = "#version 430 core" + StringHelper::lineEnd() + StringHelper::combine(f, StringHelper::lineEnd());
		const char *fsh = frag.c_str();

		//Compile shader
		GLuint vertexShader = shader(GL_VERTEX_SHADER, vsh);
		if (vertexShader == 0) {
			printf("Couldn't read file with path \"%s\". Couldn't attach vertex shader!\n", name.c_str());
			return nullptr;
		}
		GLuint fragmentShader = shader(GL_FRAGMENT_SHADER, fsh);
		if (fragmentShader == 0) {
			glDeleteShader(vertexShader);
			printf("Couldn't read file with path \"%s\". Couldn't attach fragment shader!\n", name.c_str());
			return nullptr;
		}
		GLuint geoShader = 0;
		if (gloc.size() != 0) {
			geoShader = shader(GL_GEOMETRY_SHADER, gsh);
			if (geoShader == 0) {
				glDeleteShader(vertexShader);
				glDeleteShader(fragmentShader);
				printf("Couldn't read file with path \"%s\". Couldn't attach geometry shader!\n", name.c_str());
				return nullptr;
			}
		}

		GLuint programObject = glCreateProgram();
		if (programObject == 0) {
			printf("Couldn't read file with path \"%s\". Couldn't create program!\n", name.c_str());
			return 0;
		}

		glAttachShader(programObject, vertexShader);
		glAttachShader(programObject, fragmentShader);
		if (gloc.size() != 0)glAttachShader(programObject, geoShader);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		if (gloc.size() != 0)glDeleteShader(geoShader);

		glLinkProgram(programObject);

		GLint linked;
		glGetProgramiv(programObject, GL_LINK_STATUS, &linked);
		if (!linked) {
			GLint RetinfoLen = 0;
			glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &RetinfoLen);
			if (RetinfoLen > 1) {
				GLchar* infoLog = (GLchar*)malloc(sizeof(char) * RetinfoLen);
				glGetProgramInfoLog(programObject, RetinfoLen, nullptr, infoLog);
				fprintf(stderr, "Error linking program:\n%s\n", infoLog);

				vector<string> lines = StringHelper::split(vert, StringHelper::lineEnd());
				printf("Vertex shader:\n");
				for (u32 i = 0; i < lines.size(); i++)
					printf("%u\t\t%s\n", i + 1, lines[i].c_str());

				if (gloc.size() != 0) {
					printf("Geometry shader:\n");
					lines = StringHelper::split(geo, StringHelper::lineEnd());
					for (u32 i = 0; i < lines.size(); i++)
						printf("%u\t\t%s\n", i + 1, lines[i].c_str());
				}

				printf("\nFragment shader:\n");
				lines = StringHelper::split(frag, StringHelper::lineEnd());
				for (u32 i = 0; i < lines.size(); i++)
					printf("%u\t\t%s\n", i + 1, lines[i].c_str());

				free(infoLog);
			}
			glDeleteProgram(programObject);
			return nullptr;
		}
		return new Shader(est, programObject);
	}
	else {
		//Check if contains Vert, EndVert, Frag, EndFrag, Geo, EndGeo
		std::vector<u32> vloc;
		StringHelper::find(file, "Vert", "EndVert", vloc);
		std::vector<u32> floc;
		StringHelper::find(file, "Frag", "EndFrag", floc);
		std::vector<u32> gloc;
		StringHelper::find(file, "Geo", "EndGeo", gloc);

		if (vloc.size() != 0 || floc.size() != 0 || gloc.size() != 0) {
			printf("Couldn't read file with path \"%s\". ComputeShader doesn't support Vert/Frag/Geo\n", name.c_str());
			return nullptr;
		}

		//Compile compute shader
		GLuint programObject = glCreateProgram();
		if (programObject == 0) {
			printf("Couldn't read file with path \"%s\". Couldn't create program!\n", name.c_str());
			return nullptr;
		}
		file.insert(file.begin(), "#version 430 core");
		std::string source = StringHelper::combine(file, StringHelper::lineEnd());
		const char *str = source.c_str();
		GLuint cs = shader(GL_COMPUTE_SHADER, str);
		if (cs == 0) {
			for (u32 i = 0; i < file.size(); i++)
				printf("%u\t\t%s\n", i + 1, file[i].c_str());
			printf("Couldn't read file with path \"%s\". Couldn't attach shader!\n", name.c_str());
			return nullptr;
		}

		glAttachShader(programObject, cs);
		glDeleteShader(cs);

		glLinkProgram(programObject);

		GLint linked;
		glGetProgramiv(programObject, GL_LINK_STATUS, &linked);
		if (!linked) {
			GLint RetinfoLen = 0;
			glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &RetinfoLen);
			if (RetinfoLen > 1) {
				GLchar* infoLog = (GLchar*)malloc(sizeof(char) * RetinfoLen);
				glGetProgramInfoLog(programObject, RetinfoLen, nullptr, infoLog);
				fprintf(stderr, "Error linking program:\n%s\n", infoLog);

				printf("Compute shader:\n");
				for (u32 i = 0; i < file.size(); i++)
					printf("%u\t\t%s\n", i + 1, file[i].c_str());

				free(infoLog);
			}
			glDeleteProgram(programObject);
			return nullptr;
		}
		return new ComputeShader(est, programObject);
	}
}

EShaderType Shader::getType() { return type; }

//Use this shader (required when setting attributes)
void Shader::use() { OGLHelper::useShader(id); }

//Clean up
Shader::~Shader() { OGLHelper::destroyShader(id); }

//Create shader
Shader::Shader(EShaderType t, GLuint _id) : type(t), id(_id) {
	GLint count, size;
	GLenum type;
	GLchar name[16];
	GLsizei length;

	glGetProgramiv(id, GL_ACTIVE_UNIFORMS, &count);

	types = std::map<std::string, GLuint>();
	for (GLint i = 0; i < count; i++){
		glGetActiveUniform(id, (GLuint)i, 16, &length, &size, &type, name);
		types.insert(std::make_pair(std::string(name, length), i));
	}
}