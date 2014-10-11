#include "LG_Lighting.h"

#define LG_Lighting_ElementName "lighting";


#pragma mark - Constructors


LG_Lighting::LG_Lighting(LG_Node_Map *map, TiXmlElement *element) :LG_Parsable_Node(map, LG_Lighting_Node_ID), doublesided(false), local(true), enabled(true){

	verifyElementName(element);
	verifyAttributesAndValues(element);



}


#pragma mark - Element Parsing Methods


void LG_Lighting::verifyElementName(TiXmlElement *element){

	if (!str_eq(element->Value(), LG_LIGHTING_XML_TAG_NAME))
		throw new LG_Parse_Exception_Wrong_Element_Name(new string(LG_LIGHTING_XML_TAG_NAME), new string(element->Value()));
}

void LG_Lighting::verifyAttributesAndValues(TiXmlElement *element){

	bool_tryToAttributeVariable(LG_LIGHTING_XML_ATT_DOUBLESIDED, element, doublesided);
	bool_tryToAttributeVariable(LG_LIGHTING_XML_ATT_ENABLED, element, enabled);
	bool_tryToAttributeVariable(LG_LIGHTING_XML_ATT_LOCAL, element, local);
	lightArray_tryToAttributeVariable(LG_LIGHTING_XML_ATT_AMBIENT, element, ambient);

}
