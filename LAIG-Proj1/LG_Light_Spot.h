#pragma once
#include "LG_Light.h"


#define LG_SPOT_ATT_TARGET "target"
#define LG_SPOT_ATT_ANGLE "angle"
#define LG_SPOT_ATT_EXPONENT "exponent"


class LG_Light_Spot :
	public LG_Light
{
public:
	LG_Light_Spot(LG_Node_Map *map, TiXmlElement *element);
	LG_Light_Spot(LG_Node_Map *map, string element);
	~LG_Light_Spot();



	string getId();
	bool getMarker();
	bool getEnabled();
	const LG_Point3D_F &getPos();
	const LG_Point3D_F &getTarget();
	const LG_LightArray_f *getComponents();
	double getAngle();
	double getExponent();
	void draw();



private:
	void fillLightComponents(TiXmlElement *element);
	string id;
	bool enabled, marker;
	float pos[3], target[3];
	LG_LightArray_f components[3];
	double angle, exponent;
	CGFlight *my_light;
	unsigned int my_light_id;
};
