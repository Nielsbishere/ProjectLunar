#pragma once
#include "../Type/OTypes.h"
namespace lun {
	class Shader;
	class Renderer;
	class Texture;

	class UIObject {
		friend class RenderEngine;

	public:

		REFLECTION(UIObject) {
			EXPOSEVAR(UIObject, offset);
			EXPOSEVAR(UIObject, scale);
			EXPOSEVAR(UIObject, rotation);
			EXPOSEVAR(UIObject, isHidden);
			EXPOSEVAR(UIObject, uvOffset);
			EXPOSEVAR(UIObject, uvScale);
			EXPOSEVAR(UIObject, colorizer);
			EXPOSEVAR(UIObject, depth);
		}

		//Create UIObject
		//@optional Renderer *model
		//@optional Texture *texture
		//@optional vec2 offset (-1, -1 to 1, 1; OGL space)
		//@optional vec2 scale (1, 1 = -1, -1 to 1, 1)
		//@optional f32 rotation (rotation around z axis in degrees)
		//@optional f32 depth; layer the object is on. 0->100; 100 being far, 0 being near.
		//@optional vec2 uvOffset; offset to the uv of the texture
		//@optional vec2 uvScale; scale of the uv scale
		//@optional vec4 colorizer; RGB, opacity. Multiplies the current color by the colorizer. (1, 0, 0, 0.5) would only show the red in the picture with half opacity
		//@optional bool isHidden
		//@error creates UIObject that won't be rendered
		UIObject(Renderer *r = nullptr, Texture *t = nullptr, vec2 offset = vec2(0, 0), vec2 scale = vec2(1, 1), f32 rotation = 0, f32 depth = 0, vec2 uvOffset = vec2(0, 0), vec2 uvScale = vec2(1, 1), vec4 colorizer = vec4(1, 1, 1, 1), bool isHidden = false);

		//Render the object to bound FBO & current shader
		void render(Shader *s);


		//@setter vec2 screen position / offset
		void setOffset(vec2 _offset);

		//Move the screen position by delta
		//@setter vec2 screen position / offset
		void move(vec2 delta);


		//@setter f32 rotation
		void setRotation(f32 _rotation);

		//Rotates by an angle
		//@setter f32 rotation
		void rotate(f32 delta);


		//@setter vec4 colorizer
		void setColorizer(vec4 col);

		//Colorize the current colorizer; apply a filter to the filtered image
		//@setter vec4 colorizer
		void colorize(vec4 colorize);


		//@setter vec4 colorizer.w
		void setOpacity(f32 opacity);

		//Decrease the current opacity by applying a percentage
		//@setter vec4 colorizer.w
		void fadeOpacity(f32 percentage);


		//@settter vec2 scale
		void setScale(vec2 _scale);

		//Scale this object by a factor
		//@setter vec2 scale
		void applyScale(vec2 factor);


		//@setter vec2 uvOffset
		void setUvOffset(vec2 _uvOffset);

		//@setter vec2 uvScale
		void setUvScale(vec2 _uvScale);


		//@setter f32 depth / layer
		void setDepth(f32 _depth);

		//@setter bool isHidden
		void setVisible(bool visible);


		//@setter bool isHidden
		void hide();

		//@setter bool isHidden
		void show();

		//@setter bool isHidden
		void toggle();


		//@return vec2 screen position / offset
		vec2 getOffset();

		//@return vec2 scale
		vec2 getScale();

		//@return vec2 uvOffset
		vec2 getUvOffset();

		//@return vec2 uvScale
		vec2 getUvScale();

		//@return vec4 colorizer
		vec4 getColorizer();

		//@return f3 depth
		f32 getDepth();

		//@return bool isVisible
		bool isVisible();

		//@return bool canRender
		bool canRender();

		//Function for sorting 
		bool operator<(const UIObject &uio);

	protected:

		//RenderEngine get model
		Renderer *getRenderer();

		//RenderEngine get texture
		Texture *getTexture();

		//RenderEngine nobind render
		void nobindRender(Shader *s);

	private:

		///What shape is this UIObject (Spoiler; Quad. Most of the time)
		Renderer *r;
		Texture *t;

		///Where on the screen is this UI object
		vec2 offset, scale;
		f32 rotation;
		bool isHidden;

		///What are the uv values of the UI object
		vec2 uvOffset, uvScale;

		///What colorizer should be applied? Default vec4(1, 1, 1, 1); no colorizer
		vec4 colorizer;

		///Depth/layer of the UIObject; can be ANY number between 0 and 100.
		f32 depth;
	};
}