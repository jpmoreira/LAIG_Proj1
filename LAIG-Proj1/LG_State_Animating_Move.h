//
//  LG_State_Animating_Move.h
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 29/12/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#ifndef __LAIG_Proj1__LG_State_Animating_Move__
#define __LAIG_Proj1__LG_State_Animating_Move__

#include <stdio.h>

#include "LG_Game_State.h"

class LG_State_Animating_Move: public LG_Game_State {
    
    
    
public:

    LG_State_Animating_Move(LG_Tzaar *tzaar);
    
    void animationFinished(LG_Animation *);
};

#endif /* defined(__LAIG_Proj1__LG_State_Animating_Move__) */
