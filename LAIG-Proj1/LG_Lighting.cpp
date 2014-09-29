#include "LG_Lighting.h"

#define LG_Lighting_ElementName "lighting";


#pragma mark - Constructors


LG_Lighting::LG_Lighting(LG_Node_Map *map, TiXmlElement *element) :LG_Parsable_Node(map, LG_Lighting_Node_ID), doublesided(false), local(true), enabled(true){

	//verify type - think it's useless -
	TiXmlNode::NodeType type = (TiXmlNode::NodeType)element->Type();
	if (!(type == TiXmlNode::TINYXML_ELEMENT)) {
		string expected; expected.append(LG_LIGHTING_XML_TAG_NAME);
		throw new LG_Parse_Exception_Wrong_Elem_Type(&expected);
	}

	verifyElementName(element);
	verifyAttributesAndValues(element);



}


#pragma mark - Element Parsing Methods


void LG_Lighting::verifyElementName(TiXmlElement *element){


	string lightingName(LG_LIGHTING_XML_TAG_NAME);
	if (!str_eq(element->Value(), LG_LIGHTING_XML_TAG_NAME)){
		string name_received = (char *)element->Value();
		throw new LG_Parse_Exception_Wrong_Element_Name(&name_received, &lightingName);
	}
}

void LG_Lighting::verifyAttributesAndValues(TiXmlElement *lightingElement){

	//TiXmlAttribute *att=element->FirstAttribute();
	/* search directly for attributes you need and fill them
	instead of going through all
	*/

	string elem, attr, value;
	vector<string> expected;
	LG_BOOL tmp[3];

	elem = (char *)lightingElement->Value();

	char *doublesided_att = (char *)lightingElement->Attribute(LG_LIGHTING_XML_ATT_DOUBLESIDED);
	char *enabled_att = (char *)lightingElement->Attribute(LG_LIGHTING_XML_ATT_ENABLED);
	char *local_att = (char *)lightingElement->Attribute(LG_LIGHTING_XML_ATT_LOCAL);
	char *tmp_ambient = (char *)lightingElement->Attribute(LG_LIGHTING_XML_ATT_AMBIENT);



	//see how you prefer, double check if it missing or one check one at a time and prepare multiple throws
	//constructor is setting default values, will never miss existence of any
	if (!doublesided_att || !enabled_att || !local_att || !tmp_ambient)
	{
		if (!doublesided)
			attr.append(LG_LIGHTING_XML_ATT_DOUBLESIDED);
		else	if (!enabled)
			attr.append(LG_LIGHTING_XML_ATT_ENABLED);
		else 	if (!local)
			attr.append(LG_LIGHTING_XML_ATT_LOCAL);

		else 	if (!ambient)
			attr.append(LG_LIGHTING_XML_ATT_AMBIENT);

		throw  new LG_Parse_Exception_Missing_Attribute(&elem, &attr);
	}

	tmp[0] = boolValueForAttribute_(doublesided_att);
	tmp[1] = boolValueForAttribute_(enabled_att);
	tmp[2] = boolValueForAttribute_(local_att);

	//see how you prefer, double check if it missing or one check one at a time and prepare multiple throws
	//check if there's an invalid value given
	if (tmp[0] == LG_Invalid_Bool || tmp[1] == LG_Invalid_Bool || tmp[2] == LG_Invalid_Bool)
	{

		expected[0].append(LG_BOOL_STRING_FALSE);
		expected[1].append(LG_BOOL_STRING_TRUE);



		if (tmp[0] == LG_Invalid_Bool)
			attr.append(LG_LIGHTING_XML_ATT_DOUBLESIDED);
		else if (tmp[1] == LG_Invalid_Bool)
			attr.append(LG_LIGHTING_XML_ATT_ENABLED);
		else
			attr.append(LG_LIGHTING_XML_ATT_LOCAL);

		value.append((char *)lightingElement->Attribute(attr.c_str()));

		throw new LG_Parse_Exception_Wrong_Attribute_Value(&elem, &attr, &value, &expected);
		return;

	}


	if (!lightArrayValue_(tmp_ambient, ambient))
	{
		elem = (char *)lightingElement->Value();
		expected[0].append("4 floats");
		attr.append(LG_LIGHTING_XML_ATT_AMBIENT);
		value.append(tmp_ambient);

		throw new LG_Parse_Exception_Wrong_Attribute_Value(&elem, &attr, &value, &expected);
		
	}

}
