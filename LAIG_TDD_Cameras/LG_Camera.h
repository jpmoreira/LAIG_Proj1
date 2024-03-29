#pragma once
#include "LG_Parsable_Node.h"

#define LG_Camera_XML_ATT_ID "id"
#define LG_Camera_XML_ATT_NEAR "near"
#define LG_Camera_XML_ATT_FAR "far"

#define LG_Camera_Perspective_XML_TAG_NAME "perspective"
#define LG_Camera_Ortho_XML_TAG_NAME "ortho"



class LG_Camera :
	public LG_Parsable_Node
{
public:
	LG_Camera(LG_Node_Map *map, TiXmlElement *element, string identifier);
	~LG_Camera();

	virtual string getId();
	double getNear();
	double getFar();
	static string identifierForSuper(TiXmlElement *element);

private:
	string id;
	//windows has defines for near and far, that's why we use _near and _far
	double _near, _far;
	
};

