//
//  LG_Plane.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 23/10/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_Plane.h"
#include "LG_ANF.h"


#define LG_Plane_ID_Prefix "_LG_Plane"
#define LG_Plane_NR_Points 4

int LG_Plane::classIDNr = 0;

//Used by subclasses to get through unnecessary validations and attributes
LG_Plane::LG_Plane(LG_Node_Map *map, string LG_Primitive_Identifier) : LG_Patch(map, LG_Primitive_Identifier){
	setPatch();
}


LG_Plane::LG_Plane(LG_Node_Map *map, TiXmlElement *elem) : LG_Patch(map, autoIdentifier(LG_Plane_ID_Prefix, classIDNr)){



	if (!str_eq(elem->Value(), LG_Plane_XML_Tag_Name)) {

		throw LG_Parse_Exception_Wrong_Element_Name(LG_Plane_XML_Tag_Name, elem->Value());
	}

	positiveInt_tryToAttributeVariable(LG_Plane_parts_XML_Att_Name, elem, LG_Patch::partsV);

	LG_Patch::partsU = LG_Patch::partsV;
	setPatch();

}


#pragma mark - Configuration
void LG_Plane::config(){



}


#pragma mark - Inherited Methods


void LG_Plane::draw(){

	LG_Patch::draw();
}

void LG_Plane::calculateTextureCoordinates(){


}


void LG_Plane::setPatch(){

	LG_Patch::points = new float[LG_Plane_NR_Points*LG_Point3D_Length];

	LG_Patch::points[0] = 0;
	LG_Patch::points[1] = 0;
	LG_Patch::points[2] = 0;

	LG_Patch::points[3] = 1;
	LG_Patch::points[4] = 0;
	LG_Patch::points[5] = 0;

	LG_Patch::points[6] = 0;
	LG_Patch::points[7] = 0;
	LG_Patch::points[8] = 1;

	LG_Patch::points[9] = 1;
	LG_Patch::points[10] = 0;
	LG_Patch::points[11] = 1;

	LG_Patch::order = 1;
	LG_Patch::vstride = ORDER1_VSTRIDE;
	
	GLint drawMode[2];
	glGetIntegerv(GL_POLYGON_MODE, drawMode); //get current polygon mode and store it in drawMode[0]
	
	LG_Patch::drawMode = drawMode[0];
}