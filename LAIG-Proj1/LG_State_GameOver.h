//
//  LG_State_Checking_GameOver.h
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 29/12/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#ifndef __LAIG_Proj1__LG_State_GameOver__
#define __LAIG_Proj1__LG_State_GameOver__

#include <stdio.h>
#include "LG_Game_State.h"


class LG_Tzaar;


class LG_State_GameOver: public LG_Game_State {
    
    
     LG_State_GameOver(LG_Tzaar *game);
    
public:
    
    static LG_Game_State * state(LG_Tzaar *tzaar);

};

#endif /* defined(__LAIG_Proj1__LG_State_Checking_GameOver__) */
