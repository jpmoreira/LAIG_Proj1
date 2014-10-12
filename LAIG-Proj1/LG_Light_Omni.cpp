#include "LG_Light_Omni.h"




LG_Light_Omni::LG_Light_Omni(LG_Node_Map *map, TiXmlElement *element) : LG_Light(map, element, identifierForSuper(element))
{	
	string_tryToAttributeVariable(LG_LIGHT_ATT_ID, element, id);
	bool_tryToAttributeVariable(LG_LIGHT_ATT_ENABLED, element, enabled);
	bool_tryToAttributeVariable(LG_LIGHT_ATT_MARKER, element, marker);
	point3D_F_tryToAttributeVariable(LG_LIGHT_ATT_POS, element, pos);
	fillLightComponents(element);

	my_light = new CGFlight(my_light_id, pos);

}


LG_Light_Omni::~LG_Light_Omni()
{
}



void LG_Light_Omni::fillLightComponents(TiXmlElement *element){


	TiXmlElement *sub_elem;

	sub_elem = element->FirstChildElement(LG_LIGHT_COMPONENT_XML_TAG_NAME);


	if (!sub_elem)
		throw new LG_Parse_Exception_Missing_Element(new string(LG_LIGHT_COMPONENT_XML_TAG_NAME));

	while (sub_elem)
	{
		char *comp_type = (char *)sub_elem->Attribute(LG_LIGHT_COMPONENT_ATT_TYPE);

		if (comp_type)
		{
			if (str_eq(LG_LIGHT_COMPONENT_AMBIENT_STR, comp_type))
				lightArray_f_tryToAttributeVariable(LG_LIGHT_COMPONENT_ATT_VALUE, sub_elem, components[LG_LIGHT_COMPONENT_AMBIENT]);
			
			else if (str_eq(LG_LIGHT_COMPONENT_DIFFUSE_STR, comp_type))
				lightArray_f_tryToAttributeVariable(LG_LIGHT_COMPONENT_ATT_VALUE, sub_elem, components[LG_LIGHT_COMPONENT_DIFFUSE]);
		
			else if (str_eq(LG_LIGHT_COMPONENT_SPECULAR_STR, comp_type))
				lightArray_f_tryToAttributeVariable(LG_LIGHT_COMPONENT_ATT_VALUE, sub_elem, components[LG_LIGHT_COMPONENT_SPECULAR]);
			else
				throw new LG_Parse_Exception_Wrong_Attribute_Value(new string(LG_LIGHT_COMPONENT_ATT_VALUE), new string(LG_LIGHT_COMPONENT_ATT_VALUE), new string("WRONG DOUBLE"));

		}
	
		sub_elem = sub_elem->NextSiblingElement(LG_LIGHT_COMPONENT_XML_TAG_NAME);
	}
}


string LG_Light_Omni::getId(){
	return this->id;
}

bool LG_Light_Omni::getMarker(){
	return this->marker;
}

bool LG_Light_Omni::getEnabled(){
	return this->enabled;
}

const LG_Point3D_F & LG_Light_Omni::getPos(){
	return this->pos;
}

const LG_LightArray_f * LG_Light_Omni::getComponents(){
	return this->components;
}