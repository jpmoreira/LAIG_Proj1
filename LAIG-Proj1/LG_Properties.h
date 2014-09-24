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



typedef enum{

    xx_Axis,
    yy_Axis,
    zz_Axis

} LG_Axis;


typedef GLdouble LG_LightArray[4];

typedef GLdouble LG_Matrix[4][4];

#define LG_LightValue_Not_Set -1

#define LG_LightList_InitialValue {LG_LightValue_Not_Set,LG_LightValue_Not_Set,LG_LightValue_Not_Set,LG_LightValue_Not_Set}

#define LG_Matrix_InitialValue {LG_LightList_InitialValue,LG_LightList_InitialValue,LG_LightList_InitialValue,LG_LightList_InitialValue}


/**
 
 An Object to hold all the information related to the current state when iterating through the graph structure.
 
 */

class LG_Properties
{


    
    
public:
    
    //public for testing purposes
    LG_Matrix  matrix=LG_Matrix_InitialValue;
    LG_LightArray ambient=LG_LightList_InitialValue;
    LG_LightArray diffuse=LG_LightList_InitialValue;
    LG_LightArray specular=LG_LightList_InitialValue;
    GLdouble shininess=LG_LightValue_Not_Set;
    CGFtexture *texture=NULL;

    
    
    
    
    LG_Properties();
    /**
     
     Simple constructor. Properties that are not to be set should be set to NULL, with the exception of shininess that should be set to the value LG_Shininess_Not_Set
     
     
     */
    LG_Properties(LG_Matrix matrix,LG_LightArray amb,LG_LightArray diff,LG_LightArray spec,GLdouble shininess);
    
    
    void setTexture(CGFtexture *newText);
    
    
    
    
private:
    
    /**
     
     Clones a matrix and stores a copy in the matrix data member
     
     */
    
    inline void cloneMatrix(LG_Matrix matrixToClone);
    
    /**
     
     Clones a light array and stores it in the data member .
     
     
     */
    inline static void cloneLightArray(LG_LightArray source,LG_LightArray dest);
    

};


#endif /* defined(__LAIG_Proj1__Context__) */