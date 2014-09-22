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

class Context
{

    GLdouble  matrix[4][4];
    GLdouble ambient[4];
    GLdouble diffuse[4];
    GLdouble specular[4];
    GLdouble shininess;
    CGFtexture *texture;
    
    
public:
    
    Context(GLdouble *matrix,GLdouble amb[4],GLdouble diff[4],GLdouble spec[4],GLdouble shininess);
    void setTexture(CGFtexture *newText);
    
    Context clone();
    Context clone_changeLight(GLdouble amb[4],GLdouble diff[4],GLdouble spec[4],GLdouble shininess);
    Context clone_changeTexture(CGFtexture *newTexture);
    Context clone_changeMatrix(GLdouble newMatrix[4][4]);
    Context clone_Rotate(double angle,LG_Axis axis);
    Context clone_Translate(double dx,double dy, double dz);
    Context clone_Scale(double sx,double sy,double sz);
    

};