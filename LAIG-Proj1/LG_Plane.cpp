//
//  LG_Plane.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 23/10/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_Plane.h"

#define LG_Plane_parts_XML_Att_Name "parts"
#define LG_Plane_ID_Prefix "_LG_Plane"

int LG_Plane::classIDNr=0;

LG_Plane::LG_Plane(LG_Node_Map *map,TiXmlElement *elem):LG_Primitive(map,autoIdentifier(LG_Plane_ID_Prefix, classIDNr)),parts(LG_INVALID_INT){


    
    if (!str_eq(elem->Value(), LG_Plane_XML_Tag_Name)) {
        
        throw LG_Parse_Exception_Wrong_Element_Name(LG_Plane_XML_Tag_Name, elem->Value());
    }
    
    positiveInt_tryToAttributeVariable(LG_Plane_parts_XML_Att_Name, elem, parts);
    
    
}


#pragma mark - Configuration
void LG_Plane::config(){

}


#pragma mark - Inherited Methods


void LG_Plane::draw(){
    
}

void LG_Plane::calculateTextureCoordinates(){


}
