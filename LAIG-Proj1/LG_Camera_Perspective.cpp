#include "LG_Camera_Perspective.h"

#define _LG_Primitive_Name LG_Camera_Perspective_ID
#define LG_Camera_Perspective_ID "_LG_Camera_Perspective_"

int LG_Camera_Perspective::_LG_classIDNr = 0;


//passing LG_Camera_Perspective_Node_ID won't work, ID must be unique and there may be more than one perspective
LG_Camera_Perspective::LG_Camera_Perspective(LG_Node_Map *map, TiXmlElement *element) :LG_Parsable_Node(map, autoIdentifier)
{
	verifyElementName(element);
	verifyAttributesAndValues(element);
}


LG_Camera_Perspective::~LG_Camera_Perspective()
{
}



void LG_Camera_Perspective::verifyElementName(TiXmlElement *element){

	if (!str_eq(element->Value(), LG_Camera_Perspective_XML_TAG_NAME)){
		throw new LG_Parse_Exception_Wrong_Element_Name(new string(LG_Camera_Perspective_XML_TAG_NAME), new string(element->Value()));
	}
}

void LG_Camera_Perspective::verifyAttributesAndValues(TiXmlElement *element){

	string_tryToAttributeVariable(LG_Camera_Perspective_XML_ATT_ID, element, id);
	positiveDouble_tryToAttributeVariable(LG_Camera_Perspective_XML_ATT_NEAR, element, near);
	positiveDouble_tryToAttributeVariable(LG_Camera_Perspective_XML_ATT_FAR, element, far);
	positiveDouble_tryToAttributeVariable(LG_Camera_Perspective_XML_ATT_ANGLE, element, angle);
	point3D_tryToAttributeVariable(LG_Camera_Perspective_XML_ATT_POS, element, pos);
	point3D_tryToAttributeVariable(LG_Camera_Perspective_XML_ATT_TARGET, element, target);
}
