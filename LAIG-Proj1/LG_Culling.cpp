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


	verifyElementName(element);
	verifyAttributesAndValues(element);

}
LG_Culling::LG_Culling(LG_Node_Map *map, TiXmlElement *element, LG_Culling_Order ord, LG_Culling_Face f) :LG_Parsable_Node(map, _LG_Culling_NodeID), face(f), order(ord){


}

void LG_Culling::verifyAttributesAndValues(TiXmlElement *element){

	string elem, attr, value;
	vector<string> expected;

	string face_att_name(LG_CULLING_XML_ATT_FACE), order_att_name(LG_CULLING_XML_ATT_ORDER);

	vector<string> enums;
	enums.push_back(LG_Culling_Back_String);
	enums.push_back(LG_Culling_Front_String);
	enums.push_back(LG_Culling_None_String);
	enums.push_back(LG_Culling_Both_String);

	int tmp;
	enum_tryToAttribute(LG_CULLING_XML_ATT_FACE, element, tmp, &enums);
	face =(LG_Culling_Face) tmp;

	enums.clear();
	enums.push_back(LG_Culling_CW_String);
	enums.push_back(LG_Culling_CCW_String);

	enum_tryToAttribute(LG_CULLING_XML_ATT_FACE, element, tmp, &enums);
	order =(LG_Culling_Order) tmp;

}


void LG_Culling::verifyElementName(TiXmlElement *element){
	if (!str_eq(element->Value(), LG_CULLING_XML_TAG_NAME))
		throw LG_Parse_Exception_Wrong_Element_Name(new string(LG_CULLING_XML_TAG_NAME), new string(element->Value()));
}