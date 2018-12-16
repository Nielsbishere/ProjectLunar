#pragma once

#include "../Type/vec3.h"
#include "../Type/mat4.h"

namespace lun {
	//Attached to anything that is positioned in the world
	//Includes position, rotation and scale
	class Transform {
	public:
		REFLECTION(Transform) {
			EXPOSEVAR(Transform, position);
			EXPOSEVAR(Transform, rotation);
			EXPOSEVAR(Transform, scale);
		}

		//Creates a position/rotation/scale for an object in the world
		//@optional vec3 position; default: (0, 0, 0)
		//@optional vec3 rotation (degrees); default (0, 0, 0)
		//@optional vec3 scale; default (1, 1, 1)
		Transform(vec3 position=vec3(), vec3 rotation=vec3(), vec3 scale=vec3(1, 1, 1));

		//Convert 3 vec3s into a transformation/model matrix
		//@return mat4 M
		mat4 makeModelMatrix();

		//@return vec3 position
		vec3 getPosition();

		//@return vec3 rotation
		vec3 getRotation();

		//@return vec3 scale
		vec3 getScale();

		//@setter vec3 position
		void setPosition(vec3 position);

		//@setter vec3 rotation
		void setRotation(vec3 rotation);

		//@setter vec3 scale
		void setScale(vec3 scale);

		//Adds delta to position
		//@setter vec3 position
		void addPosition(vec3 delta);

		//Adds delta to rotation
		//@setter vec3 position
		void addRotation(vec3 delta);

		//Adds delta to rotation in local space / relative to the player
		//@setter vec3 position
		void addLocal(vec3 delta);

		//Called to prevent changing values
		//This is used in static objects
		//@setter bool readOnly
		void setReadOnly();

	private:
		vec3 position, rotation, scale;
		bool readOnly;

		mat4 m;
		bool edit;
	};
}