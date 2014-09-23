//
//  Context.h
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 22/09/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#ifndef __LAIG_Proj1__Context__
#define __LAIG_Proj1__Context__

#include <stdio.h>
#include <GL/glew.h>
#include <CGFtexture.h>

#endif /* defined(__LAIG_Proj1__Context__) */

typedef enum{

    xx_Axis,
    yy_Axis,
    zz_Axis

} LG_Axis;


typedef GLdouble LG_LightArray[4];


/**
 
 An Object to hold all the information related to the current state when iterating through the graph structure.
 
 */

class LG_Properties
{

    GLdouble  matrix[4][4];
    LG_LightArray ambient;
    LG_LightArray diffuse;
    LG_LightArray specular;
    GLdouble shininess;
    CGFtexture *texture;
    
    
public:
    
    
    
    
    LG_Properties();
    
    LG_Properties(GLdouble *matrix,GLdouble amb[4],GLdouble diff[4],GLdouble spec[4],GLdouble shininess);
    void setTexture(CGFtexture *newText);
    
    
    
    /**
     * Clones a context. Creates a copy of the context.
     *
    */
    LG_Properties * clone();
    
    
    /**
     
     Clones a Context object but changes it's light component.
     
     */
    LG_Properties * clone_changeLight(GLdouble amb[4],GLdouble diff[4],GLdouble spec[4],GLdouble shininess);
    
    
    /**
     
     Clones a Context object but changes the texture.
     
     
     */
    LG_Properties * clone_changeTexture(CGFtexture *newTexture);
    
    
    /**
     
     
     Clones a context but changes the matrix for this context.
     
     */
    LG_Properties * clone_changeMatrix(GLdouble newMatrix[4][4]);
    
    /**
     
     Clones a context but applies a rotation to the current matrix.
     
     */
    LG_Properties * clone_Rotate(double angle,LG_Axis axis);
    
    
    /**
     
     Clones a context but applies a translation to the current matrix.
     
     */
    LG_Properties * clone_Translate(double dx,double dy, double dz);
    
    /**
     
     Clones a context but applies a scaling operation to the current matrix.
     
     */
    LG_Properties * clone_Scale(double sx,double sy,double sz);
    

    
private:
    /**
     
     Loads the identity matrix onto the matrix data member of this object
     
     
     */
    void loadIdentity();
    
    /**
     
     Clones the other contexts matrix
     
     */
    void cloneMatrix(LG_Properties *contextToClone);
    
    /**
     
     Clones all light parameters from one LG_Properties to another.
     
     
     */
    void cloneLightParameters(LG_Properties * contextToClone);
    
    /**
     
     Clones the texture parameters from one LG_Properties to another.
     
     */
    
    void cloneTexture(LG_Properties *context);
};