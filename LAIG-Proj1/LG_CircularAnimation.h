//
//  LG_CircularAnimation.h
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 28/10/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#ifndef __LAIG_Proj1__LG_CircularAnimation__
#define __LAIG_Proj1__LG_CircularAnimation__

#include <stdio.h>

#include "LG_Animation.h"

class LG_CircularAnimation:public LG_Animation {
    
    
public:
    

    LG_CircularAnimation(LG_Node_Map *map,TiXmlElement *elem);
    
    
    void apply(long int elapsedTime);
    
};

#endif /* defined(__LAIG_Proj1__LG_CircularAnimation__) */
