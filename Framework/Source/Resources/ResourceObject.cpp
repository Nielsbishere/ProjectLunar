#include "../../Headers/Resources/ResourceObject.h"
#include "../../Headers/Resources/Textures/Texture.h"
#include "../../Headers/Render/Renderer.h"
#include "../../Headers/Render/Shader.h"
#include "../../Headers/Render/Line/LineRenderer.h"
#include "../../Headers/Render/Line/Wireframe.h"
using namespace lun;

template<class T> std::string ResourceObject<T>::getPath() { return path; }
template<class T> std::string ResourceObject<T>::getName() { return name; }
template<class T> T *ResourceObject<T>::getResource() { return t; }
template<class T> ResourcePile *ResourceObject<T>::getParent() { return daddy; }

template<class T> ResourceObject<T>::ResourceObject(std::string p, std::string n, T *_t) : path(p), name(n), t(_t), refCount(1) {}

template<class T> u32 ResourceObject<T>::getRefCount() { return refCount; }

template<class T> bool ResourceObject<T>::destroy() {
	if (refCount <= 1) {
		refCount = 0;
		return true;
	}
	refCount--;
	return false;
}

template<class T> T *ResourceObject<T>::load() {
	refCount++;
	return t;
}

template<class T> ResourceObject<T>::~ResourceObject() {
	delete t;
}

template class ResourceObject<Texture>;
template class ResourceObject<Renderer>;
template class ResourceObject<Shader>;
template class ResourceObject<LineRenderer>;
template class ResourceObject<Wireframe>;