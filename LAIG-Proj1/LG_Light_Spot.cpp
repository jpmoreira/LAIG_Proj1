#include "LG_Light_Spot.h"



LG_Light_Spot::LG_Light_Spot(LG_Node_Map *map, TiXmlElement *element) : LG_Light(map, element, identifierForSuper(element))
{
	
	bool_tryToAttributeVariable(LG_LIGHT_ATT_ENABLED, element, enabled);
	bool_tryToAttributeVariable(LG_LIGHT_ATT_MARKER, element, marker);
	point3D_tryToAttributeVariable(LG_LIGHT_ATT_POS, element, pos);
	fillLightComponents(element);

	point3D_tryToAttributeVariable(LG_SPOT_ATT_TARGET, element, target);
	double_tryToAttributeVariable(LG_SPOT_ATT_ANGLE, element, angle);
	double_tryToAttributeVariable(LG_SPOT_ATT_EXPONENT, element, exponent);
}


LG_Light_Spot::~LG_Light_Spot()
{
}



void LG_Light_Spot::fillLightComponents(TiXmlElement *element){


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
				lightArray_tryToAttributeVariable(LG_LIGHT_COMPONENT_ATT_VALUE, sub_elem, components[LG_LIGHT_COMPONENT_AMBIENT]);

			else if (str_eq(LG_LIGHT_COMPONENT_DIFFUSE_STR, comp_type))
				lightArray_tryToAttributeVariable(LG_LIGHT_COMPONENT_ATT_VALUE, sub_elem, components[LG_LIGHT_COMPONENT_DIFFUSE]);

			else if (str_eq(LG_LIGHT_COMPONENT_SPECULAR_STR, comp_type))
				lightArray_tryToAttributeVariable(LG_LIGHT_COMPONENT_ATT_VALUE, sub_elem, components[LG_LIGHT_COMPONENT_SPECULAR]);
			else 
				throw new LG_Parse_Exception_Wrong_Attribute_Value(new string(LG_LIGHT_COMPONENT_ATT_VALUE), new string(LG_LIGHT_COMPONENT_ATT_VALUE), new string("WRONG DOUBLE"));
		}

		sub_elem = sub_elem->NextSiblingElement(LG_LIGHT_COMPONENT_XML_TAG_NAME);
	}
}


#pragma mark - Getters & Setters

bool LG_Light_Spot::getMarker(){
	return this->marker;
}

bool LG_Light_Spot::getEnabled(){
	return this->enabled;
}

const LG_Point3D & LG_Light_Spot::getPos(){
	return this->pos;
}

const LG_Point3D & LG_Light_Spot::getTarget(){
	return this->target;
}

const LG_LightArray * LG_Light_Spot::getComponents(){
	return this->components;
}

double LG_Light_Spot::getAngle(){
	return angle;
}

double LG_Light_Spot::getExponent(){
	return this->exponent;
}

