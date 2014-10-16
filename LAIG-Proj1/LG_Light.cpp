#include "LG_Light.h"

unsigned int LG_Light::lights_count = 0;

LG_Light::LG_Light(LG_Node_Map *map, TiXmlElement *element) :LG_Parsable_Node(map, _LG_Light_NODE_ID), CGFlight(myGL_LIGHT(), initial){
	if (!str_eq(LG_LIGHT_XML_TAG_NAME, element->Value()))
		throw new LG_Parse_Exception_Wrong_Element_Name(new string(LG_LIGHT_XML_TAG_NAME), new string(element->Value()));
	increaseLightsCount();
}


LG_Light::LG_Light(LG_Node_Map *map, TiXmlElement *element, string identifier) : LG_Parsable_Node(map, identifier), CGFlight(myGL_LIGHT(), initial)
{
	if (!str_eq(LG_LIGHT_XML_TAG_NAME, element->Value()))
		throw new LG_Parse_Exception_Wrong_Element_Name(new string(LG_LIGHT_XML_TAG_NAME), new string(element->Value()));
	increaseLightsCount();
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

float LG_Light::initial[3] = {0, 0, 0};

void LG_Light::increaseLightsCount()
{
	lights_count++;
}

unsigned int LG_Light::getLightsCount()
{
	return lights_count;
}

unsigned int LG_Light::myGL_LIGHT()
{
	switch (lights_count)
	{
	case 0:

		return GL_LIGHT0;
	case 1:

		return GL_LIGHT1;
	case 2:
		
		return GL_LIGHT2;
	case 3:
		
		return GL_LIGHT3;
	case 4:
		
		return GL_LIGHT4;
	case 5:
		
		return GL_LIGHT5;
	case 6:
		
		return GL_LIGHT6;
	case 7:
		
		return GL_LIGHT7;
	}

	return GL_MAX_LIGHTS;
}


void LG_Light::fillLightComponents(TiXmlElement *element, LG_LightArray_f components[3]){


	TiXmlElement *sub_elem;

	bool ambient_set, diffuse_set, specular_set;
	ambient_set = diffuse_set = specular_set = false;

	sub_elem = element->FirstChildElement(LG_LIGHT_COMPONENT_XML_TAG_NAME);

	if (!sub_elem)
		throw new LG_Parse_Exception_Missing_Element(new string(LG_LIGHT_COMPONENT_XML_TAG_NAME));

	while (sub_elem)
	{
		char *comp_type = (char *)sub_elem->Attribute(LG_LIGHT_COMPONENT_ATT_TYPE);

		if (comp_type)
		{
			if (str_eq(LG_LIGHT_COMPONENT_AMBIENT_STR, comp_type))
			{
				lightArray_f_tryToAttributeVariable(LG_LIGHT_COMPONENT_ATT_VALUE, sub_elem, components[LG_LIGHT_COMPONENT_AMBIENT]);
				ambient_set = true;
			}
			else if (str_eq(LG_LIGHT_COMPONENT_DIFFUSE_STR, comp_type))
			{
				lightArray_f_tryToAttributeVariable(LG_LIGHT_COMPONENT_ATT_VALUE, sub_elem, components[LG_LIGHT_COMPONENT_DIFFUSE]);
				diffuse_set = true;
			}
			else if (str_eq(LG_LIGHT_COMPONENT_SPECULAR_STR, comp_type))
			{
				lightArray_f_tryToAttributeVariable(LG_LIGHT_COMPONENT_ATT_VALUE, sub_elem, components[LG_LIGHT_COMPONENT_SPECULAR]);
				specular_set = true;
			}
			else
				throw new LG_Parse_Exception_Wrong_Attribute_Value(new string(LG_LIGHT_COMPONENT_ATT_VALUE), new string(LG_LIGHT_COMPONENT_ATT_VALUE), new string("WRONG DOUBLE"));
		}

		sub_elem = sub_elem->NextSiblingElement(LG_LIGHT_COMPONENT_XML_TAG_NAME);
	}

	if (!(ambient_set && diffuse_set && specular_set))
		if (!ambient_set)
			throw new LG_Parse_Exception_Missing_Element(new string(LG_LIGHT_COMPONENT_AMBIENT_STR));
		else if (!diffuse_set)
			throw new LG_Parse_Exception_Missing_Element(new string(LG_LIGHT_COMPONENT_DIFFUSE_STR));
		else if (!specular_set)
			throw new LG_Parse_Exception_Missing_Element(new string(LG_LIGHT_COMPONENT_SPECULAR_STR));

}

string LG_Light::getName()
{
	return id_str;
}

unsigned int LG_Light::getGL_LIGHTID()
{
	return id;
}

bool LG_Light::isEnabled()
{
	return enabled;
}