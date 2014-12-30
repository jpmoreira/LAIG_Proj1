//
//  LG_Drawing.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 26/09/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_Drawing.h"
#ifdef _WIN32
#include <Windows.h>
#endif

#define LG_Drawing_Fill_String "fill"
#define LG_Drawing_Line_String "line"
#define LG_Drawing_Point_String "point"

#define LG_Drawing_Mode_XML_Att_Name "mode"

#define LG_Shading_Mode_XML_Att_Name "shading"

#define LG_Background_XML_Att_Name "background"


#define LG_Shading_Flat_String "flat"
#define LG_Shading_Gourad_String "gouraud"









LG_Drawing::LG_Drawing(LG_Node_Map *map, TiXmlElement *element) :LG_Parsable_Node(map, _LG_Drawing_NodeID), mode(LG_Drawing_Not_Set), shading(LG_Shading_Not_Set){




	verifyElementName(element);
	verifyElementAttributesAndValues(element);

}

LG_Drawing::LG_Drawing(LG_Node_Map *map, LG_Drawing_Mode md, LG_Shading_Mode shading, LG_LightArray bkg) :LG_Parsable_Node(map, _LG_Drawing_NodeID), mode(md), shading(shading){

	for (int i = 0; i < LG_LightArray_Lenght; i++) {
		background[i] = bkg[i];
	}


}



#pragma mark - Helper Methods
void LG_Drawing::verifyElementName(TiXmlElement *element){


	if (strcmp(element->Value(), LG_Drawing_XML_Tag_Name) == 0)return;


	string *expected = new string(LG_Drawing_XML_Tag_Name);
	string *actual = new string(element->Value());
	throw new LG_Parse_Exception_Wrong_Element_Name(expected, actual);


}

void LG_Drawing::verifyElementAttributesAndValues(TiXmlElement *element){


	TiXmlAttribute *att = element->FirstAttribute();//get first attribute

	while (att) {//para cada atributo

		if (str_eq(att->Name(), LG_Drawing_Mode_XML_Att_Name)){//se o nome é o do atributo drawing




			vector<string> possible;

			possible.push_back(string(LG_Drawing_Fill_String));
			possible.push_back(string(LG_Drawing_Line_String));
			possible.push_back(string(LG_Drawing_Point_String));


			int value;
			enum_tryToAttribute(att->Name(), element, value, &possible);

			//LG_Parsable_Node::stringValue(att, values, 3);//tenta ver que valor é o que está no atributo
			if (value >= 0) this->mode = (LG_Drawing_Mode)value;//caso o valor retornado seja >=0 então pode-se fazer logo cast para o tipo adequado e guardar o valor


		}

		else if (str_eq(att->Name(), LG_Shading_Mode_XML_Att_Name)){

			char * values[2];

			values[0] = LG_Shading_Flat_String;
			values[1] = LG_Shading_Gourad_String;


			vector<string> possible;

			possible.push_back(string(LG_Shading_Flat_String));
			possible.push_back(string(LG_Shading_Gourad_String));


			int value;

			enum_tryToAttribute(att->Name(), element, value, &possible);
			if (values >= 0) this->shading = (LG_Shading_Mode)value;


		}

		else if (str_eq(att->Name(), LG_Background_XML_Att_Name)){


			LG_Parsable_Node::lightArrayValue(att, this->background);
		}

		att = att->Next();
	}



	string *node_name = new string(LG_Drawing_XML_Tag_Name);

	//verify if something is missing
	if (this->mode == LG_Drawing_Not_Set){


		throw new LG_Parse_Exception_Missing_Attribute(node_name, new string(LG_Drawing_Mode_XML_Att_Name));
	}


	else if (this->shading == LG_Shading_Not_Set){

		throw new LG_Parse_Exception_Missing_Attribute(node_name, new string(LG_Shading_Mode_XML_Att_Name));

	}

	else if (this->background[0] == LG_LightValue_Not_Set){




		throw new LG_Parse_Exception_Missing_Attribute(node_name, new string(LG_Background_XML_Att_Name));

	}



}


#pragma mark - Inherited Methods

void LG_Drawing::draw(bool selectMode) {



	if (mode == LG_Drawing_Line) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else if (mode == LG_Drawing_Point) glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	else if (mode == LG_Drawing_Fill) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


	if (shading == LG_Flat) glShadeModel(GL_FLAT);
	else if (shading == LG_Gouraud) glShadeModel(GL_SMOOTH);

	glClearColor(background[0], background[1], background[2], background[3]);
    


}

LG_Drawing_Mode LG_Drawing::getMode()
{
	return mode;
}

void LG_Drawing::setMode(LG_Drawing_Mode mode)
{
	this->mode = mode;
}