#include "LG_Light_Spot.h"



LG_Light_Spot::LG_Light_Spot(LG_Node_Map *map, TiXmlElement *element) : LG_Light(map, element, identifierForSuper(element))
{
	LG_Point3D_F pos, _target;
	LG_LightArray_f components[3];

	float tmp_angle;
	string_tryToAttributeVariable(LG_LIGHT_ATT_ID, element, id);
	bool_tryToAttributeVariable(LG_LIGHT_ATT_ENABLED, element, enabled);
	bool_tryToAttributeVariable(LG_LIGHT_ATT_MARKER, element, marker);
	point3D_F_tryToAttributeVariable(LG_LIGHT_ATT_POS, element, pos);
	fillLightComponents(element, components);
	
	point3D_F_tryToAttributeVariable(LG_SPOT_ATT_TARGET, element, _target);
	float_tryToAttributeVariable(LG_SPOT_ATT_ANGLE, element, tmp_angle);
	float_tryToAttributeVariable(LG_SPOT_ATT_EXPONENT, element, exponent);

	this->setAmbient(components[LG_LIGHT_COMPONENT_AMBIENT]);
	this->setDiffuse(components[LG_LIGHT_COMPONENT_DIFFUSE]);
	this->setSpecular(components[LG_LIGHT_COMPONENT_SPECULAR]);
	
	this->setAngle((float)tmp_angle);
		
	this->position[0] = pos[0];
	this->position[1] = pos[1];
	this->position[2] = pos[2];
	this->position[3] = LG_IS_SPOT_LIGHT;

	this->direction[0] = _target[0]; //-pos[0];
	this->direction[1] = _target[1]; //-pos[1];
	this->direction[2] = _target[2];// -pos[2];

	if (enabled)
		this->enable();
	else
	this->disable();
}


LG_Light_Spot::~LG_Light_Spot()
{
}



void LG_Light_Spot::fillLightComponents(TiXmlElement *element, LG_LightArray_f components[3]){


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


void LG_Light_Spot::draw()
{
	if (marker)
		this->CGFlight::draw();
	glLightf(my_GL_Id, GL_SPOT_EXPONENT, exponent);
}


unsigned int LG_Light_Spot::getGL_ID()
{
	return my_GL_Id;
}

void LG_Light_Spot::setMyGL_ID(unsigned int GL_ID)
{
	my_GL_Id = GL_ID;
}