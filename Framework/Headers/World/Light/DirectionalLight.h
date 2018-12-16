#pragma once
#include "LightObject.h"
#include "../../GPU/Buffer.h"
#include "../../Type/DataTypes.h"
namespace lun {
	class DirectionalLight : public LightObject {

	public:

		REFLECTION(DirectionalLight) {
			EXPOSEVAR(DirectionalLight, direction);
			EXPOSEVAR(DirectionalLight, color);
			EXPOSEVAR(DirectionalLight, intensity);
		}

		//Create directional light
		//@param vec3 direction
		//@param vec3 color
		//@param f32 intensity
		DirectionalLight(vec3 dir, vec3 color, f32 intensity);

		//@setter vec3 direction
		void setDirection(vec3 d);

		//@return vec3 direction
		vec3 getDirection();

		//Positions the directional light (temporarily) relative to the camera
		//@return vec3 position (world)
		vec3 getPosition(vec3 camPos, f32 delta);

		//@return compressed data for GPU buffer
		TDirectionalLight getData();

		//Link light object to buffer
		void link(Buffer<DirectionalLight, TDirectionalLight> *parent);

	protected:

		void onEdit() override;

	private:

		vec3 direction;
		Buffer<DirectionalLight, TDirectionalLight> *daddy;
	};
}