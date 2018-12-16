#pragma once
#include "CrossPlatform.h"
#include <string>
namespace lun {
	class Context {
		friend class Engine;
	private:
		#ifdef __DESKTOP__
		GLFWwindow *window;
		#endif

		Context();
		~Context();

		static void OGLDefaults();

		static Context *create(std::string windowTitle);
	};
}