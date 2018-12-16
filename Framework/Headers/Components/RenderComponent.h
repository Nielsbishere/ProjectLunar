#pragma once
#include "../GameObjectBehaviour/Component.h"
#include "../Type/OTypes.h"
namespace lun {
	class Renderer;
	class RenderObject;
	class Transform;

	//Component attached to a GameObject to add a renderer
	class RenderComponent : public Component {
		friend class GameObject;

	public:

		//Basic constructor
		//Requires 'attachRenderer' to be called
		RenderComponent();

		//Sends the render data to the render engine
		void start() override;

		//Prepare data
		void onAttach() override;

		//Update the component
		void update(f32 delta) override;

		//Attach the model/renderobject to the object
		//@setter renderer->renderer
		void attachRenderer(Renderer *renderer);


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

		//@return bool !isStatic
		bool isDynamic();

		//@return Transform &transform
		Transform &getTransform();

	protected:
		~RenderComponent();

	private:
		RenderObject *renderer;
		bool started;
	};
}