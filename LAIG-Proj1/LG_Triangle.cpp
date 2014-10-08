//
//  LG_Triangle.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 23/09/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_Triangle.h"
#include <GL/glut.h>



#define _LG_Primitive_Name LG_Triangle_ID

#define LG_Triangle_XML_Att1_Name "xyz1"
#define LG_Triangle_XML_Att2_Name "xyz2"
#define LG_Triangle_XML_Att3_Name "xyz3"
#define LG_Triangle_ID "_LG_Triangle_"

#pragma mark - Constructors

int LG_Triangle::_LG_classIDNr=0;

LG_Triangle::LG_Triangle(LG_Node_Map *map,TiXmlElement *elem):LG_Primitive(map,autoIdentifier){


    initializePoint3D(pt1);
    initializePoint3D(pt2);
    initializePoint3D(pt3);
    
    if(!str_eq(LG_Triangle_XML_Tag_Name, elem->Value())){
        
        
        throw new LG_Parse_Exception_Wrong_Element_Name(new string(LG_Triangle_XML_Tag_Name),new string(elem->Value()));
    }
    
    point3D_tryToAttributeVariable(LG_Triangle_XML_Att1_Name, elem, pt1);
    point3D_tryToAttributeVariable(LG_Triangle_XML_Att2_Name, elem, pt2);
    point3D_tryToAttributeVariable(LG_Triangle_XML_Att3_Name, elem, pt3);
    
    newells(pt1, pt2, pt3, normal);

}

LG_Triangle::LG_Triangle(LG_Node_Map *map,string identifier,LG_Point3D point1,LG_Point3D point2, LG_Point3D point3):LG_Primitive(map,identifier){
    
    initializePoint3D(pt1);
    initializePoint3D(pt2);
    initializePoint3D(pt3);
    
    this->copyPoints(point1, point2, point3);
    newells(pt1, pt2, pt3, normal);
    
    
}


LG_Triangle::LG_Triangle(LG_Node_Map *map,string identifier):LG_Primitive(map,identifier){


    initializePoint3D(pt1);
    initializePoint3D(pt2);
    initializePoint3D(pt3);
    
    newells(pt1, pt2, pt3, normal);
}

#pragma mark - Inherited Methods


void LG_Triangle::draw(){
    
    glBegin(GL_TRIANGLES);
    
    glNormal3d(normal[0], normal[1], normal[2]);
    glVertex3d(pt1[0], pt1[1], pt1[2]);
    glVertex3d(pt2[0], pt2[1], pt2[2]);
    glVertex3d(pt3[0], pt3[1], pt3[2]);
    
    glEnd();
    
    


}





#pragma mark - Helper Methods


void LG_Triangle::copyPoints(LG_Point3D point1,LG_Point3D point2, LG_Point3D point3){
    
    
    for (int i=0; i<LG_Point3D_Length; i++) {
        
        pt1[i]=point1[i];
        pt2[i]=point2[i];
        pt3[i]=point3[i];
    }
    

}






