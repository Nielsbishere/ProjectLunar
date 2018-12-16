#pragma once

#include <map>
#include <string>
#include <typeinfo>
#include "GameObjectBehaviour/Component.h"
#include "Factory.h"

namespace reflo {

	struct MetaVarObject {
		std::string className;
		std::string varName;
		std::string typeName;
		unsigned int variableOffset;
		std::string range;
	};

	struct MetaClassObject {
		std::string className;
		std::string parentName = "NULL";
		bool isComponent;
		std::map<std::string, MetaVarObject> classMetaData;
	};

	class Reflection
	{
	public:
		//register an object in the reflection class
		static bool reflect(std::string className, std::string variableName, std::string typeName, unsigned int offset, bool isComponent, std::string range = "");

		//get the MetaObject of a variable
		static MetaVarObject getMeta(std::string className, std::string varName);

		//get a variable of an object by using the class name and variable name
		template<typename T>
		static T *getVariable(void *object, std::string className, std::string variableName);

		//put reflection data into a string
		static std::string collectReflectedData();

		//save reflection data to a file
		static void exportReflectionData(std::string path);

		//misc functions
		template<typename T, typename U> static constexpr size_t offsetOf(U T::*member) {
			return (char*)&((T*)nullptr->*member) - (char*)nullptr;
		}
		template<typename T, typename U> static std::string getType(U T::*member) {
			return typeid(U).name();
		}

		//setters
		static void setClassParent(std::string className, std::string parentName);
		static void setIsClassComponent(std::string className, bool isComponent);

	private:
		static std::map<std::string, MetaClassObject> *metaData;

		static void createIfNotThere(std::string className);
	};

	template<typename T>
	inline T * Reflection::getVariable(void * object, std::string className, std::string variableName)
	{
		MetaVarObject &metaRef = (*metaData)[className].classMetaData[variableName];
		return (T*)((char*)object + metaRef.variableOffset);
	}
}

/* OLD
#define REFLECT(classT, variableT, typeT, offset) static bool classT ## _ ## variableT ## _ref = reflo::Reflection::reflect(# classT, # variableT, typeT, offset)
#define EXPOSE(classT, variableT) REFLECT(classT, variableT, reflo::Reflection::getType(& ## classT ## :: ## variableT), (unsigned int)reflo::Reflection::offsetOf(& ## classT ## :: ## variableT))

#define REFLECT2(classT, variableT, typeT, offset) reflo::Reflection::reflect(# classT, # variableT, typeT, offset)
#define EXPOSEVAR(classT, variableT) REFLECT2(classT, variableT, reflo::Reflection::getType(& ## classT ## :: ## variableT), (unsigned int)reflo::Reflection::offsetOf(& ## classT ## :: ## variableT))

#define REFLECTION(className) static void _ ## className ## _reflection()
#define REFLECT_CLASS(className) \
static bool _ ## className ## _reflect_ref_function() {\
	className ## ::_ ## className ## _reflection();\
	return true;\
}\
static bool _ ## className ## _reflectstatic = _ ## className ## _reflect_ref_function()
*/

#define REFLECT(classT, variableT, typeT, offset) static bool classT ## _ ## variableT ## _ref = reflo::Reflection::reflect(# classT, # variableT, typeT, offset)
#define EXPOSE(classT, variableT) REFLECT(classT, variableT, reflo::Reflection::getType(& ## classT ## :: ## variableT), (unsigned int)reflo::Reflection::offsetOf(& ## classT ## :: ## variableT))

#define REFLECT2(classT, variableT, typeT, offset) reflo::Reflection::reflect(# classT, # variableT, typeT, offset, std::is_base_of<lun::Component,classT>::value)
#define EXPOSEVAR(classT, variableT) REFLECT2(classT, variableT, reflo::Reflection::getType(& ## classT ## :: ## variableT), (unsigned int)reflo::Reflection::offsetOf(& ## classT ## :: ## variableT))
#define EXPOSEPARENT(classT, parentT) reflo::Reflection::setClassParent(# classT, # parentT)

#define REFLECTION(className) static void _ ## className ## _reflection()
#define REFLECT_CLASS(className) \
static bool _ ## className ## _reflect_ref_function() {\
	lun::Factory::regist(new lun::FactoryCreatorChild<className>, # className);\
	reflo::Reflection::setIsClassComponent(# className, std::is_base_of<lun::Component,className>::value);\
	className ## ::_ ## className ## _reflection();\
	return true;\
}\
static bool _ ## className ## _reflectstatic = _ ## className ## _reflect_ref_function()

#define REFLECT_CLASS_NOFACTORY(className) \
static bool _ ## className ## _reflect_ref_function() {\
	reflo::Reflection::setIsClassComponent(# className, std::is_base_of<lun::Component,className>::value);\
	className ## ::_ ## className ## _reflection();\
	return true;\
}\
static bool _ ## className ## _reflectstatic = _ ## className ## _reflect_ref_function()

/*

HOW TO USE REFLECTION	

in the class declaration, use the REFLECTION function and add the variables you want to reflect:
	
	>SomeClass.h
class SomeClass
{
public:
	REFLECTION(SomeClass)
	{
		EXPOSE(SomeClass, privateVar);
	}

private:
	float privateVar;
}


then, in the cpp file, you need to specifie that you want to reflect the class:

	>SomeClass.cpp
REFLECT_CLASS(SomeClass);

*/