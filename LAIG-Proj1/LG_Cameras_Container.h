#pragma once
#include "LG_Parsable_Node.h"
#include "LG_Camera_Ortho.h"
#include "LG_Camera_Perspective.h"



#define LG_CAMERAS_TAG_ID "lg_cameras"
#define LG_CAMERAS_XML_TAG_NAME "cameras"
#define LG_CAMERAS_ATT_INITIAL "initial"


class LG_Cameras_Container :
	public LG_Parsable_Node
{
public:
	LG_Cameras_Container(LG_Node_Map *map, TiXmlElement *element);
	~LG_Cameras_Container();

	string getInitial();

private:
	string initial;
};

