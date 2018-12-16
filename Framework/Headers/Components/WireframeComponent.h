#pragma once
#include "../GameObjectBehaviour/Component.h"
#include "../GameObjectBehaviour/Transform.h"
#include "../Type/OTypes.h"
namespace lun {
	class Wireframe;
	class WireframeObject;

	//Component attached to a GameObject to add a wireframe
	class WireframeComponent : public Component {
		friend class GameObject;

	public:

		//Basic constructor
		//Requires 'attachWires' to be called
		WireframeComponent(Transform local=Transform());

		//Sends the render data to the render engine
		void start() override;

		//Prepares data
		void onAttach() override;

		//Update the component
		void update(f32 delta) override;

		//Attach the wireframe to the object
		//@setter wires->wires
		void attachWires(Wireframe *renderer);


		///Shortcuts

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

		//@setter bool usesDepth
		void setUsesDepth(bool b);

		//Apply tint to line
		void colorize(vec3 tint);

		//@return Transform & object transform
		Transform &getObjectTransform();

		//@return Transform & object relative transform
		Transform &getLocalTransform();

	protected:
		~WireframeComponent();

	private:
		Transform tempTransform;
		WireframeObject *wires;

		bool started;
	};
}