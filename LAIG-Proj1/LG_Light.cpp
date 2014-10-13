#include "LG_Light.h"


LG_Light::LG_Light(LG_Node_Map *map, TiXmlElement *element) :LG_Parsable_Node(map, _LG_Light_NODE_ID){
	if (!str_eq(LG_LIGHT_XML_TAG_NAME, element->Value()))
		throw new LG_Parse_Exception_Wrong_Element_Name(new string(LG_LIGHT_XML_TAG_NAME), new string(element->Value()));
}


LG_Light::LG_Light(LG_Node_Map *map, TiXmlElement *element, string identifier) : LG_Parsable_Node(map, identifier)
{
	if (!str_eq(LG_LIGHT_XML_TAG_NAME, element->Value()))
		throw new LG_Parse_Exception_Wrong_Element_Name(new string(LG_LIGHT_XML_TAG_NAME), new string(element->Value()));
}

LG_Light::~LG_Light()
{
}

string LG_Light::identifierForSuper(TiXmlElement *element)
{
	string tmp;

	string_tryToAttributeVariable(LG_LIGHT_ATT_ID, element, tmp);

	return tmp;

}

LG_LIGHT_TYPE LG_Light::myLightType(TiXmlElement *element)
{
	string my_type;

	string_tryToAttributeVariable(LG_LIGHT_ATT_TYPE, element, my_type);

	if (str_eq(my_type.c_str(), LG_LIGHT_TYPE_OMNI))
		return LG_LIGHT_OMNI;
	else if (str_eq(my_type.c_str(), LG_LIGHT_TYPE_SPOT))
		return LG_LIGHT_SPOT;

	throw new LG_Parse_Exception_Wrong_Attribute_Value(LG_LIGHT_XML_TAG_NAME, LG_LIGHT_ATT_TYPE, my_type.c_str());
}

unsigned int LG_Light::lights_count = 0;

void LG_Light::increaseLightsCount()
{
	lights_count++;
}

unsigned int LG_Light::getLightsCount()
{
	return lights_count;
}