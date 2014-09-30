//
//  LG_Torus.h
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 29/09/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#ifndef __LAIG_Proj1__LG_Torus__
#define __LAIG_Proj1__LG_Torus__

#include <stdio.h>
#include "LG_Primitive.h"

class LG_Torus: public LG_Primitive{

    
private:
    
    double innerRadius;
    double outerRadius;
    int slices;
    int loops;
    
    static int _LG_classIDNr;
    
public:
    
    
    LG_Torus(LG_Node_Map *map,TiXmlElement *elem);
    LG_Torus(LG_Node_Map *map,double inner,double outer,int sl,int loop);

};

#endif /* defined(__LAIG_Proj1__LG_Torus__) */
