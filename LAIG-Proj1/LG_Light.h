#pragma once
#include "LG_Parsable_Node.h"

#define LG_LIGHT_XML_TAG_NAME "light"
#define _LG_Light_NODE_ID "_LG_Light"

#define LG_LIGHT_ATT_TYPE "type"
#define LG_LIGHT_TYPE_OMNI "omni"
#define LG_LIGHT_TYPE_SPOT "spot"

#define LG_LIGHT_COMPONENT_AMBIENT 0
#define LG_LIGHT_COMPONENT_DIFFUSE 1
#define LG_LIGHT_COMPONENT_SPECULAR 2

#define LG_LIGHT_COMPONENT_AMBIENT_STR "ambient"
#define LG_LIGHT_COMPONENT_DIFFUSE_STR "diffuse"
#define LG_LIGHT_COMPONENT_SPECULAR_STR "specular"
#define LG_LIGHT_COMPONENT_XML_TAG_NAME "component"



#define LG_LIGHT_ATT_MARKER "marker"
#define LG_LIGHT_ATT_ENABLED "enabled"
#define LG_LIGHT_ATT_ID "id"
#define LG_LIGHT_ATT_POS "pos"
#define LG_LIGHT_COMPONENT_ATT_TYPE "type"
#define LG_LIGHT_COMPONENT_ATT_VALUE "value"



typedef enum{

	LG_LIGHT_OMNI,
	LG_LIGHT_SPOT,
	LG_LIGHT_INVALID
} LG_LIGHT_TYPE;

class LG_Light : public LG_Parsable_Node
{
public:
	LG_Light(LG_Node_Map *map, TiXmlElement *element);
	LG_Light(LG_Node_Map *map, TiXmlElement *element, string identifier);
	~LG_Light();
	
	LG_LIGHT_TYPE selectMyType(LG_Node_Map *map, TiXmlElement *element);
	void constructMyLights(LG_Node_Map *map, TiXmlElement *element);

	static string identifierForSuper(TiXmlElement *element);
	static LG_LIGHT_TYPE myLightType(TiXmlElement *element);

};
