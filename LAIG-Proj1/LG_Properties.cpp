//
//  Context.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 22/09/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_Properties.h"





#pragma mark - Constructors


LG_Properties::LG_Properties():texture(NULL){
    
    loadIdentity();


    
    

}


#pragma mark - Cloning

LG_Properties * LG_Properties::clone(){

    LG_Properties * newContext=new LG_Properties();
    
    newContext->cloneMatrix(this);
    
    newContext->cloneLightParameters(this);
    
    
#error continue implementation here
    
    return newContext;
    

}


/**
 
 Clones a Context object but changes it's light component.
 
 */
LG_Properties clone_changeLight(GLdouble amb[4],GLdouble diff[4],GLdouble spec[4],GLdouble shininess);


/**
 
 Clones a Context object but changes the texture.
 
 
 */
LG_Properties clone_changeTexture(CGFtexture *newTexture);


/**
 
 
 Clones a context but changes the matrix for this context.
 
 */
LG_Properties clone_changeMatrix(GLdouble newMatrix[4][4]);

/**
 
 Clones a context but applies a rotation to the current matrix.
 
 */
LG_Properties clone_Rotate(double angle,LG_Axis axis);


/**
 
 Clones a context but applies a translation to the current matrix.
 
 */
LG_Properties clone_Translate(double dx,double dy, double dz);

/**
 
 Clones a context but applies a scaling operation to the current matrix.
 
 */
LG_Properties clone_Scale(double sx,double sy,double sz);


#pragma mark - Helper Methods


void LG_Properties::loadIdentity(){

    for (int col=0; col<4; col++) {
        for (int line=0; line<4; line++) {
            
            if (line==col) matrix[col][line]=1;
            else matrix[col][line]=0;
            
        }
    }

}


void LG_Properties::cloneMatrix(LG_Properties * contextToClone){
    
    for (int col=0; col<4; col++) {
        for (int line=0; line<4; line++) {
            matrix[col][line]=contextToClone->matrix[col][line];
        }
    }

}

void LG_Properties::cloneLightParameters(LG_Properties * contextToClone)
{

    for (int i=0; i<4; i++) {
        ambient[i]=contextToClone->ambient[i];
        diffuse[i]=contextToClone->diffuse[i];
        specular[i]=contextToClone->specular[i];
    }
    
    shininess=contextToClone->shininess;
    
}


void LG_Properties::cloneTexture(LG_Properties *context){

#error implement this

}
