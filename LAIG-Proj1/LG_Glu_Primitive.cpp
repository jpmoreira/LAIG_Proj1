//
//  LG_Glu_Primitives.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 08/10/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_Glu_Primitive.h"


#pragma mark - Constructors

LG_Glu_Primitive::LG_Glu_Primitive(LG_Node_Map *map,string identifier):LG_Primitive(map,identifier) {
    
    configureQuadric();
}

#pragma mark - Helper Methods

void LG_Glu_Primitive::configureQuadric() {
    
    quadric=gluNewQuadric();
    
    gluQuadricNormals(quadric, GLU_SMOOTH);
    gluQuadricOrientation(quadric, GLU_OUTSIDE);
    gluQuadricDrawStyle(quadric, GLU_FILL);
    gluQuadricTexture(quadric, GL_TRUE);
    
    
}