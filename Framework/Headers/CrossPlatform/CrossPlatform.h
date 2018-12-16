#pragma once

#ifdef _WIN32				//Windows
	#define __WINDOWS__
	#define __DESKTOP__
#elif __APPLE__				//Apple
	#include "TargetConditionals.h"
		#ifdef TARGET_OS_IPHONE				//iOS
		#define __IOS__
		#elif								//OS X
		#define __OSX__
		#define __DESKTOP__
		#endif
	#define __PHONE__
#elif __ANDROID				//Android
	#define __ANDROID__
	#define __PHONE__
#elif XBOXONE
	#define __XBONE__
	#define __CONSOLE__
#elif _PS4
	#define __PS4__
	#define __CONSOLE__
#else						//Linux
	#define __DESKTOP__
#endif

#ifdef __DESKTOP__
	#include <GL/glew.h>
	#include <GLFW/glfw3.h>
	#define __OGL__
#elif __PHONE__
	#define __OGL__
	#define __EGL__
#elif __CONSOLE__
	#define __OGL__
	#define __EGL__
#endif