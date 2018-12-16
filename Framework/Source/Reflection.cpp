#include "../Headers/Reflection.h"
#include "../Headers/API/rapidxml/rapidxml.h"
#include "../Headers/API/rapidxml/rapidxml_print.h"
#include <sstream>
#include <iostream>
#include <fstream>

using namespace reflo;

std::map<std::string, MetaClassObject> *Reflection::metaData = nullptr;

bool reflo::Reflection::reflect(std::string className, std::string variableName, std::string typeName, unsigned int offset, bool isComponent, std::string range)
{
	createIfNotThere(className);

	//load MetaClass
	MetaClassObject &mClass = (*metaData)[className];
	mClass.isComponent = isComponent;

	//create metaVarObject
	MetaVarObject mVar;
	mVar.className = className;
	mVar.typeName = typeName;
	mVar.varName = variableName;
	mVar.variableOffset = offset;
	mVar.range = range;

	//save var
	mClass.classMetaData[variableName] = mVar;

	return true;
}

MetaVarObject reflo::Reflection::getMeta(std::string className, std::string varName)
{
	return (*metaData)[className].classMetaData[varName];
}

std::string reflo::Reflection::collectReflectedData()
{
	if (metaData == nullptr) {
		return "NULL";
	}
	if (metaData->empty()) {
		return "NULL";
	}
	std::string ret;
	//base of the xml file
	char xmlbase[] = "<?xml version=\"1.0\" encoding=\"latin-1\"?>";

	using namespace rapidxml;
	//xml document object
	xml_document<> doc;
	doc.parse<0>(xmlbase);
	xml_node<> *base = doc.allocate_node(node_element, "reflection");
	doc.append_node(base);

	auto data = *metaData;

	//read data into xml file
	auto &exportData = *metaData;
	for (auto it = exportData.begin(); it != exportData.end(); it++) {

		xml_node<> *classNode = doc.allocate_node(node_element, doc.allocate_string(it->first.c_str()));
		std::string isCompString;
		if (it->second.isComponent)
		{
			isCompString = "true";
		}
		else
		{
			isCompString = "false";
		}
		//add bool "isComponent" to class node, add "variables" node to class node to put variables in, add "parent" node to store parent name
		xml_node<> *varIsComponent = doc.allocate_node(node_element, "isComponent", doc.allocate_string(isCompString.c_str()));
		xml_node<> *classVarList = doc.allocate_node(node_element, "variables", doc.allocate_string(isCompString.c_str()));
		xml_node<> *classParent = doc.allocate_node(node_element, "parent", doc.allocate_string(it->second.parentName.c_str()));
		classNode->insert_node(nullptr, varIsComponent);
		classNode->insert_node(nullptr, classVarList);
		classNode->insert_node(nullptr, classParent);

		for (auto varIt = it->second.classMetaData.begin(); varIt != it->second.classMetaData.end(); varIt++) {
			//make variable node
			xml_node<> *varNode = doc.allocate_node(node_element, doc.allocate_string(varIt->second.varName.c_str()));

			//add variable data to append to varNode
			xml_node<> *varTypeNode = doc.allocate_node(node_element, "type", doc.allocate_string(varIt->second.typeName.c_str()));
			std::string unsNum = std::to_string(varIt->second.variableOffset);
			xml_node<> *varOffset = doc.allocate_node(node_element, "offset", doc.allocate_string(unsNum.c_str()));

			//insert vars to varNode
			varNode->insert_node(nullptr, varTypeNode);
			varNode->insert_node(nullptr, varOffset);

			//insert varNode to classNode
			classVarList->insert_node(nullptr, varNode);
		}
		//doc.append_node(classNode);
		base->append_node(classNode);
	}

	//save xml file to string
	std::stringstream xmlReturn;
	xmlReturn << *doc.first_node();
	ret = xmlReturn.str();
	return ret;
}

void reflo::Reflection::exportReflectionData(std::string path)
{
	std::ofstream out(path, std::ios::out);
	if (!out.good()) {
		printf("Couldn't open file \"%s\"\n", path.c_str());
		return;
	}
	std::string refl = collectReflectedData();
	int test = 0;
	out << refl;
	out.close();
}

void reflo::Reflection::setClassParent(std::string className, std::string parentName)
{
	createIfNotThere(className);
	(*metaData)[className].parentName = parentName;
}

void reflo::Reflection::setIsClassComponent(std::string className, bool isComponent)
{
	createIfNotThere(className);
	(*metaData)[className].isComponent = isComponent;
}

void reflo::Reflection::createIfNotThere(std::string className)
{
	bool createMetaClass = false;

	//create the metadata datastructure if it hasnt been created already
	if (metaData == nullptr) {
		metaData = new std::map<std::string, MetaClassObject>();
		createMetaClass = true;
	}

	//check if metaclass already exists
	if (!createMetaClass)
	{
		if ((*metaData).find(className) == (*metaData).end())
		{
			//not found
			createMetaClass = true;
		}
	}

	//if metaclass does not exist, create it
	if (createMetaClass)
	{
		MetaClassObject c = MetaClassObject();
		c.className = className;
		(*metaData)[className] = c;
	}
}
