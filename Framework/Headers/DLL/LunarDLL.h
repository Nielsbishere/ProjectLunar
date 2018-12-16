#pragma once
#include <vector>
#include <string>

/*
LunarDLL

containts functions to load DLLs and functions in them at runtime.
also has functions to hotload DLLs.

is an interface on top of platform specific DLL loading functions.
*/

#define __WINDOWS__
#ifdef __WINDOWS__
#include <Windows.h>
#endif //__WINDOWS__

//macro that creates empty function pointer, able to be registered in a LibLoader
#define DLLFUNC(returnType, name, ...) extern returnType (* name)(__VA_ARGS__) = nullptr

namespace lun
{
	class LibLoader
	{
	private:
		struct LibFunc
		{
			std::string name;
			void *func;
		};
	public:
		LibLoader(const char *path)
		{
			dllPath = path;
			loaded = false;
		}
		~LibLoader()
		{
			unloadLib();
		}

		void load()
		{
			if (!loaded)
			{
				//load the DLL
				loadLib(dllPath.c_str());

				//load the function pointers of the registered functions
				for (int i = 0; i < functions.size(); ++i)
				{
					*((void**)functions[i].func) = getFunction(functions[i].name.c_str());
				}

				//set bool
				loaded = true;
				return;
			}
			printf("Lib from path \"%s\" could not be loaded!\n", dllPath.c_str());
		}

		void unload()
		{
			if (loaded)
			{
				//unload the DLL
				unloadLib();

				//set bool
				loaded = false;
				return;
			}
			printf("Lib from path \"%s\" has already been loaded!\n", dllPath.c_str());
		}

		//returns index of the function
		void registerFunction(void *funcPtr, std::string name)
		{
			LibFunc func;
			func.name = name;
			func.func = funcPtr;
			functions.push_back(func);
		}

		bool isLoaded()
		{
			return loaded;
		}
	private:
		//basic data
		std::vector<LibFunc> functions;
		std::string dllPath;
		bool loaded;

	private:
		void loadLib(const char *path)
		{
#ifdef __WINDOWS__
			libObj = LoadLibrary(path);
#endif //__WINDOWS__
		}

		void unloadLib()
		{
#ifdef __WINDOWS__
			FreeLibrary(libObj);
#endif //__WINDOWS__
		}

		void *getFunction(const char *functionName)
		{
#ifdef __WINDOWS__
			return GetProcAddress(libObj, functionName);
#endif //__WINDOWS__
		}

		//VARS
		//lib object
#ifdef __WINDOWS__
		HMODULE libObj;
#endif //__WINDOWS__
	};
}