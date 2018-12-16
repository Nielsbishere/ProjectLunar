#pragma once
#include <vector>
#include <cstring>
#include <type_traits>

namespace lun
{
	template<typename Base>
	class PolyPoolAreaBase
	{
	public:
		virtual ~PolyPoolAreaBase() {}
		virtual std::size_t add(Base &element) = 0;
		virtual bool remove(std::size_t index) = 0;
		virtual Base &get(std::size_t index) = 0;

		template<typename F>
		inline void for_each(F function)
		{
			char *objArray = getObjects();
			bool *aliveArray = getAliveArray();
			std::size_t max = getSize();
			std::size_t elementSize = getElementSize();
			for (std::size_t i = 0; i < max; ++i)
			{
				if (aliveArray[i])
				{
					function(reinterpret_cast<Base&>(objArray[i*elementSize]));
				}
			}
		}
	private:
		virtual bool *getAliveArray() = 0;
		virtual char *getObjects() = 0;
		virtual std::size_t getElementSize() = 0;
		virtual std::size_t getSize() = 0;
	};

	template<typename Base, typename Child, class = typename std::enable_if<std::is_base_of<Base, Child>::value>::type>
	class PolyPoolAreaChild : public PolyPoolAreaBase<Base>
	{
	public:
		PolyPoolAreaChild()
		{
			aliveVector = std::vector<char>(0, false);
		}
		~PolyPoolAreaChild() {} //auto clears vectors
	public: //functions
		std::size_t add(Base &element) override
		{
			for (std::size_t i = 0; i < aliveVector.size(); ++i)
			{
				if (!aliveVector[i])
				{
					//call copy constructor
					objectVector[i] = Child((Child&)element);
					aliveVector[i] = true;
					return i;
				}
			}
			//else
			objectVector.push_back((Child&)element);
			aliveVector.push_back(true);
		}
		bool remove(std::size_t index) override
		{
			bool ret = aliveVector[index];
			aliveVector[index] = false;
			return ret;
		}
		Base &get(std::size_t index)
		{
			return (Base&)objectVector[index];
		}
	private: //functions
		bool *getAliveArray() override
		{
			return (bool*)aliveVector.data();
		}
		char *getObjects() override
		{
			return (char*)objectVector.data();
		}
		std::size_t getElementSize() override
		{
			return sizeof(Child);
		}
		std::size_t getSize() override
		{
			return objectVector.size();
		}
	private: //vars
		std::vector<char> aliveVector;
		std::vector<Child> objectVector;
	};

	struct PolyPoolIndex
	{
		std::size_t index;
		std::size_t type;
	};

	template<typename Base>
	class PolyPool
	{
	public: //container management
		PolyPool()
		{
			typeVectors = std::vector<PolyPoolAreaBase<Base>*>(0, nullptr);
		}
		~PolyPool()
		{
			for (PolyPoolAreaBase<Base> *it : typeVectors)
			{
				delete it;
			}
		}

		//gets element from the pool given a certain index
		template<typename T, class = typename std::enable_if<std::is_base_of<Base, T>::value>::type>
		T &get(std::size_t index)
		{
			return (T&)get(getIndex<T>(), index);
		}

		//gets element from the pool using the PoolIndex received from the "add" function
		Base &get(PolyPoolIndex index)
		{
			return get(index.type, index.index);
		}

		//gets element from the pool
		Base &get(std::size_t type, std::size_t index)
		{
			return typeVectors[type]->get(index);
		}

		//function that adds an element to the pool
		//returns index type that can be used to identify the object
		template<typename T, class = typename std::enable_if<std::is_base_of<Base, T>::value>::type>
		PolyPoolIndex add()
		{
			return add(T());
		}

		//function that adds an element to the pool
		//object specified will be places inside pool
		//returns index type that can be used to identify the object
		template<typename T, class = typename std::enable_if<std::is_base_of<Base, T>::value>::type>
		PolyPoolIndex add(T object)
		{
			//get type number
			std::size_t type = getIndex<T>();

			//check if the vector is big enough
			if (type >= typeVectors.size())
			{
				typeVectors.resize(type + 1);
			}

			//add vector if not created yet
			if (typeVectors[type] == nullptr)
			{
				typeVectors[type] = new PolyPoolAreaChild<Base, T>();
			}

			//add object to vector
			std::size_t retIndex = typeVectors[type]->add(object);
			PolyPoolIndex ret;
			ret.index = retIndex;
			ret.type = type;
			return ret;
		}

		//remove an element at an index and of a specific type
		template<typename T, class = typename std::enable_if<std::is_base_of<Base, T>::value>::type>
		bool remove(std::size_t index)
		{
			return remove(getIndex<T>(), index);
		}

		//remove an element using the return type gotten from the "add" function
		//PolyPoolIndex contains the type and index of an element, and is used to remove the element from the pool
		bool remove(PolyPoolIndex index)
		{
			return remove(index.type, index.index);
		}

		//
		bool remove(std::size_t type, std::size_t index)
		{
			typeVectors[type]->remove(index);
		}
	public: //functional
		template<typename F>
		inline void for_each(F function)
		{
			for (PolyPoolAreaBase<Base> *it : typeVectors)
			{
				if (it != nullptr)
				{
					it->for_each(function);
				}
			}
		}
	public: //type index
		static std::size_t typeIndex;
		template<typename T, class = typename std::enable_if<std::is_base_of<Base, T>::value>::type>
		static std::size_t getIndex()
		{
			const static std::size_t ret = typeIndex++;
			return ret;
		}
	private:
		std::vector<PolyPoolAreaBase<Base>*> typeVectors;
	};

	template<typename Base>
	std::size_t PolyPool<Base>::typeIndex = 0;
}