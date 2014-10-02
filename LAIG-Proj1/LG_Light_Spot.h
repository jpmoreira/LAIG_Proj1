#pragma once
#include "LG_Parsable_Node.h"
#include "LG_Primitive.h"


#define LG_SPOT_COMPONNENT_AMBIENT 0
#define LG_SPOT_COMPONNENT_DIFFUSE 1
#define LG_SPOT_COMPONNENT_SPECULAR 2

#define LG_SPOT_COMPONNENT_AMBIENT_STR "ambient"
#define LG_SPOT_COMPONNENT_DIFFUSE_STR "diffuse"
#define LG_SPOT_COMPONNENT_SPECULAR_STR "specular"
#define LG_SPOT_COMPONNENT_XML_TAG_NAME "componnent"


#define LG_SPOT_ATT_MARKER "marker"
#define LG_SPOT_ATT_ENABLED "enabled"
#define LG_SPOT_ATT_ID "id"
#define LG_SPOT_ATT_POS "pos"
#define LG_SPOT_ATT_TARGET "target"
#define LG_SPOT_ATT_ANGLE "angle"
#define LG_SPOT_ATT_EXPONENT "exponent"
#define LG_SPOT_COMPONNENT_ATT_TYPE "type"
#define LG_SPOT_COMPONNENT_ATT_VALUE "value"

class LG_Light_Spot :
	public LG_Parsable_Node
{
public:
	LG_Light_Spot(LG_Node_Map *map, TiXmlElement *element);
	~LG_Light_Spot();

private:
	void fillLightComponents(TiXmlElement *element);
	static int _LG_classIDNr;
	string id;
	bool enabled, marker;
	LG_Point3D pos, target;
	LG_LightArray componnents[3];
	double angle, exponent;
};

/* target = "ff ff ff"
	angle = "ff" 
	exponent = "ff"
	*/