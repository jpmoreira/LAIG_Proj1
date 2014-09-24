//
//  Context.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 22/09/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_Properties.h"
#include <GL/glew.h>





#pragma mark - Constructors


LG_Properties::LG_Properties(){
    
    


    
    

}


LG_Properties::LG_Properties(LG_Matrix matrix,LG_LightArray amb,LG_LightArray diff,LG_LightArray spec,GLdouble shininess):shininess(shininess){


    
    this->cloneMatrix(matrix);
    if (amb) {
        LG_Properties::cloneLightArray(amb, ambient);
    }
    if (diff) {
        LG_Properties::cloneLightArray(diff, diffuse);
    }
    if (spec) {
        LG_Properties::cloneLightArray(spec, specular);
    }

    if (this->shininess<0)this->shininess=LG_LightValue_Not_Set;//dont allow any negative value but LG_Shininess_Not_Set
    
}




#pragma mark - Helper Methods


void LG_Properties::cloneMatrix(LG_Matrix matrix){
    
    for (int col=0; col<4; col++) {
        for (int line=0; line<4; line++) {
            this->matrix[col][line]=matrix[col][line];
        }
    }

}


void LG_Properties::cloneLightArray(GLdouble *source, GLdouble *dest){
    
    for (int i=0; i<4; i++) dest[i]=source[i];
}




