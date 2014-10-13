#pragma once
#include "LG_Light.h"


#define LG_SPOT_ATT_TARGET "target"
#define LG_SPOT_ATT_ANGLE "angle"
#define LG_SPOT_ATT_EXPONENT "exponent"

#define LG_IS_SPOT_LIGHT 1 //opengl defined value for spot lights type


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
	void draw();
	void setMyGL_ID(unsigned int GL_ID);
	unsigned int getGL_ID();
	void fillLightComponents(TiXmlElement *element, LG_LightArray_f components[3]);


private:
	string id;
	bool enabled, marker;
	float exponent; //Only values in the range [0, 128] are accepted
	
};
