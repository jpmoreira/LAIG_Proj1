//
//  LG_Rectangle.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 28/09/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_Rectangle.h"

#define LG_Rectangle_ID "_LG_Rectangle_"
#define LG_Rectangle_Node_Name "rectangle"
#define LG_Rectangle_XML_Att1_Name "xy1"
#define LG_Rectangle_XML_Att2_Name "xy2"


int LG_Rectangle::rectangleNr=0;

LG_Rectangle::LG_Rectangle(LG_Node_Map *map,LG_Point3D point1,LG_Point3D point2):LG_Primitive(map,rectangleID(rectangleNr++)){
    
    copyPoints(point1, point2);

}
LG_Rectangle::LG_Rectangle(LG_Node_Map *map,TiXmlElement *elem):LG_Primitive(map,rectangleID(rectangleNr++)){
    
    
    initializePoint3D(pt1);
    initializePoint3D(pt2);
    
    verifyElementName(elem);
    verifyElementAttributesAndValues(elem);

    

}


#pragma mark - Helper Methods

string LG_Rectangle::rectangleID(int nr){

    return string(LG_Rectangle_ID+std::to_string(nr));
}


void LG_Rectangle::copyPoints(LG_Point3D point1,LG_Point3D point2){

    for (int i=0; i<LG_Point3D_Length; i++) {
        pt1[i]=point1[i];
        pt2[i]=point2[i];
    }

}
#pragma mark - Inherited Methods



void LG_Rectangle::verifyElementName(TiXmlElement *element){
    
    if (!str_eq(element->Value(), LG_Rectangle_Node_Name)) {
        throw new LG_Parse_Exception_Wrong_Element_Name(new string(LG_Rectangle_Node_Name),new string(element->Value()));
    }
                                                        

}

void LG_Rectangle::verifyElementAttributesAndValues(TiXmlElement *element){
    
    TiXmlAttribute *att=element->FirstAttribute();
    
    while(att){
        
        
        if(str_eq(att->Name(),LG_Rectangle_XML_Att1_Name)){
        
            point3DValueFromPoint2D(att, pt1);
        }
        else if(str_eq(att->Name(),LG_Rectangle_XML_Att2_Name)){
        
            point3DValueFromPoint2D(att, pt2);
        }
        
        att=att->Next();
    }
    
    
    if(pt1[0]==LG_INVALID_DOUBLE)
        throw new LG_Parse_Exception_Missing_Attribute(new string(LG_Rectangle_Node_Name),new string(LG_Rectangle_XML_Att1_Name));
    if(pt2[0]==LG_INVALID_DOUBLE)
        throw new LG_Parse_Exception_Missing_Attribute(new string(LG_Rectangle_Node_Name),new string(LG_Rectangle_XML_Att2_Name));
    
}

