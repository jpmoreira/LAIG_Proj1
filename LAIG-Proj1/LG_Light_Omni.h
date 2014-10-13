#pragma once
#include "LG_Light.h"

class LG_Light_Omni :
	public LG_Light
{
public:
	LG_Light_Omni(LG_Node_Map *map, TiXmlElement *element);
	LG_Light_Omni(LG_Node_Map *map, string identifier);
	~LG_Light_Omni();

	string getId();
	bool getMarker();
	bool getEnabled();
	const LG_Point3D_F &getPos();
	const LG_LightArray_f *getComponents();

private:
	
	string id;
	bool enabled, marker;
	LG_Point3D_F pos;
	LG_LightArray_f components[3];
	CGFlight *my_light;
	unsigned int my_light_id;

	void fillLightComponents(TiXmlElement *element);

};