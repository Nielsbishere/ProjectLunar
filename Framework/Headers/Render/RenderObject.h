#pragma once
#include "../GameObjectBehaviour/Transform.h"
namespace lun {
	class Renderer;
	class RenderObject {
		friend class RenderComponent;

	public:

		REFLECTION(RenderObject) {
			EXPOSEVAR(RenderObject, isVisible);
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

		//@return bool !isStatic
		bool isDynamic();

		//@return Transform &transform
		Transform &getTransform();

		//@return Renderer *r
		Renderer *getRenderer();

	protected:

		RenderObject(bool visible, bool &isStatic, Transform &transform, Renderer *r);

	private:

		bool isVisible;
		bool &isStatic;
		Transform &transform;
		Renderer *r;
	};
}