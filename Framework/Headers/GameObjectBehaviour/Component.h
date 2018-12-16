#pragma once

#include "../Type/DataTypes.h"

namespace lun {
	class GameObject;

	//A component can be attached to a GameObject
	//It can handle anything, as long as it is supposed to be attachable to a GameObject
	class Component  {
	public:
		//Basic component constructor
		Component();

		//Basic component destructor
		~Component();

		//Start function (should be overridden in child class)
		virtual void start() = 0;

		//Update function (should be overridden in child class)
		virtual void update(f32 deltaTime) = 0;

		//On attach (can be overridden in child class)
		virtual void onAttach();

		//Get the object it is attached to
		//@return GameObject *owner
		GameObject *getOwner();

		//Attaches owner; if there is none attached
		//@setter GameObject *owner
		void attachOwner(GameObject *owner);

	private:
		GameObject *owner;
	};
}