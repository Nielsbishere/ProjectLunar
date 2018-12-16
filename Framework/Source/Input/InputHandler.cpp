#include "../../Headers/Input/InputHandler.h"
#include "../../Headers/Engine.h"
using namespace lun;

InputHandler::~InputHandler() {}
InputHandler::InputHandler() {
	for (u32 i = 0; i < 256; ++i)
		currKeys[i] = prevKeys[i] = false;
	for (u32 i = 0; i < 8; ++i)
		currMouse[i] = prevMouse[i] = false;
	cursorX = cursorY = 0;
	mouseX = mouseY = 0;
}

#ifdef __DESKTOP__
void key(GLFWwindow* window, int key, int scancode, int action, int mods) {
	InputHandler *ih = ((Engine*)glfwGetWindowUserPointer(window))->getInput();
	ih->updateKey(InputHandler::getKeyCode(key), action != GLFW_RELEASE);
}

void mouse(GLFWwindow* window, int button, int action, int mods) {
	InputHandler *ih = ((Engine*)glfwGetWindowUserPointer(window))->getInput();
	ih->updateMouse(button, action == GLFW_PRESS);
}

void cursor(GLFWwindow* window, double xpos, double ypos) {
	InputHandler *ih = ((Engine*)glfwGetWindowUserPointer(window))->getInput();
	ih->setCursorPos((f32)xpos, (f32)ypos);
}

