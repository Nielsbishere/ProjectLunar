#pragma once
#include "../Type/OTypes.h"
#include <string>
namespace lun {
	template<class T> class ResourceObject {
		friend class ResourcePile;

	public:

		//@return std::string path to resource
		std::string getPath();

		//@return std::string name of resource
		std::string getName();

		//@return T *t representation of resource
		T *getResource();

		//@return ResourcePile *parent of resource
		ResourcePile *getParent();

	protected:

		//Constructor
		ResourceObject(std::string p, std::string n, T *_t);

		//@return u32 reference count
		u32 getRefCount();

		//@return can be deleted
		bool destroy();

		//Load this resource if it has already been loaded before (increase ref count)
		T *load();

		//Deconstructor
		~ResourceObject();

	private:

		///Variables
		std::string path;
		std::string name;
		T *t;
		u32 refCount;

		///Parent
		ResourcePile *daddy;
	};
}