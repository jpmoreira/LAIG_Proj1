#pragma once


//class LG_Lighting : public LG_Parsable_Node{

#include "LG_Parsable_Node.h"


/*
Problem: element cameras must have a default camera set, with its id 
*/

#define LG_Perspective_Node_ID "perspective" //useless
#define LG_PERSPECTIVE_XML_TAG_NAME "perspective"
#define LG_ORTHO_XML_TAG_NAME "ortho"

#define LG_PERSPECTIVE_XML_ATT_ID "id"
#define LG_PERSPECTIVE_XML_ATT_NEAR "near"
#define LG_PERSPECTIVE_XML_ATT_FAR "far"
#define LG_PERSPECTIVE_XML_ATT_ANGLE "angle"
#define LG_PERSPECTIVE_XML_ATT_POS "pos"
#define LG_PERSPECTIVE_XML_ATT_TARGET "target"


class LG_Perspective : public LG_Parsable_Node
{
public:
	LG_Perspective(LG_Node_Map *map, TiXmlElement *element);
	~LG_Perspective();

	void verifyElementName(TiXmlElement *element);
	void verifyAttributesAndValues(TiXmlElement* element);
private:
	string id;
	double near, far, angle, pos[3], target[3];

};

