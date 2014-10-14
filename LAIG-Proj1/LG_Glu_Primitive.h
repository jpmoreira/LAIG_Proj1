//
//  LG_Glu_Primitives.h
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 08/10/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#ifndef __LAIG_Proj1__LG_Glu_Primitives__
#define __LAIG_Proj1__LG_Glu_Primitives__

#include <GL/glu.h>
#include "LG_Primitive.h"

class LG_Glu_Primitive: public LG_Primitive {

protected:
    GLUquadric *quadric;

private:
 
    
    
    
    /**
     
     A method for configuring the GLUquadric object to be used in the drawing process
     
     
     */
    void configureQuadric();
    
public:
    LG_Glu_Primitive(LG_Node_Map *map,string identifier);
    LG_Glu_Primitive(LG_Node_Map *map,string identifier,LG_Appearance *app);
    
    

    
};

#endif /* defined(__LAIG_Proj1__LG_Glu_Primitives__) */
