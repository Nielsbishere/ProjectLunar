#pragma once
namespace lun {
	//All supported file extensions
	enum EResourceType {
		//Shader types
		OGLSL = 0x100,	//Osomi GLSL

		//Model types
		OIRM = 0x200,	//OsomI Raw Model
		OIEM = 0x201,	//OsomI Encrypted Model
		OIOM = 0x202,	//OsomI Optimized Model
		OIM = 0x203,	//OsomI Model

		//Texture formats (pixels)
		PNG = 0x300,	//Portable Network Graphics
		JPG = 0x301,	//Joint Photographic Group
		OICT = 0x302,	//OsomI Compressed Texture

		//Texture formats (vectors)
		SVG = 0x400,	//Scalable Vector Graphics
		OICVI = 0x303,	//OsomI Compressed Vector Image

		//Audio formats
		OGG = 0x500,	//OGG (audio; open source)
		OIMF = 0x501,	//OsomI Music File

		//Video formats
		OIVID = 0x600,	//OsomI Video

		//Procedural texture formats
		OIPT = 0x700,	//OsomI Procedural Texture

		//Procedural mesh formats
		OIPHM = 0x800,	//OsomI Procedural Height Mesh
		OIPMS = 0x801,	//OsomI Procedural Marching Squares
		OIPMC = 0x802,	//OsomI Procedural Marching Cubes

		//Debug file formats
		OILR = 0x900,	//OsomI Line Renderer
		OIWF = 0x901,	//OsomI WireFrame

		//Scripting file formats
		OICL = 0xA00,	//OsomI Compute Language
		OICLD = 0xA01,	//OsomI Compute Language Data (compiled OICL)

		//Unsupported
		UNSUPPORTED = 0x10000
	};
	//Types of extensions
	enum EFileType {
		UNDEF = 0,
		SHADER = 1,
		MODEL = 2,
		TEXTURE = 3,
		VECTEX = 4,
		AUDIO = 5,
		VIDEO = 6,
		PROCEDURAL_TEXTURE = 7,
		PROCEDURAL_MESH = 8,
		DEBUG = 9,
		SCRIPTING = 10
	};
}