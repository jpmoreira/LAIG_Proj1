#include "LG_Lighting.h"

#define LG_Lighting_ElementName "lighting";


#pragma mark - Constructors


LG_Lighting::LG_Lighting(LG_Node_Map *map, TiXmlElement *element) :LG_Parsable_Node(map, LG_Lighting_Node_ID,NULL), doublesided(false), local(true), enabled(true){

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
	lightArray_f_tryToAttributeVariable(LG_LIGHTING_XML_ATT_AMBIENT, element, ambient);

}


#pragma mark - Inherited Methods


void LG_Lighting::draw() {
    
    if (enabled)glEnable(GL_LIGHTING);
    else glDisable(GL_LIGHTING);
    
    if (doublesided)glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    else glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
    
    
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, (GLfloat *)ambient);
    
    
    if (local) glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    else glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);
    
    
    
}
