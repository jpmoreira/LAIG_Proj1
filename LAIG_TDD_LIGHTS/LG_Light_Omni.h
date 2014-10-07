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
	const LG_Point3D &getPos();
	const LG_LightArray *getComponents();

private:
	
	string id;
	bool enabled, marker;
	LG_Point3D pos;
	LG_LightArray components[3];

	void fillLightComponents(TiXmlElement *element);

};