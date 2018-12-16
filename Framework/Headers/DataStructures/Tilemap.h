#pragma once
#include "../Type/OTypes.h"
#include <string>
#include <vector>
#include "Bitset.h"
#include "../Resources/ResourcePile.h"
namespace lun {

	//An owner of a tile
	//0 = nobody
	//Otherwise, it is seen as a valid owner. For example; the default access id could be 333, which means that all tiles are claimed under owner '333' (when unmodded).
	typedef u32 OwnerId;

	struct Owner {
		std::string name;
		OwnerId id;
	};

	//An id of a tile
	typedef u32 TileId;
	class TileValidation {
		friend class Tilemap;
		friend class ModHelper;

	protected:

		//Whether or not an TileId is valid
		static bool isValid(TileId id);

		//Returns 0 when no available
		static TileId getRandom();

		//Gets index of TileId in ids vector
		//@error return 0xFF FF FF FF
		static u32 indexOf(TileId id);

	private:

		static std::vector<Owner> ids;
	};

	//Whether or not an OwnerId is valid
	class OwnerValidation {
		friend class Tilemap;
		friend class ModHelper;

	protected:

		//Whether or not an OwnerId is valid
		static bool isValid(OwnerId id);

		//Returns 0 when no available
		static OwnerId getRandom();

		//Gets index of OwnerId in ids vector
		//@error return 0xFF FF FF FF
		static u32 indexOf(OwnerId id);

	private:

		static std::vector<Owner> ids;
	};

	class Texture;
	class Tilemap {

	public:

		//Create a tilemap from a texture with a certain width/height in tiles
		//@param std::string name; tilemap name
		//@param std::string source; texture path
		//@param ResourcePile *rp; resource pile to store texture
		//@param OwnerId &i; the random id of the default access
		//@optional u32 w; width in tiles (default = 16)
		//@optional u32 h; height in tiles (default = 16)
		//@auto u32 tileWidth; width of tile in pixels (calculated by using w)
		//@auto u32 tileHeight; height of tile in pixels (calculated by using h)
		//@return Tilemap *tilemap
		//@error return nullptr
		//@errors
		//texture == nullptr
		//textureWidth % w != 0
		//textureHeight % h != 0
		//rp == nullptr
		//tw or th or w or h is 0
		//name == ""
		//@note
		//Creates w * h - 1 ids; so default has 255 ids (since 0 is air or nothing)
		static Tilemap *create(std::string name, std::string source, ResourcePile *rp, OwnerId &i, u32 w = 16, u32 h = 16);

		//Create an empty tilemap with a certain width/height in tiles
		//@param std::string name; tilemap name
		//@param ResourcePile *rp; resource pile to store texture
		//@param OwnerId &i; the random id of the default access
		//@optional u32 tw; width of one tile in pixels (default = 32)
		//@optional u32 th; height of one tile in pixels (default = 32)
		//@optional u32 w; width in tiles (default = 16)
		//@optional u32 h; height in tiles (default = 16)
		//@return Tilemap *tilemap
		//@error return nullptr
		//@errors
		//rp == nullptr
		//tw or th or w or h is 0
		//name == ""
		//@note
		//Creates w * h - 1 ids; so default has 255 ids (since 0 is air or nothing)
		static Tilemap *create(std::string name, ResourcePile *rp, OwnerId &i, u32 tw = 32, u32 th = 32, u32 w = 16, u32 h = 16);

		//Whether or not you can insert this texture at a certain id
		//@param TileId id (u32); index in tilemap
		//@param OwnerId oid (u32); owner of the tile (default owner is obtained from Tilemap::create, if you can't access that, you have to create a new one)
		//@param Texture *t; texture to insert at id
		//@return bool isInserted
		//@errors
		//id is taken
		//owner is invalid
		//texture == nullptr
		bool insert(TileId id, OwnerId owner, Texture *t);

		//Assigns the first available id to the texture if possible
		//@param OwnerId owner
		//@param Texture *t; texture to insert at id
		//@return TileId id
		//@error return 0
		//@errors
		//OwnerId is invalid
		//texture == nullptr
		TileId add(OwnerId owner, Texture *t);

		//Tries to remove the tile with id as long as it belongs to the owner
		//@errors
		//owner is invalid
		//id isn't owned by owner
		//there is nothing at id
		bool remove(OwnerId owner, TileId id);

		~Tilemap();

	protected:

		Tilemap();

	private:

		u32 tileWidth, tileHeight, width, height;
		Texture *t;
		ResourcePile *rp;
		OwnerId *owners;
		bool *tiles;
		std::string source, name;
	};
}