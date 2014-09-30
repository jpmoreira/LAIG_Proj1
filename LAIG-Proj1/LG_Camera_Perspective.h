#pragma once


//class LG_Lighting : public LG_Parsable_Node{

#include "LG_Parsable_Node.h"
#include "LG_Primitive.h"


/*
Problem: element cameras must have a default camera set, with its id 
*/


#define LG_Camera_Perspective_Node_ID "perspective" //useless
#define LG_Camera_Perspective_XML_TAG_NAME "perspective"

#define LG_Camera_Perspective_XML_ATT_ID "id"
#define LG_Camera_Perspective_XML_ATT_NEAR "near"
#define LG_Camera_Perspective_XML_ATT_FAR "far"
#define LG_Camera_Perspective_XML_ATT_ANGLE "angle"
#define LG_Camera_Perspective_XML_ATT_POS "pos"
#define LG_Camera_Perspective_XML_ATT_TARGET "target"


class LG_Camera_Perspective : public LG_Parsable_Node
{
public:
	LG_Camera_Perspective(LG_Node_Map *map, TiXmlElement *element);
	~LG_Camera_Perspective();

	void verifyElementName(TiXmlElement *element);
	void verifyAttributesAndValues(TiXmlElement* element);
private:
	string id;
	double near, far, angle;
	LG_Point3D pos, target;

	static int _LG_classIDNr;
};

