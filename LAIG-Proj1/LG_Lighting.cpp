#include "LG_Lighting.h"

#define LG_Lighting_ElementName "lighting";


#pragma mark - Constructors


LG_Lighting::LG_Lighting(LG_Node_Map *map, TiXmlElement *element) :LG_Parsable_Node(map, LG_Lighting_Node_ID), doublesided(false), local(true), enabled(true){

	//verify type - think it's useless -
	TiXmlNode::NodeType type = (TiXmlNode::NodeType)element->Type();
	if (!(type == TiXmlNode::TINYXML_ELEMENT)) {
		string expected; expected.append("lighting");
		throw LG_Parse_Exception_Wrong_Elem_Type(&expected);
		return;
	}

	verifyElementName(element);
	verifyAttributesAndValues(element);



}


#pragma mark - Element Parsing Methods


void LG_Lighting::verifyElementName(TiXmlElement *element){


	string lightingName = "lightning";
	if (!str_eq(element->Value(), "lightning")){
		string name_received = (char *)element->Value();
		throw LG_Parse_Exception_Wrong_Element_Name(&name_received, &lightingName);
		return;
	}
}

void LG_Lighting::verifyAttributesAndValues(TiXmlElement *lightingElement){

	//TiXmlAttribute *att=element->FirstAttribute();
	/* search directly for attributes you need and fill them
	instead of going through all
	*/

	string elem, attr, value;
	vector<string> expected;


	elem = (char *)lightingElement->Value();
	doublesided = boolValueForAttribute(lightingElement->Attribute("doublesided"));
	enabled = (char *)lightingElement->Attribute("enabled");
	local = (char *)lightingElement->Attribute("local");
	char *tmp_ambient = (char *)lightingElement->Attribute("ambient");



	//see how you prefer, double check if it missing or one check one at a time and prepare multiple throws
	//constructor is setting default values, will never miss existence of any
	if (!doublesided || !enabled || !local || !ambient)
	{
		if (!doublesided)
			attr.append("doublesided");
		else	if (!enabled)
			attr.append("enabled");
		else 	if (!local)
			attr.append("local");

		else 	if (!ambient)
			attr.append("ambient");

		throw LG_Parse_Exception_Missing_Attribute(&elem, &attr);
	}

	//see how you prefer, double check if it missing or one check one at a time and prepare multiple throws
	//check if there's an invalid value given
	if (doublesided == LG_Invalid_Bool || enabled == LG_Invalid_Bool || local == LG_Invalid_Bool)
	{

		expected[0].append("true");
		expected[1].append("false");



		if (doublesided == LG_Invalid_Bool)
			attr.append("doublesided");
		else if (enabled == LG_Invalid_Bool)
			attr.append("enabled");
		else
			attr.append("local");

		value.append((char *)lightingElement->Attribute(attr.c_str()));

		throw LG_Parse_Exception_Wrong_Attribute_Value(&elem, &attr, &value, &expected);
		return;

	}


	if (!lightArrayValue_(tmp_ambient, ambient))
	{
		elem = (char *)lightingElement->Value();
		expected[0].append("4 floats");
		attr.append("ambient");
		value.append(tmp_ambient);

		throw LG_Parse_Exception_Wrong_Attribute_Value(&elem, &attr, &value, &expected);
		return;
	}

}
