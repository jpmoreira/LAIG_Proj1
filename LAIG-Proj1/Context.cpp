//
//  Context.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 22/09/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "Context.h"





#pragma mark - Constructors


LG_Context::LG_Context():texture(NULL){
    
    loadIdentity();


    
    

}


#pragma mark - Cloning

LG_Context * LG_Context::clone(){

    LG_Context * newContext=new LG_Context();
    
    newContext->cloneMatrix(this);
    
    
    
    
    return newContext;
    

}


/**
 
 Clones a Context object but changes it's light component.
 
 */
LG_Context clone_changeLight(GLdouble amb[4],GLdouble diff[4],GLdouble spec[4],GLdouble shininess);


/**
 
 Clones a Context object but changes the texture.
 
 
 */
LG_Context clone_changeTexture(CGFtexture *newTexture);


/**
 
 
 Clones a context but changes the matrix for this context.
 
 */
LG_Context clone_changeMatrix(GLdouble newMatrix[4][4]);

/**
 
 Clones a context but applies a rotation to the current matrix.
 
 */
LG_Context clone_Rotate(double angle,LG_Axis axis);


/**
 
 Clones a context but applies a translation to the current matrix.
 
 */
LG_Context clone_Translate(double dx,double dy, double dz);

/**
 
 Clones a context but applies a scaling operation to the current matrix.
 
 */
LG_Context clone_Scale(double sx,double sy,double sz);


#pragma mark - Helper Methods


void LG_Context::loadIdentity(){

    for (int col=0; col<4; col++) {
        for (int line=0; line<4; line++) {
            
            if (line==col) matrix[col][line]=1;
            else matrix[col][line]=0;
            
        }
    }

}


void LG_Context::cloneMatrix(LG_Context * contextToClone){
    
    for (int col=0; col<4; col++) {
        for (int line=0; line<4; line++) {
            matrix[col][line]=contextToClone->matrix[col][line];
        }
    }

}
