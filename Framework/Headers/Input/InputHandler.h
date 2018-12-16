#pragma once
#include "../Type/OTypes.h"
#include "../CrossPlatform/CrossPlatform.h"
#include "Keys.h"
#include <thread>

namespace lun {
	class InputHandler {
		friend class Engine;
	public:
		//@return bool whether or not CODE_<key> is down
		bool isKeyDown(u8 handle);

		//@return bool whether or not CODE_<key> is up
		bool isKeyUp(u8 handle);

		//@return bool whether or not CODE_<key> is pressed (down for the first tick)
		bool isKeyPressed(u8 handle);

		//@return bool whether or not CODE_<key> is released (up for the first tick)
		bool isKeyReleased(u8 handle);


		//@return bool whether or not the mouse is down (0 = CODE_MOUSE_LEFT, 1 = CODE_MOUSE_RIGHT, 2 = CODE_MOUSE_MIDDLE, extra buttons >= 3)
		bool isMouseDown(u8 handle);

		//@return bool whether or not the mouse is up (0 = CODE_MOUSE_LEFT, 1 = CODE_MOUSE_RIGHT, 2 = CODE_MOUSE_MIDDLE, extra buttons >= 3)
		bool isMouseUp(u8 handle);

		//@return bool whether or not the mouse is pressed (down for 1 tick) (0 = CODE_MOUSE_LEFT, 1 = CODE_MOUSE_RIGHT, 2 = CODE_MOUSE_MIDDLE, extra buttons >= 3)
		bool isMousePressed(u8 handle);

		//@return bool whether or not the mouse is released (up for 1 tick) (0 = CODE_MOUSE_LEFT, 1 = CODE_MOUSE_RIGHT, 2 = CODE_MOUSE_MIDDLE, extra buttons >= 3)
		bool isMouseReleased(u8 handle);


		//Add delta x and y to the cursor position
		//@setter f32 cursorX, cursorY
		void addCursorPos(f32 x, f32 y);

		//@setter f32 cursorX, cursorY
		void setCursorPos(f32 x, f32 y);


		//@return f32 x, y; xMouseDelta & yMouseDelta
		void getCursorDelta(f32 &x, f32 &y);

		//@return f32 x, y; mouse position
		void getMousePos(f32 &x, f32 &y);


		//Update a mouse button to a state
		//@param u8 button (CODE_<key> of the pressed button)
		//@param bool state; pressed (true) or released (false0
		void updateMouse(u8 button, bool state);

		//Update a key to a state
		//@param u8 button (CODE_<key> of the pressed button)
		//@param bool state; pressed (true) or released (false0
		void updateKey(u8 key, bool state);

		//Replace the previous keys with current keys (update the key states)
		void update();

		//Convert platform dependent keycode to osomi keycode
		//@param u32 someCode; any value dependent on the current platform
		//On PC; GLFW, it converts things like GLFW_KEY_A to CODE_A
		static u8 getKeyCode(u32 someCode);

	protected:
		~InputHandler();

		#ifdef __DESKTOP__
			static InputHandler *create(GLFWwindow *w);
		#endif

		InputHandler();

		void forceMouse(f32 x, f32 y);

	private:
		bool currKeys[256], prevKeys[256];
		bool currMouse[8], prevMouse[8];

		f32 cursorX, cursorY;
		f32 deltaX, deltaY;

		f32 mouseX, mouseY;

		#ifdef __DESKTOP__
			GLFWwindow *w;
		#endif
	};
}