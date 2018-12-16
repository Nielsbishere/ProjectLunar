#pragma once
#include "../../Type/OTypes.h"
namespace lun {
	//Class for any point in 3D space that should be connected in some sort of way
	class Node {

	public:

		//Create default node
		Node();

		//Create node in 3D space
		Node(u32 _id, vec3 _position);

		//@return vec3 position
		vec3 getPosition();

		//@setter vec3 position
		void move(vec3 _position);

		//@setter vec3 position
		void addPosition(vec3 delta);

		void setId(u32 i);

	private:

		u32 id;
		vec3 position;
	};
}