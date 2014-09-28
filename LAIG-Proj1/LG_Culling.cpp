//
//  LG_Culling.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 26/09/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_Culling.h"

#include "LG_Parsable_Node.h"




LG_Culling::LG_Culling(LG_Node_Map *map, TiXmlElement *element) :LG_Parsable_Node(map, _LG_Culling_NodeID), face(LG_Culling_Face_Not_Set), order(LG_Culling_Order_Not_Set){

	//verify type - think it's useless -
	TiXmlNode::NodeType type = (TiXmlNode::NodeType)element->Type();
	if (!(type == TiXmlNode::TINYXML_ELEMENT)) {
		string expected; expected.append("culling");
		throw LG_Parse_Exception_Wrong_Elem_Type(&expected);
		return;
	}

	verifyElementName(element);
	verifyAttributesAndValues(element);

}
LG_Culling::LG_Culling(LG_Node_Map *map, TiXmlElement *element, LG_Culling_Order ord, LG_Culling_Face f) :LG_Parsable_Node(map, _LG_Culling_NodeID), face(f), order(ord){


}

void LG_Culling::verifyAttributesAndValues(TiXmlElement *element){

	string elem, attr, value;
	vector<string> expected;

	string face_att_name("face"), order_att_name("order");

	elem = (char *)element->Value();

	char* face_val = (char *)element->Attribute(face_att_name.c_str());
	char* order_val = (char *)element->Attribute(order_att_name.c_str());

	if (!face_val || !order_val){
		if (!face_val)
			throw LG_Parse_Exception_Missing_Attribute(&elem, &face_att_name);
		else
			throw LG_Parse_Exception_Missing_Attribute(&elem, &order_att_name);

		return;
	}


	if (strcmp(face_val, "none") != 0 && strcmp(face_val, "back") != 0
		&& strcmp(face_val, "front") != 0 && strcmp(face_val, "both") != 0)
	{
		value.append(face_val);
		expected[0] = "none"; expected[1] = "back";
		expected[2] = "front"; expected[3] = "both";
		throw LG_Parse_Exception_Wrong_Attribute_Value(&elem, &face_att_name, &value, &expected);
		return;
	}
	else
		stringToAttr(&face_att_name, face_val);


	if (strcmp(order_val, "cw") != 0 && strcmp(order_val, "ccw") != 0)
	{
		value.append(order_val);
		expected[0] = "cw"; expected[1] = "ccw";
		throw LG_Parse_Exception_Wrong_Attribute_Value(&elem, &order_att_name, &value, &expected);
		return;
	}
	else
		stringToAttr(&order_att_name, order_val);
}


void LG_Culling::verifyElementName(TiXmlElement *element){
	string lightingName = "culling";
	if (!str_eq(element->Value(), "culling")){
		string name_received = (char *)element->Value();
		throw LG_Parse_Exception_Wrong_Element_Name(&name_received, &lightingName);
		return;
	}
}


void LG_Culling::stringToAttr(string *att_name, char *att){
	
	if (att_name->compare("face")==0){
		if (strcmp(att, "none")== 0)
			this->face = LG_None;
		else if (strcmp(att, "back")== 0)
			this->face = LG_Back;
		else if (strcmp(att, "front")==0)
			this->face = LG_Front;
		else 
			this->face = LG_Both;
	}
	else
		if (att_name->compare("order") == 0)
		if (strcmp(att, "cw"))
			this->order = LG_Culling_Order_CW;
		else
			this->order = LG_Culling_Order_CCW;
}