//
//  LG_Rectangle.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 28/09/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_Rectangle.h"
#include <GL/glut.h>

#define LG_Rectangle_ID "_LG_Rectangle_"
#define _LG_Primitive_Name LG_Rectangle_ID

#define LG_Rectangle_XML_Att1_Name "xy1"
#define LG_Rectangle_XML_Att2_Name "xy2"


int LG_Rectangle::_LG_classIDNr=0;

LG_Rectangle::LG_Rectangle(LG_Node_Map *map,LG_Point3D point1,LG_Point3D point2):LG_Primitive(map,autoIdentifier){
    
    copyPoints(point1, point2);

}
LG_Rectangle::LG_Rectangle(LG_Node_Map *map,TiXmlElement *elem):LG_Primitive(map,autoIdentifier){
    
    
    initializePoint3D(pt1);
    initializePoint3D(pt2);
    
    
    
    if (!str_eq(elem->Value(), LG_Rectangle_XML_Tag_Name)) {
        throw new LG_Parse_Exception_Wrong_Element_Name(new string(LG_Rectangle_XML_Tag_Name),new string(elem->Value()));
    }
    
    
    
    point3DFrom2D_tryToAttributeVariable(LG_Rectangle_XML_Att1_Name, elem, pt1);
    point3DFrom2D_tryToAttributeVariable(LG_Rectangle_XML_Att2_Name, elem, pt2);
    
    

}


LG_Rectangle::LG_Rectangle(LG_Node_Map *map,TiXmlElement *elem,LG_Appearance *app):LG_Primitive(map,autoIdentifier,app){

    
    initializePoint3D(pt1);
    initializePoint3D(pt2);
    
    
    
    if (!str_eq(elem->Value(), LG_Rectangle_XML_Tag_Name)) {
        throw new LG_Parse_Exception_Wrong_Element_Name(new string(LG_Rectangle_XML_Tag_Name),new string(elem->Value()));
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


void LG_Rectangle::draw(){

    
    LG_Primitive::draw();
    
    glBegin(GL_QUADS);

    glNormal3d(0, 0, 1);
    
    glTexCoord2d(pt1_textCoords[0], pt1_textCoords[1]);
    glVertex3d(pt1[0], pt1[1], pt1[2]);
    glTexCoord2d(pt1_2_textCoords[0],pt1_2_textCoords[1]);
    glVertex3d(pt2[0], pt1[1], pt1[2]);
    glTexCoord2d(pt2_textCoords[0], pt2_textCoords[1]);
    glVertex3d(pt2[0], pt2[1], pt1[2]);
    glTexCoord2d(pt2_2_textCoords[0], pt2_2_textCoords[1]);
    glVertex3d(pt1[0], pt2[1], pt2[2]);
    
    
    glEnd();

}

void LG_Rectangle::calculateTextureCoordinates(){

    
    if (!LG_Appearance::currentTexture) return;

    pt1_textCoords[0]=0;
    pt1_textCoords[1]=0;
    
    pt1_2_textCoords[0]=(pt2[0]-pt1[0])/LG_Appearance::currentTexture->getLength_s() ;
    pt1_2_textCoords[1]=0;
    
    
    pt2_textCoords[0]=(pt2[0]-pt1[0])/LG_Appearance::currentTexture->getLength_s();
    pt2_textCoords[1]=(pt2[1]-pt1[1])/LG_Appearance::currentTexture->getLength_t();
    
    
    pt2_2_textCoords[0]=0;
    pt2_2_textCoords[1]=(pt2[1]-pt1[1])/LG_Appearance::currentTexture->getLength_t();

}

