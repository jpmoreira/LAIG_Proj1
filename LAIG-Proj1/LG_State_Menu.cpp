//
//  LG_State_Menu.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 29/12/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_State_Menu.h"
#include "LG_Tzaar.h"


LG_State_Menu::LG_State_Menu(LG_Tzaar *tzaar):LG_Game_State(tzaar){


}


#pragma mark - Actions


void LG_State_Menu::drawMenu(){
    
    this->game->menu_anf->draw();


}


void LG_State_Menu::processMouse(int button, int state, int x, int y){


    
    
}