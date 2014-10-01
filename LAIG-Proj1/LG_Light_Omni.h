#pragma once
#include "LG_Parsable_Node.h"
#include "LG_Primitive.h"

#define LG_OMNI_COMPONNENT_AMBIENT 0
#define LG_OMNI_COMPONNENT_DIFFUSE 1
#define LG_OMNI_COMPONNENT_SPECULAR 2

#define LG_OMNI_COMPONNENT_AMBIENT_STR "ambient"
#define LG_OMNI_COMPONNENT_DIFFUSE_STR "diffuse"
#define LG_OMNI_COMPONNENT_SPECULAR_STR "specular"
#define LG_OMNI_COMPONNENT_XML_TAG_NAME "componnent"


#define LG_OMNI_ATT_MARKER "marker"
#define LG_OMNI_ATT_ENABLED "enabled"
#define LG_OMNI_ATT_ID "id"
#define LG_OMNI_ATT_POS "pos"
#define LG_OMNI_COMPONNENT_ATT_TYPE "type"
#define LG_OMNI_COMPONNENT_ATT_VALUE "value"



class LG_Light_Omni :
	public LG_Parsable_Node
{
public:
	LG_Light_Omni(LG_Node_Map *map, TiXmlElement *element);
	~LG_Light_Omni();

private:
	static int _LG_classIDNr;
	string id;
	bool enabled, marker;
	LG_Point3D pos;
	LG_LightArray componnents[3];

	void fillLightComponents(TiXmlElement *element);

};

