#include "LG_Camera_Ortho.h"

//string LG_Camera_Ortho::getIdentifier(){
//	return this->id;
//}

LG_Camera_Ortho::LG_Camera_Ortho(LG_Node_Map *map, TiXmlElement *element) :LG_Camera(map, element, identifierForSuper(element))
{
	void verifyElementName(TiXmlElement *element);
	void verifyAttributesAndValues(TiXmlElement *element);
}


LG_Camera_Ortho::~LG_Camera_Ortho()
{
}

void LG_Camera_Ortho::verifyElementName(TiXmlElement *element){
	if (!str_eq(element->Value(), LG_Camera_Ortho_XML_TAG_NAME))
		throw LG_Parse_Exception_Wrong_Element_Name(new string(LG_Camera_Ortho_XML_TAG_NAME), new string(element->Value()));
}

void LG_Camera_Ortho::verifyAttributesAndValues(TiXmlElement *element){

	positiveDouble_tryToAttributeVariable(LG_Camera_Ortho_XML_ATT_TOP, element, top);
	positiveDouble_tryToAttributeVariable(LG_Camera_Ortho_XML_ATT_BOTTOM, element, bottom);
	positiveDouble_tryToAttributeVariable(LG_Camera_Ortho_XML_ATT_LEFT, element, left);
	positiveDouble_tryToAttributeVariable(LG_Camera_Ortho_XML_ATT_RIGHT, element, right);


	vector<string> options;
	options.push_back(LG_AXIS_X_STR);
	options.push_back(LG_AXIS_Y_STR);
	options.push_back(LG_AXIS_Z_STR);

	int tmp;
	enum_tryToAttribute(LG_Camera_Ortho_XML_ATT_DIRECTION, element, tmp, &options);

	direction = (LG_AXIS) tmp;

}
