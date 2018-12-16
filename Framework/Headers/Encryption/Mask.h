#pragma once
#include "../Type/OTypes.h"
namespace lun {
	class Mask {

	public:

		//Applies a mask
		static u32 encode(u32 decoded, u32 mask);

		//Removes a mask
		static u32 decode(u32 encoded, u32 mask);
	};
}