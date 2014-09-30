#pragma once
#include "LG_Parsable_Node.h"
#include "LG_Primitive.h"


typedef enum{
	LG_AXIS_X,
	LG_AXIS_Y,
	LG_AXIS_Z
} LG_AXIS;


#define LG_AXIS_X_STR "x"
#define LG_AXIS_Y_STR "y"
#define LG_AXIS_Z_STR "z"


#define LG_Camera_Ortho_XML_TAG_NAME "ortho"
#define LG_Camera_Ortho_XML_ATT_ID "id"
#define LG_Camera_Ortho_XML_ATT_NEAR "near"
#define LG_Camera_Ortho_XML_ATT_FAR "far"
#define LG_Camera_Ortho_XML_ATT_LEFT "left"
#define LG_Camera_Ortho_XML_ATT_RIGHT "right"
#define LG_Camera_Ortho_XML_ATT_TOP "top"
#define LG_Camera_Ortho_XML_ATT_BOTTOM "bottom"
#define LG_Camera_Ortho_XML_ATT_DIRECTION "direction"

class LG_Camera_Ortho :
	public LG_Parsable_Node
{
public:
	LG_Camera_Ortho(LG_Node_Map *map, TiXmlElement *element);
	~LG_Camera_Ortho();

	void verifyAttributesAndValues(TiXmlElement *element);
	void verifyElementName(TiXmlElement *element);
private:
	//<ortho id="ss" direction="ee" near="ff" far="ff" left="ff" right="ff" top="ff" bottom="ff" />
	string id;
	LG_AXIS direction;
	double near, far, left, right, top, bottom;
	static int _LG_classIDNr;
	

};

