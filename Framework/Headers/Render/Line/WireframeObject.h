#pragma once
#include "../../GameObjectBehaviour/Transform.h"
#include "../../Type/OTypes.h"
#include "../../Shapes/AABB.h"
namespace lun {
	class Wireframe;
	class WireframeObject {
		friend class WireframeComponent;

	public:

		REFLECTION(WireframeObject) {
			EXPOSEVAR(WireframeObject, isVisible);
			EXPOSEVAR(WireframeObject, usesDepth);
			EXPOSEVAR(WireframeObject, localTransform);
			EXPOSEVAR(WireframeObject, lineColor);
			EXPOSEVAR(WireframeObject, lineSize);
		}

		//@return bool !isVisible
		bool isHidden();

		//@setter bool !isVisible
		void toggleVisiblity();

		//@setter bool isVisible
		void hide();

		//@setter bool isVisible
		void show();

		//@setter bool isVisible
		void setHidden(bool hide);

		//@return vec3 lineColor
		vec3 getLineColor();

		//@return f32 lineSize
		f32 getLineSize();

		//@setter vec3 lineColor
		void setLineColor(vec3 lineColor);

		//@setter f32 lineSize
		void setLineSize(f32 lineSize);

		//Apply tint to line
		void colorize(vec3 tint);

		//@return Transform &transform
		Transform &getTransform();

		//@return Transform &transform
		Transform &getLocalTransform();

		//@return Renderer *wires
		Wireframe *getWireframe();

		//@return bool canRender
		bool canRender();

		//@return AABB bounding box
		AABB getAABB();

		//@setter bool usesDepth
		void setUsesDepth(bool b);

		//@return bool usesDepth
		bool fakes3D();

	protected:

		WireframeObject(bool visible, Transform local, Transform &transform, Wireframe *wires, vec3 lineColor=vec3(), f32 lineSize=1.f);

	private:

		bool isVisible;
		bool usesDepth;
		Transform &transform;
		Transform localTransform;
		Wireframe *wires;
		vec3 lineColor;
		f32 lineSize;
	};
}