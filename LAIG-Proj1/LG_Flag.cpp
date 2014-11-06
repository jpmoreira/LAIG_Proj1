#include "LG_Flag.h"

#define LG_Flag_ID_Prefix "_LG_Flag_"
#define LG_Plane_Parts_Default 5

int LG_Flag::classIDNr = 0;

LG_Flag::LG_Flag(LG_Node_Map *map, TiXmlElement *elem) : LG_Plane(map, autoIdentifier(LG_Flag_ID_Prefix, classIDNr))
{

	try{
		positiveInt_tryToAttributeVariable(LG_Plane_parts_XML_Att_Name, elem, LG_Patch::partsV);
	}
	catch (LG_Parse_Exception *e){
		LG_Patch::partsV = LG_Plane_Parts_Default;
	}

	LG_Patch::partsU = LG_Patch::partsV;

	if (!str_eq(elem->Value(), LG_Flag_XML_Tag_Name)) {

		throw LG_Parse_Exception_Wrong_Element_Name(LG_Flag_XML_Tag_Name, elem->Value());
	}

}


LG_Flag::~LG_Flag()
{
	LG_Plane::~LG_Plane();
}


#pragma mark - Configuration
void LG_Flag::config(){



}


#pragma mark - Inherited Methods


void LG_Flag::draw(){

	LG_Plane::draw();

}

void LG_Flag::calculateTextureCoordinates(){


}
