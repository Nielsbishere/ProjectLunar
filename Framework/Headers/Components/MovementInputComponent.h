#pragma once
#include "../Components/MovementInputComponent.h"
#include "../GameObjectBehaviour/GameObject.h"
#include "../Type/OTypes.h"
namespace lun {
	//Basic movement input component; can be attached to a GameObject to provide basic WASD (^<V>) movement.
	//W and up arrow for forward
	//S and down arrow for backward
	//A and left arrow for left
	//D and right arrow for right
	//Q for down
	//E for up
	class MovementInputComponent : public Component {
	public:
		REFLECTION(MovementInputComponent) {
			//REQUIRED(InputComponent);		//TODO:
			EXPOSEVAR(MovementInputComponent, speed);
		}

		//Basic constructor; use vec3 constructor to set speed
		//Or use setSpeed on an empty constructor instance
		MovementInputComponent(vec3 _speed = vec3(1, 1, 1));

		//@return vec3 speed
		vec3 getSpeed();

		//@setter vec3 speed
		void setSpeed(vec3 sp);

		//The basic start function
		//Fetches InputComponent from the player (if attached)
		void start() override;

		//Applies input to the owner of this component
		void update(f32 dt) override;
		
	private:
		bool activated;
		vec3 speed;
	};
}