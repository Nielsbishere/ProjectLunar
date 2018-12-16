#pragma once

#include <string>
#include "../../Type/OTypes.h"

namespace lun {
	class Mesh;
	class Shader;

	//Header for oiRM file; only used for size reference
	struct oiRMHead {
		u8 data[4];
		u32 vertices;
		u32 indices;
	};

	//Per vertex attributes; only used for size reference
	struct oiRMVertex {
		vec3f32 position;
		vec2f32 uv;
		vec3f32 normal;
	};

	//Class for loading and writing oiRM files
	class oiRM {
		template<class T> friend class ResourceObject;
		friend class ResourcePile;

	protected:
		//Load mesh from file
		static Mesh *load(std::string file, Shader *s, bool log=false);

		//Write mesh to file
		static void write(std::string file, Mesh *m);
	};
}