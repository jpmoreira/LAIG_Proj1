//
//  LG_Bounce_Animation.h
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 28/12/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#ifndef __LAIG_Proj1__LG_Bounce_Animation__
#define __LAIG_Proj1__LG_Bounce_Animation__

#include "LG_Animation.h"

#include <stdio.h>


class LG_Bounce_Animation: public LG_Animation {
    
    
public:
    virtual void update(unsigned long timeNow,LG_AnimationState *state);
    virtual void configureInitialParameters(LG_AnimationState *state);
    
    static int animNr;
    static string identifForAnim();
    
    LG_Bounce_Animation(LG_Node_Map *map);

};




#endif /* defined(__LAIG_Proj1__LG_Bounce_Animation__) */
