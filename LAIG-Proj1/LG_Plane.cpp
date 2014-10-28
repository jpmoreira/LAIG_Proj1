//
//  LG_Plane.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 23/10/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_Plane.h"
#include "LG_ANF.h"

#define LG_Plane_parts_XML_Att_Name "parts"
#define LG_Plane_ID_Prefix "_LG_Plane"

int LG_Plane::classIDNr=0;

LG_Plane::LG_Plane(LG_Node_Map *map,TiXmlElement *elem):LG_Primitive(map,autoIdentifier(LG_Plane_ID_Prefix, classIDNr)),parts(LG_INVALID_INT){


    
    if (!str_eq(elem->Value(), LG_Plane_XML_Tag_Name)) {
        
        throw LG_Parse_Exception_Wrong_Element_Name(LG_Plane_XML_Tag_Name, elem->Value());
    }
    
    positiveInt_tryToAttributeVariable(LG_Plane_parts_XML_Att_Name, elem, parts);
    

    points[0][0]=0;
    points[0][1]=0;
    points[0][2]=0;
    
    points[1][0]=1;
    points[1][1]=0;
    points[1][2]=0;
    
    points[2][0]=0;
    points[2][1]=0;
    points[2][2]=1;
    
    points[3][0]=1;
    points[3][1]=0;
    points[3][2]=1;
    
}


#pragma mark - Configuration
void LG_Plane::config(){
    
    

}


#pragma mark - Inherited Methods


void LG_Plane::draw(){
    

	/*points[0][0] = 0;
	points[0][1] = 0;
	points[0][2] = 0;

	points[1][0] = 1;
	points[1][1] = 0;
	points[1][2] = 0;

	points[2][0] = 0;
	points[2][1] = 0;
	points[2][2] = 1;

	points[3][0] = 1;
	points[3][1] = 0;
	points[3][2] = 1;
    */
    
    
    glMap2d(	GL_MAP2_VERTEX_3,
                 0,//u start
                 1.0,//u finish
                 3,//ustride
                 2,//1st degree curve
                 0,//v start
                 1.0,//v end
                 6,//vstride
                 2,//1st degree curve
                (GLdouble *) points);

    glEnable(GL_MAP2_VERTEX_3);
    
    
    glMapGrid2d(parts,0,1,parts,0,1);
    
    GLint drawMode[2];
    glGetIntegerv(GL_POLYGON_MODE,
                       drawMode);

    
    glEvalMesh2(drawMode[0], 0, parts, 0, parts);
    
}

void LG_Plane::calculateTextureCoordinates(){


}