InputHandler *InputHandler::create(GLFWwindow *w) {
	InputHandler *ih = new InputHandler();
	ih->w = w;
	glfwSetKeyCallback(w, key);
	glfwSetMouseButtonCallback(w, mouse);
	glfwSetCursorPosCallback(w, cursor);
	glfwSetInputMode(w, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	return ih;
}
#endif

void InputHandler::update() {
	Engine *e = (Engine*)glfwGetWindowUserPointer(this->w);

	for (u32 i = 0; i < 256; ++i)
		prevKeys[i] = currKeys[i];

	for (u32 i = 0; i < 8; ++i)
		prevMouse[i] = currMouse[i];

	f32 halfwit = e->getWidth() / 2.f, halfhit = e->getHeight() / 2.f;
	deltaX = cursorX - halfwit;
	deltaY = cursorY - halfhit;
	forceMouse(halfwit, halfhit);
	mouseX += deltaX, mouseY += deltaY;
}

void InputHandler::forceMouse(f32 mx, f32 my) {
	#ifdef __DESKTOP__
	glfwSetCursorPos(w, mx, my);
	cursorX = mx, cursorY = my;
	#endif
}

bool InputHandler::isKeyDown(u8 handle) { return currKeys[handle]; }
bool InputHandler::isKeyUp(u8 handle) { return !currKeys[handle]; }
bool InputHandler::isKeyPressed(u8 handle) { return currKeys[handle] && !prevKeys[handle]; }
bool InputHandler::isKeyReleased(u8 handle) { return !currKeys[handle] && prevKeys[handle]; }

bool InputHandler::isMouseDown(u8 handle) { return currMouse[handle]; }
bool InputHandler::isMouseUp(u8 handle) { return !currMouse[handle]; }
bool InputHandler::isMousePressed(u8 handle) { return currMouse[handle] && !prevMouse[handle]; }
bool InputHandler::isMouseReleased(u8 handle) { return !currMouse[handle] && prevMouse[handle]; }

void InputHandler::addCursorPos(f32 x, f32 y) { cursorX += x; cursorY += y; }
void InputHandler::setCursorPos(f32 x, f32 y) { cursorX = x; cursorY = y; }

void InputHandler::getCursorDelta(f32 &x, f32 &y) { x = deltaX, y = deltaY; }
void InputHandler::getMousePos(f32 &x, f32 &y) { x = mouseX; y = mouseY; }

void InputHandler::updateMouse(u8 button, bool state) { currMouse[button] = state; }
void InputHandler::updateKey(u8 key, bool state) { currKeys[key] = state; }

#ifdef __DESKTOP__
u8 InputHandler::getKeyCode(u32 someCode) {
	if (someCode >= GLFW_KEY_A && someCode <= GLFW_KEY_Z)return CODE_A + (someCode - GLFW_KEY_A);
	if (someCode >= GLFW_KEY_0 && someCode <= GLFW_KEY_9)return CODE_0 + (someCode - GLFW_KEY_0);
	if (someCode >= GLFW_KEY_F1 && someCode <= GLFW_KEY_F24)return CODE_F1 + (someCode - GLFW_KEY_F1);
	if (someCode >= GLFW_KEY_KP_0 && someCode <= GLFW_KEY_KP_9)return CODE_KP0 + (someCode - GLFW_KEY_KP_0);
	switch (someCode) {
		case GLFW_KEY_UP: return CODE_UP;
		case GLFW_KEY_DOWN: return CODE_DOWN;
		case GLFW_KEY_LEFT: return CODE_LEFT;
		case GLFW_KEY_RIGHT: return CODE_RIGHT;
		case GLFW_KEY_SPACE: return CODE_SPACE;
		case GLFW_KEY_ESCAPE: return CODE_ESC;
		case GLFW_KEY_NUM_LOCK: return CODE_NUMLCK;
		case GLFW_KEY_CAPS_LOCK: return CODE_CAPS;
		case GLFW_KEY_SCROLL_LOCK: return CODE_SCRLLCK;
		case GLFW_KEY_LEFT_ALT: return CODE_LALT;
		case GLFW_KEY_RIGHT_ALT: return CODE_RALT;
		case GLFW_KEY_LEFT_SHIFT: return CODE_LSHIFT;
		case GLFW_KEY_RIGHT_SHIFT: return CODE_RSHIFT;
		case GLFW_KEY_LEFT_CONTROL: return CODE_LCTRL;
		case GLFW_KEY_RIGHT_CONTROL: return CODE_RCTRL;
		case GLFW_KEY_TAB: return CODE_TAB;
		case GLFW_KEY_ENTER: return CODE_ENTER;
		case GLFW_KEY_BACKSPACE: return CODE_BACKSPACE;
		case GLFW_KEY_PAGE_DOWN: return CODE_PAGEDOWN;
		case GLFW_KEY_PAGE_UP: return CODE_PAGEUP;
		case GLFW_KEY_HOME: return CODE_HOME;
		case GLFW_KEY_END: return CODE_END;
		case GLFW_KEY_INSERT: return CODE_INSERT;
		case GLFW_KEY_DELETE: return CODE_DELETE;
		case GLFW_KEY_MINUS: return CODE_MINUS;
		case GLFW_KEY_EQUAL: return CODE_EQUALS;
		case GLFW_KEY_LEFT_BRACKET: return CODE_LBRACE;
		case GLFW_KEY_RIGHT_BRACKET: return CODE_RBRACE;
		case GLFW_KEY_SEMICOLON: return CODE_SEMICOLON;
		case GLFW_KEY_APOSTROPHE: return CODE_APOSTROPHE;
		case GLFW_KEY_GRAVE_ACCENT: return CODE_TILDE;
		case GLFW_KEY_BACKSLASH: return CODE_BACKSLASH;
		case GLFW_KEY_COMMA: return CODE_COMMA;
		case GLFW_KEY_PERIOD: return CODE_DOT;
		case GLFW_KEY_SLASH: return CODE_SLASH;
		case GLFW_KEY_KP_DIVIDE: return CODE_KPSLASH;
		case GLFW_KEY_KP_MULTIPLY: return CODE_KPSTAR;
		case GLFW_KEY_KP_SUBTRACT: return CODE_KPMINUS;
		case GLFW_KEY_KP_ADD: return CODE_KPPLUS;
		case GLFW_KEY_KP_DECIMAL: return CODE_KPDOT;
		case GLFW_KEY_KP_ENTER: return CODE_KPENTER;
		default: return CODE_UNDEF;
	}
}
#endif