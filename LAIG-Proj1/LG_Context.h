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
#include <OpenGL/OpenGL.h>
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

class LG_Context
{

    GLdouble  matrix[4][4];
    GLdouble ambient[4];
    GLdouble diffuse[4];
    GLdouble specular[4];
    GLdouble shininess;
    CGFtexture *texture;
    
    
public:
    
    
    LG_Context();
    
    LG_Context(GLdouble *matrix,GLdouble amb[4],GLdouble diff[4],GLdouble spec[4],GLdouble shininess);
    void setTexture(CGFtexture *newText);
    
    
    
    /**
     * Clones a context. Creates a copy of the context.
     *
    */
    LG_Context * clone();
    
    
    /**
     
     Clones a Context object but changes it's light component.
     
     */
    LG_Context * clone_changeLight(GLdouble amb[4],GLdouble diff[4],GLdouble spec[4],GLdouble shininess);
    
    
    /**
     
     Clones a Context object but changes the texture.
     
     
     */
    LG_Context * clone_changeTexture(CGFtexture *newTexture);
    
    
    /**
     
     
     Clones a context but changes the matrix for this context.
     
     */
    LG_Context * clone_changeMatrix(GLdouble newMatrix[4][4]);
    
    /**
     
     Clones a context but applies a rotation to the current matrix.
     
     */
    LG_Context * clone_Rotate(double angle,LG_Axis axis);
    
    
    /**
     
     Clones a context but applies a translation to the current matrix.
     
     */
    LG_Context * clone_Translate(double dx,double dy, double dz);
    
    /**
     
     Clones a context but applies a scaling operation to the current matrix.
     
     */
    LG_Context * clone_Scale(double sx,double sy,double sz);
    

    
private:
    /**
     
     Loads the identity matrix onto the matrix data member of this object
     
     
     */
    void loadIdentity();
    
    /**
     
     Clones the other contexts matrix
     
     */
    void cloneMatrix(LG_Context *contextToClone);
    
    void cloneLightArray(GLdouble * lightArray);
};