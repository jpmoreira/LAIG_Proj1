#pragma once
#include "LG_Light_Spot.h"
#include "LG_Light_Omni.h"


#define LG_LIGHTS_CONTAINER_ID "LG_Lights_Container"
#define LG_LIGHTS_XML_TAG_NAME "lights"


class LG_Lights_Container :
	public LG_Parsable_Node
{
	friend class LG_SceneInterface;
private:
    LG_Node_Map *lightsMap;
public:
	LG_Lights_Container( TiXmlElement *element);
	~LG_Lights_Container();
	void draw(bool selectMode);
};

