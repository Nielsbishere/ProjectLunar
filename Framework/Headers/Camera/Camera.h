#pragma once
#include "../Type/OTypes.h"
#include "../GameObjectBehaviour/GameObject.h"
namespace lun {
	class Frustum;
	class InputHandler;

	//Camera is an object in the world and simulates a viewpoint in the game
	//It has a frustum for culling and a view/projection matrix for rendering
	class Camera : public GameObject {
		friend class World;
	public:
		REFLECTION(Camera) {
			EXPOSEVAR(Camera, fov);			//>10 && < 170
			EXPOSEVAR(Camera, aspect);		//not 0
			EXPOSEVAR(Camera, far);			//> near && not 0
			EXPOSEVAR(Camera, near);		//< far && not 0
			EXPOSEVAR(Camera, direction);	//!= 0
			EXPOSEVAR(Camera, up);			//!= 0
		}

		//Create camera in world
		//@param vec3 world position
		//@param f32 aspect ratio
		//@optional f32 fov;					default: 40 (degrees)
		//@optional vec3 view direction;		default: (0, 0, -1) (negative Z direction)
		//@optional vec3 up direction;			default: (0, 1, 0) (world up)
		//@optional f32 far;					default: 100
		//@optional f32 near;					default: 0.1
		//@error corrects invalid values to defaults
		//@return Camera *camera
		static Camera *create(vec3 position, f32 aspect, f32 fov=40, vec3 direction = vec3(0, 0, -1), vec3 up = vec3(0, 1, 0), f32 far = 100.f, f32 near = 0.1f);

		//@return vec3 world position
		vec3 getPosition();

		//@return vec3 camera focus (center)
		vec3 getCenter();

		//@return vec3 camera up
		vec3 getUp();

		//@return vec3 forward direction of camera
		vec3 getForward();

		//@return vec3 right direction of camera
		vec3 getRight();

		//@return vec3 direction of camera
		vec3 getDirection();

		//@return f32 fov (degrees)
		f32 getFov();

		//@return f32 aspect (width / height)
		f32 getAspect();

		//@return f32 far
		f32 getFar();

		//@return f32 near
		f32 getNear();

		//Set far plane
		//@setter far;	if far < near
		void setFar(f32 far);

		//Set near plane
		//@setter near;  if near < far
		void setNear(f32 near);

		//Move to a world position
		//@setter Transform.position
		void move(vec3 position);

		//Applies movement to this Camera
		//@setter Transform.position
		void addMovement(vec3 deltaPosition);

		//Applies local (relative) movement to this camera
		//@setter Transform.position
		void addLocal(vec3 localPosition);

		//Set forward direction
		//@setter direction
		bool setDirection(vec3 direction);

		//Rotate with (yaw, pitch)
		//@setter direction
		void rotate(f32 yaw, f32 pitch);

		//Mirrors the X axis
		void mirrorXAxis();

		//Mirrors the Y axis
		void mirrorYAxis();

		//Mirrors the Z axis
		void mirrorZAxis();

		//Get the view matrix of this camera
		mat4 getView();

		//Get the projection matrix of this camera
		mat4 getProjection();

		//Get the rotation of this camera (yaw, pitch)
		//@return vec2 xy
		vec2 getRotation();

		//Set the rotation of this camera (yaw, pitch)
		//@setter direction
		void setRotation(vec2 rotation);

		//Create a frustum (for culling)
		Frustum getFrustum();

	protected:
		void updateAspect(f32 aspect);

	private:
		f32 fov, aspect, far, near;
		vec3 direction, up;

		Camera(vec3 position, vec3 direction, f32 fov, f32 aspect, vec3 up, f32 far, f32 near);
	};
}