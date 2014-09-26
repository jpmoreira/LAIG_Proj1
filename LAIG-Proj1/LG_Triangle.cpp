//
//  LG_Triangle.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 23/09/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_Triangle.h"
#include <GL/glew.h>



#pragma mark - Constructors


LG_Triangle::LG_Triangle(LG_Node_Map *map,string identifier,LG_Point point1,LG_Point point2, LG_Point point3):LG_Node(map,identifier),pt1 LG_Origin_3D_Point,pt2 LG_Origin_3D_Point,pt3 LG_Origin_3D_Point{
    
    
    this->copyPoints(point1, point2, point3);
    
    
}


LG_Triangle::LG_Triangle(LG_Node_Map *map,string identifier):LG_Node(map,identifier){


}

#pragma mark - Inherited Methods



void LG_Triangle::draw(){
    
    glPushMatrix();
    
    //properties->multMatrix();
    
    glVertex3d(pt1[0], pt1[1], pt1[2]);
    glVertex3d(pt2[0], pt2[1], pt2[2]);
    glVertex3d(pt3[0], pt3[1], pt3[2]);
    
    
    glPopMatrix();
    


}

#pragma mark - Helper Methods


void LG_Triangle::copyPoints(LG_Point point1,LG_Point point2, LG_Point point3){
    
    
    
    
    
    for (int i=0; i<3; i++) {
        
        pt1[i]=point1[i];
        pt2[i]=point2[i];
        pt3[i]=point3[i];
    }
    
    
    


}








