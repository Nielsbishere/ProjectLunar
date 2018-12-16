#include "../../Headers/Camera/Camera.h"
#include "../../Headers/Shapes/Frustum.h"
#include "../../Headers/Input/InputHandler.h"
using namespace lun;

REFLECT_CLASS_NOFACTORY(Camera);

//Constructor
Camera::Camera(vec3 _position, vec3 _direction, f32 _fov, f32 _aspect, vec3 _up, f32 _far, f32 _near) : GameObject(_position), direction(_direction), fov(_fov), aspect(_aspect), far(_far), near(_near), up(_up) {}

//Getters
vec3 Camera::getPosition() { return getTransform().getPosition(); }
vec3 Camera::getCenter() { return getPosition() + direction; }
vec3 Camera::getUp() { return up; }
vec3 Camera::getDirection() { return direction; }
f32 Camera::getFov() { return fov; }
f32 Camera::getAspect() { return aspect; }
f32 Camera::getFar() { return far; }
f32 Camera::getNear() { return near; }
mat4 Camera::getView() { return mat4::lookat(getPosition(), getCenter(), up); }
mat4 Camera::getProjection() { return mat4::perspective(fov, aspect, near, far); }
Frustum Camera::getFrustum() { return Frustum(fov, aspect, far, near, getPosition(), getCenter(), up); }
vec3 Camera::getForward() { return direction; }
vec3 Camera::getRight() { return direction.cross(up); }
//TODO:
vec2 Camera::getRotation() {
	return vec2();
}

//Position
void Camera::move(vec3 newPos) { getTransform().setPosition(newPos); }
void Camera::addMovement(vec3 deltaPos) { getTransform().addPosition(deltaPos); }
void Camera::addLocal(vec3 v) { addMovement(getRight() * v.x + getUp() * v.y + getForward() * v.z); }

//Setters
void Camera::setFar(f32 far) { if (far < near) return; this->far = far; }
void Camera::setNear(f32 near) { if (near < far) return; this->near = near; }
bool Camera::setDirection(vec3 ndir) {
	if (ndir == vec3())return false;
	direction = ndir.normalize();
	return true;
}
void Camera::setRotation(vec2 rot) {
	rot *= M_PI / 180;
	vec3 fwd = mat4::rotateY(rot.y) * mat4::rotateX(rot.x) * vec4(0, 0, -1, 0);
	direction = fwd;
}

//Rotate
void Camera::rotate(f32 yaw, f32 pitch) {
	vec2 rot = getRotation();
	rot += vec2(yaw, pitch);
	rot *= 180 / M_PI;
	setRotation(rot);
}

//Aspect
void Camera::updateAspect(f32 _aspect) { aspect = _aspect; }

//Mirror axes
void Camera::mirrorXAxis() { direction.x *= -1; }
void Camera::mirrorYAxis() { direction.y *= -1; }
void Camera::mirrorZAxis() { direction.z *= -1; }

//Create camera
Camera *Camera::create(vec3 position, f32 aspect, f32 fov, vec3 direction, vec3 up, f32 far, f32 near) {
	if (far < near) {
		printf("Warning: Tried to create a camera with far < near. Defaulting to near=0.1, far = 100.\n");
		near = 0.1f;
		far = 100;
	}
	if (near == 0) {
		printf("Warning: Tried to create a camera with near = 0. Defaulting to near=0.1, far = 100.\n");
		near = 0.1f;
		far = 100;
	}
	if (up == vec3()) {
		printf("Warning: Invalid up direction. Defaulting to [0,1,0]\n");
		up = vec3(0, 1, 0);
	}
	if (direction == vec3()) {
		printf("Warning: Invalid forward direction. Defaulting to -z axis\n");
		direction = vec3(0, 0, -1);
	}
	if (fov < 10 || fov > 170) {
		printf("Warning: Invalid FOV. Should be in degrees [10, 170].\n");
		if (fov < 10)fov = 10;
		if (fov > 170)fov = 170;
	}
	if (aspect == 0) {
		printf("Warning: Camera aspect = 0. Defaulting to 16:9\n");
		aspect = 16.f / 9;
	}
	return new Camera(position, direction, fov, aspect, up, far, near);
}