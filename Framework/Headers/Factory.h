#pragma once
#include <map>
#include <typeinfo>
#include <string>

namespace lun
{
	class FactoryCreatorBase
	{
	public:
		virtual ~FactoryCreatorBase(){}
		virtual void *create() = 0;
		virtual void *createPlacement(void *position) = 0;
		virtual void *clone(void *other) = 0;
		virtual unsigned int size() = 0;
	};

	template<typename T>
	class FactoryCreatorChild : public FactoryCreatorBase
	{
	public:
		void *create() override
		{
			return new T();
		}
		void *createPlacement(void *position) override
		{
			return new(position) T();
		}
		void *clone(void *other) override
		{
			T *t = (T*)other;
			return new T(*t);
		}
		unsigned int size() override
		{
			return sizeof(T);
		}
	};

	template<typename T>
	class FactoryCreatorChildPrototype : public FactoryCreatorBase
	{
		//private default constructor
		//FactoryCreatorChildPrototype()
		//{}
	public:
		FactoryCreatorChildPrototype(T *protoObject)
		{
			cloneObj = protoObject;
		}
		void *create() override
		{
			return new T(*cloneObj);
		}
		void *createPlacement(void *position) override
		{
			return new(position) T(*cloneObj);
		}
		void *clone(void *other) override
		{
			T *t = (T*)other;
			return new T(*t);
		}
		unsigned int size() override
		{
			return sizeof(T);
		}
	private:
		T *cloneObj;
	};


	//static factory
	class Factory
	{
	public:
		template<typename T>
		static T *create(std::string name)
		{
			return (T*)(*factoryData)[name]->create();
		}

		template<typename T>
		static T *clone(std::string name, void *cloned)
		{
			return (T*)(*factoryData)[name]->clone(cloned);
		}

		static unsigned int size(std::string name)
		{
			return (*factoryData)[name]->size();
		}

		static void regist(FactoryCreatorBase *creator, std::string name)
		{
			if (factoryData == nullptr)
			{
				factoryData = new std::map<std::string, FactoryCreatorBase*>();
			}
			(*factoryData)[name] = creator;
		}

	private:
		static std::map<std::string, FactoryCreatorBase*> *factoryData;
	};

}