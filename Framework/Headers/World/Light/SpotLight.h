#pragma once
#include "LightObject.h"
#include "../../GPU/Buffer.h"
namespace lun {
	class SpotLight : public LightObject {

	public:

		REFLECTION(SpotLight) {
			EXPOSEVAR(SpotLight, position);
			EXPOSEVAR(SpotLight, height);
			EXPOSEVAR(SpotLight, direction);
			EXPOSEVAR(SpotLight, radius);
			EXPOSEVAR(SpotLight, color);
			EXPOSEVAR(SpotLight, intensity);
		}

		//Create spotlight
		//@param vec3 position
		//@param f32 height
		//@param vec3 direction
		//@param f32 radius
		//@param vec3 color
		//@param f32 power
		SpotLight(vec3 p, f32 h, vec3 d, f32 r, vec3 color, f32 power);

		//@setter vec3 position
		void setPosition(vec3 p);

		//Moves with a certain vector
		//@setter vec3 position	
		void move(vec3 dp);

		//@setter vec3 direction
		void setDirection(vec3 d);

		//@setter f32 height
		void setHeight(f32 h);

		//@setter f32 radius
		void setRadius(f32 r);

		//@return vec3 position
		vec3 getPosition();

		//@return f32 height
		f32 getHeight();

		//@return vec3 direction
		vec3 getDirection();

		//@return f32 radius
		f32 getRadius();

		//@return compressed data for GPU buffer
		TSpotLight getData();

		//Link light object to buffer
		void link(Buffer<SpotLight, TSpotLight> *parent);

	protected:

		void onEdit() override;

	private:

		vec3 position;
		f32 height;
		vec3 direction;
		f32 radius;

		Buffer<SpotLight, TSpotLight> *daddy;
	};
}