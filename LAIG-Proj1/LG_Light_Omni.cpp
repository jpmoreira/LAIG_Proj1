#include "LG_Light_Omni.h"




LG_Light_Omni::LG_Light_Omni(LG_Node_Map *map, TiXmlElement *element) : LG_Light(map, element, identifierForSuper(element))
{	

	LG_Point3D_F pos;
	LG_LightArray_f components[3];
	string_tryToAttributeVariable(LG_LIGHT_ATT_ID, element, id_str);
	bool_tryToAttributeVariable(LG_LIGHT_ATT_ENABLED, element, enabled);
	bool_tryToAttributeVariable(LG_LIGHT_ATT_MARKER, element, marker);
	point3D_F_tryToAttributeVariable(LG_LIGHT_ATT_POS, element, pos);
	fillLightComponents(element, components);

	this->setAmbient(components[LG_LIGHT_COMPONENT_AMBIENT]);
	this->setDiffuse(components[LG_LIGHT_COMPONENT_DIFFUSE]);
	this->setSpecular(components[LG_LIGHT_COMPONENT_SPECULAR]);

	this->position[0] = pos[0];
	this->position[1] = pos[1];
	this->position[2] = pos[2];
	

	if (enabled)
		this->enable();
	else
		this->disable();


}


LG_Light_Omni::~LG_Light_Omni()
{
}

bool LG_Light_Omni::getMarker(){
	return this->marker;
}

bool LG_Light_Omni::getEnabled(){
	return this->enabled;
}


void LG_Light_Omni::draw()
{
	if (marker)
		this->CGFlight::draw();
	else
		this->CGFlight::update();
}