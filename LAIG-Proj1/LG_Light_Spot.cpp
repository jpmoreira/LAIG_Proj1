#include "LG_Light_Spot.h"



LG_Light_Spot::LG_Light_Spot(LG_Node_Map *map, TiXmlElement *element) : LG_Light(map, element, identifierForSuper(element))
{
	
	string_tryToAttributeVariable(LG_LIGHT_ATT_ID, element, id);
	bool_tryToAttributeVariable(LG_LIGHT_ATT_ENABLED, element, enabled);
	bool_tryToAttributeVariable(LG_LIGHT_ATT_MARKER, element, marker);
	point3D_F_tryToAttributeVariable(LG_LIGHT_ATT_POS, element, pos);
	fillLightComponents(element);

	
	point3D_F_tryToAttributeVariable(LG_SPOT_ATT_TARGET, element, target);
	double_tryToAttributeVariable(LG_SPOT_ATT_ANGLE, element, angle);
	double_tryToAttributeVariable(LG_SPOT_ATT_EXPONENT, element, exponent);

	my_light_id = LG_Light::getLightsCount();
	LG_Light::increaseLightsCount();

	my_light = new CGFlight(GL_LIGHT6, pos, target);
	my_light->setAmbient(components[LG_LIGHT_COMPONENT_AMBIENT]);
	my_light->setDiffuse(components[LG_LIGHT_COMPONENT_DIFFUSE]);
	my_light->setSpecular(components[LG_LIGHT_COMPONENT_SPECULAR]);

	my_light->setAngle((float)angle);
	glLightf(my_light_id, GL_SPOT_EXPONENT, float(exponent));
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



string LG_Light_Spot::getId(){
	return this->id;
}

bool LG_Light_Spot::getMarker(){
	return this->marker;
}

bool LG_Light_Spot::getEnabled(){
	return this->enabled;
}

const LG_Point3D_F & LG_Light_Spot::getPos(){
	return this->pos;
}

const LG_Point3D_F & LG_Light_Spot::getTarget(){
	return this->target;
}

const LG_LightArray_f * LG_Light_Spot::getComponents(){
	return this->components;
}

double LG_Light_Spot::getAngle(){
	return angle;
}

double LG_Light_Spot::getExponent(){
	return this->exponent;
}

void LG_Light_Spot::draw()
{

	/*float posi[3];
	posi[0] = 3;
	posi[1] = 3;
	posi[2] = 3;
	CGFlight mylight2 = CGFlight(GL_LIGHT6, posi);*/ //testing purpose

	if (marker)
		my_light->draw();
	if (enabled)
		my_light->enable();
	else
		my_light->disable();

	//my_light->disable();
}