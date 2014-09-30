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

//id="ss" near="ff" far="ff" angle="ff" pos="ff ff ff" target="ff ff ff"
void LG_Perspective::verifyAttributesAndValues(TiXmlElement *element){

	LG_BOOL tmp[3];

	/*
	string id;
	double near, far, angle, pos[3], target[3];
	*/

	isValidString(element, LG_PERSPECTIVE_XML_ATT_ID, id);


	vector< double *> dbl_atts;
	dbl_atts.push_back(&near);
	dbl_atts.push_back(&far);
	dbl_atts.push_back(&angle);

	vector< const char *> dbl_att_nms;
	dbl_att_nms.push_back(LG_PERSPECTIVE_XML_ATT_NEAR);
	dbl_att_nms.push_back(LG_PERSPECTIVE_XML_ATT_FAR);
	dbl_att_nms.push_back(LG_PERSPECTIVE_XML_ATT_ANGLE);

	doubleValueForMandatoryAtts(element, dbl_att_nms, dbl_atts);
	point3DMandatoryDblArray(element, LG_PERSPECTIVE_XML_ATT_POS, pos);
	point3DMandatoryDblArray(element, LG_PERSPECTIVE_XML_ATT_TARGET, target);


}
