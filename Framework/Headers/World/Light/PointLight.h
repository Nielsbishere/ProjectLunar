#pragma once
#include "LightObject.h"
#include "../../GPU/Buffer.h"
#include "../../Reflection.h"
namespace lun {
	class PointLight : public LightObject {

	public:

		REFLECTION(PointLight) {
			EXPOSEVAR(PointLight, position);
			EXPOSEVAR(PointLight, color);
			EXPOSEVAR(PointLight, intensity);
		}

		//Create point light
		//@param vec3 position
		//@param vec3 color
		//@param f32 intensity
		PointLight(vec3 pos, vec3 color, f32 intensity);

		//@setter vec3 position
		void setPosition(vec3 p);

		//Moves with a certain vector
		//@setter vec3 position
		void move(vec3 dp);

		//@return vec3 position
		vec3 getPosition();

		//@return f32 radius
		f32 getRadius();

		//@return compressed version of data for GPU buffer
		TPointLight getData();

		//Link to GPU buffer
		void link(Buffer<PointLight, TPointLight> *parent);

	protected:

		vec4 getPosRadius();

		void onEdit() override;

	private:

		vec3 position;
		Buffer<PointLight, TPointLight> *daddy;
	};
}