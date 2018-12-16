#pragma once
#include "../Type/OTypes.h"

// Cellular noise ("Worley noise") in 3D in GLSL.
// Copyright (c) Stefan Gustavson 2011-04-19. All rights reserved.
// This code is released under the conditions of the MIT license.
// Author: Stefan Gustavson	(Algorithm for GLSL)
// 		   Niels Brunekreef	(Ported GLSL code to C++, formatted and added shortcut for 1D and 2D worley).
// Title: Classic 3D cellular noise

namespace lun{
	
	// Cellular noise, returning F1 and F2 in a vec2.
	// 3x3x3 search region for good F2 everywhere, but a lot
	// slower than the 2x2x2 version.
	// The code below is a bit scary even to its author,
	// but it has at least half decent performance on a
	// modern GPU. In any case, it beats any software
	// implementation of Worley noise hands down.
	class WorleyNoise {
	
	private:
	
		static vec3 permute(vec3 x);
		static vec2 worley(vec3 P, f32 jitter = 1.f);
			
	public:
		
		//Actual worley noise (Looks like crystals)
		static f32 worley3D(vec3 P, f32 jitter = 1.f);
		
		//Cellular noise (The x component of worley noise)
		static f32 cellularNoise3D(vec3 P, f32 jitter = 1.f);

		//Actual worley noise (Looks like crystals)
		static f32 worley2D(vec2 P, f32 jitter = 1.f);
		
		//Cellular noise (The x component of worley noise)
		static f32 cellularNoise2D(vec2 P, f32 jitter = 1.f);

		//Actual worley noise (Looks like crystals)
		static f32 worley1D(f32 P, f32 jitter = 1.f);

		//Cellular noise (The x component of worley noise)
		static f32 cellularNoise1D(f32 P, f32 jitter = 1.f);

	private:

		static f32 K, Ko, K2, Kz, Kzo;
	};
}