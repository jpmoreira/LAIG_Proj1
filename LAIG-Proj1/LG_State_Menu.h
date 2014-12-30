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
    
    void drawMenu(bool selectMode);
    
    void processMouse(int button, int state, int x, int y);
    
    //void nodeSelected(LG_Node *node);

};

#endif /* defined(__LAIG_Proj1__LG_State_Menu__) */
