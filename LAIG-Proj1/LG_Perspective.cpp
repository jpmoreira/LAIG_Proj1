#include "LG_Perspective.h"


//passing LG_Perspective_Node_ID won't work, ID must be unique and there may be more than one perspective
LG_Perspective::LG_Perspective(LG_Node_Map *map, TiXmlElement *element) :LG_Parsable_Node(map, LG_Perspective_Node_ID)
{
	//verify type - think it's useless -
	TiXmlNode::NodeType type = (TiXmlNode::NodeType)element->Type();
	if (!(type == TiXmlNode::TINYXML_ELEMENT)) {
		string expected; expected.append(LG_PERSPECTIVE_XML_TAG_NAME);
		throw new LG_Parse_Exception_Wrong_Elem_Type(&expected);
	}

	verifyElementName(element);
	verifyAttributesAndValues(element);

}


LG_Perspective::~LG_Perspective()
{
}



void LG_Perspective::verifyElementName(TiXmlElement *element){
	string perspective_name(LG_PERSPECTIVE_XML_TAG_NAME);
	if (!str_eq(element->Value(), LG_PERSPECTIVE_XML_TAG_NAME)){
		string name_received = (char *)element->Value();
		throw new LG_Parse_Exception_Wrong_Element_Name(&name_received, &perspective_name);
	}
}

void LG_Perspective::verifyAttributesAndValues(TiXmlElement *element){
	
}