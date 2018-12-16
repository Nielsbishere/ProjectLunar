#include "../../Headers/CrossPlatform/Context.h"
#include "../../Headers/Helper/OGLHelper.h"
#include "../../Headers/Settings/Settings.h"
using namespace lun;

#ifdef __DESKTOP__

void err(int error, const char *desc) {
	printf("GLFW error %i: %s\n", error, desc);
}

Context *Context::create(std::string name) {
	glfwSetErrorCallback(err);

	if (!glfwInit()) {
		printf("Couldn't init context. GLFW init failed\n");
		return nullptr;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_MAXIMIZED, GL_TRUE);

	GLFWwindow *window = glfwCreateWindow(1920, 1080, name.c_str(), NULL, NULL);
	if (window == nullptr) {
		printf("Couldn't init context. glfwCreateWindow failed\n");
		return nullptr;
	}

	glfwMakeContextCurrent(window);
	#ifdef VSYNC
	glfwSwapInterval(1);
	#else
	glfwSwapInterval(0);
	#endif

	if (glewInit()) {
		printf("Couldn't init context. glewInit failed\n");
		return nullptr;
	}

	printf("Lunar Core intialized with OpenGL version %s\n", glGetString(GL_VERSION));

	OGLDefaults();

	Context *context = new Context();
	context->window = window;
	return context;
}

#endif

void Context::OGLDefaults() {
	OGLHelper::setCulling(true);
	OGLHelper::depth();
	OGLHelper::depthFunc(LESS);
	OGLHelper::clearColor(RGBA());
}
Context::Context() {}

Context::~Context() {
	#ifdef __DESKTOP__
	glfwSetWindowShouldClose(window, 1);
	#endif
}