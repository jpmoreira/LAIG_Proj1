//
//  LG_Rectangle.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 28/09/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_Rectangle.h"

#define LG_Rectangle_ID "_LG_Rectangle_"
#define _LG_Primitive_Name LG_Rectangle_ID
#define LG_Rectangle_Node_Name "rectangle"
#define LG_Rectangle_XML_Att1_Name "xy1"
#define LG_Rectangle_XML_Att2_Name "xy2"


int LG_Rectangle::_LG_classIDNr=0;

LG_Rectangle::LG_Rectangle(LG_Node_Map *map,LG_Point3D point1,LG_Point3D point2):LG_Primitive(map,autoIdentifier){
    
    copyPoints(point1, point2);

}
LG_Rectangle::LG_Rectangle(LG_Node_Map *map,TiXmlElement *elem):LG_Primitive(map,autoIdentifier){
    
    
    initializePoint3D(pt1);
    initializePoint3D(pt2);
    
    
    
    if (!str_eq(elem->Value(), LG_Rectangle_Node_Name)) {
        throw new LG_Parse_Exception_Wrong_Element_Name(new string(LG_Rectangle_Node_Name),new string(elem->Value()));
    }
    
    
    
    point3DFrom2D_tryToAttributeVariable(LG_Rectangle_XML_Att1_Name, elem, pt1);
    point3DFrom2D_tryToAttributeVariable(LG_Rectangle_XML_Att2_Name, elem, pt2);
    
    

}


#pragma mark - Helper Methods


void LG_Rectangle::copyPoints(LG_Point3D point1,LG_Point3D point2){

    for (int i=0; i<LG_Point3D_Length; i++) {
        pt1[i]=point1[i];
        pt2[i]=point2[i];
    }

}
#pragma mark - Inherited Methods


