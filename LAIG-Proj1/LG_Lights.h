#pragma once

#include "LG_Parsable_Node.h"
#include "LG_Light_Omni.h"
#include "LG_Light_Spot.h"


#define LG_LIGHTS_XML_TAG_NAME "lights"
#define LG_LIGHT_XML_TAG_NAME "light"
#define _LG_LIGHTS_NODE_ID "_LG_LIGHTS"

#define LG_LIGHT_ATT_TYPE "type"
#define LG_LIGHT_TYPE_OMNI "omni"
#define LG_LIGHT_TYPE_SPOT "spot"

class LG_Lights : LG_Parsable_Node
{
public:
	LG_Lights(LG_Node_Map *map, TiXmlElement *element);
	~LG_Lights();

	void selectMyType(LG_Node_Map *map, TiXmlElement *element);
};

