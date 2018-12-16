#pragma once
#include <vector>
#include <string>

namespace lun {
	class Mesh;
	class ResourcePile;
	class Grid2D;
	class Grid3D;
	class Shader;

	//Parameters for creating a marching squares mesh
	enum EMeshParamsMS {
		MS_INVALID = 0,

		MS_WALLS = 0b1, MS_ROOF = 0b10, MS_FLOOR = 0b100,

		MS_NOWALLS = MS_ROOF | MS_FLOOR,
		MS_NOROOF = MS_WALLS | MS_FLOOR,
		MS_NOFLOOR = MS_WALLS | MS_ROOF,

		MS_ALL = MS_WALLS | MS_NOWALLS
	};

	class MeshHelper {

	public:

		//Creates a top-down mesh (using x,z from Grid2D)
		//(Automatically positions the mesh around 0,0 with size 1 (-1,-1 to 1,1))
		static Mesh *createTopDown(ResourcePile *pile, std::string name, Shader *s, Grid2D *grid);

		//Creates a marching squares mesh (using [x,z] from Grid2D)
		//(Automatically positions the mesh around 0,0 with size 1 (-1,-1 to 1,1))
		static Mesh *createMarchingSquares(ResourcePile *pile, std::string name, Shader *s, Grid2D *grid, EMeshParamsMS params = MS_ALL);

		//Creates a marching cubes mesh (using [x,y,z] from Grid3D)
		//(Automatically positions the mesh around 0,0,0 with size 1 (-1,-1,-1 to 1,1,1))
		static Mesh *createMarchingCubes(ResourcePile *pile, std::string name, Shader *s, Grid3D *grid);
	};
}