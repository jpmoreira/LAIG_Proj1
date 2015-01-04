//
//  LG_State_Menu.h
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 29/12/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#ifndef __LAIG_Proj1__LG_State_Menu__
#define __LAIG_Proj1__LG_State_Menu__

#include <stdio.h>
#include "LG_Game_State.h"

class LG_State_Menu: public LG_Game_State {
    
    
    
    
public:
    
    LG_State_Menu(LG_Tzaar *tzaar);
    
    LG_Game_State * drawMenu(bool selectMode);
    
    LG_Game_State * update(unsigned long time);
    //void processMouse(int button, int state, int x, int y);
    
    //void nodeSelected(LG_Node *node);
    

	LG_Game_State * startPlaying(int difficulty);
    
    LG_Game_State * processMouse(int button, int state, int x, int y);
    
    LG_Game_State * exitButtonClicked();
    
};

#endif /* defined(__LAIG_Proj1__LG_State_Menu__) */
