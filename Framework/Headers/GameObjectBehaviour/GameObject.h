#pragma once
#include <vector>
#include <string>
#include "Transform.h"
#include "../Reflection.h"

namespace lun {
	class Component;
	class World;

	struct ComponentHolder {
		Component *component = nullptr;
		std::string name = "";
	};

	class GameObject {
		friend class World;
	public:
		REFLECTION(GameObject) {
			EXPOSEVAR(GameObject, transform);
		}

		GameObject();
		GameObject(vec3 p);
		GameObject(vec3 p, vec3 r);
		GameObject(vec3 p, vec3 r, vec3 s);
		~GameObject();

		//start function, called when object is spawned
		void start();

		//update function, called each frame
		virtual void update(f32 deltaTime);

		//spawn an object into the world
		template<typename T>
		GameObject *spawnObject();

		//get the world pointer
		World *getWorld() { return world; }

		//get component with type T and name 'n'
		template<typename T>
		T *getComponent(std::string str) {
			for (auto it = components.begin(); it != components.end(); it++) {
				if (it->name == str && typeid(*it->component) == typeid(T))
					return dynamic_cast<T*>(it->component);
			}
			return nullptr;
		}

		//get first component with type T
		template<typename T>
		T *getComponent() {
			for (auto it = components.begin(); it != components.end(); it++) {
				if (typeid(*it->component) == typeid(T))
					return dynamic_cast<T*>(it->component);
			}
			return nullptr;
		}


		//other function to get a component by name
		Component *getComponent(std::string name);

		//add component
		void addComponent(Component *newComponent, std::string name = "");

		//check if component is there
		bool hasComponent(std::string name);

		//check if component with type exists
		template<typename T>
		bool hasComponent() {
			return getComponent<T>() != nullptr;
		}

		//add component with type
		template<typename T>
		T *addComponent(std::string name = "", bool afterSpawn = true) {
			ComponentHolder push;
			push.component = new T();
			push.name = name;
			components.push_back(push);
			push.component->attachOwner(this);
			if (afterSpawn)
			{
				push.component->start();
			}
			push.component->onAttach();
			return (T*)push.component;
		}

		//remove component
		void removeComponent(Component *component);
		void removeComponent(std::string name);
		template<typename T>
		void removeComponent() {
			for (auto it = components.begin(); it != components.end(); it++) {
				if (typeid(*it->component) == typeid(T)) {
					components.erase(it);
					return;
				}
			}
		}

		Transform &getTransform() { return transform; }
		mat4 getModelMatrix() { return transform.makeModelMatrix(); }

		void setStatic() { notDynamic = true; transform.setReadOnly(); }
		bool &isStatic() { return notDynamic; }
	private:
		World *world;
		Transform transform;
		std::vector<ComponentHolder> components;
		bool notDynamic;
	};
}