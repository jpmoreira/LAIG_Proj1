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
    
    
    LG_State_Animating_Move(LG_Tzaar *tzaar);
    
    
public:
    
    
    static LG_Game_State *state(LG_Tzaar *tzaar);
    

	LG_Game_State * undo();
    LG_Game_State * animationFinished(LG_Animation *);
    LG_Game_State * cameraAnimationFinished();
    LG_Game_State * drawMenu(bool selectMode);
};

#endif /* defined(__LAIG_Proj1__LG_State_Animating_Move__) */
