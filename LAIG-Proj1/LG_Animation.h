//
//  LG_Animation.h
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 28/10/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#ifndef __LAIG_Proj1__LG_Animation__
#define __LAIG_Proj1__LG_Animation__

#include <stdio.h>

#include "LG_Parsable_Node.h"

class LG_Animation: public LG_Parsable_Node {
    
    
public:
    
    
    virtual void apply()=0;
    
    LG_Animation(LG_Node_Map *map,string identifier);
    
    
};

#endif /* defined(__LAIG_Proj1__LG_Animation__) */


