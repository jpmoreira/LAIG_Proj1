//
//  LG_Glu_Primitives.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 08/10/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_Glu_Primitive.h"
#include "LG_ANF.h"


#pragma mark - Constructors

LG_Glu_Primitive::LG_Glu_Primitive(LG_Node_Map *map,string identifier):LG_Primitive(map,identifier) {
    
    configureQuadric();
}


LG_Glu_Primitive::LG_Glu_Primitive(LG_Node_Map *map,string identifier,LG_Appearance *app):LG_Primitive(map,identifier,app){

    configureQuadric();
}

#pragma mark - Helper Methods

void LG_Glu_Primitive::configureQuadric() {
    
    quadric=gluNewQuadric();
    
    gluQuadricNormals(quadric, GLU_SMOOTH);
    gluQuadricOrientation(quadric, GLU_OUTSIDE);
    
    
    if (LG_ANF::currentDrawingMode()==LG_Drawing_Fill) {
        gluQuadricDrawStyle(quadric, GLU_FILL);
    }
    else if(LG_ANF::currentDrawingMode()==LG_Drawing_Line){
        gluQuadricDrawStyle(quadric, GLU_LINE);
    }
    
    else if(LG_ANF::currentDrawingMode()==LG_Drawing_Point){
        gluQuadricDrawStyle(quadric, GLU_POINT);
    }

    
    gluQuadricTexture(quadric, GL_TRUE);
    
    
}