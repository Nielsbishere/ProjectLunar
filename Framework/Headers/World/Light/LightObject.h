#pragma once
#include "LightDataTypes.h"
namespace lun {
	class LightObject {

	public:

		//@setter vec3 color
		void setColor(vec3 c);

		//@setter f32 intensity
		void setIntensity(f32 i);

		//Multiply the intensity
		//@setter f32 multiply
		void intensify(f32 mi);

		//@return vec3 color
		vec3 getColor();

		//@return f32 intensity
		f32 getIntensity();

	protected:

		LightObject(vec3 c, f32 i);

		vec4 getColPow();

		virtual void onEdit() = 0;

		vec3 color;
		f32 intensity;
	};
}