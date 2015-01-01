//
//  LG_State_Menu.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 29/12/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_State_Menu.h"
#include "LG_Tzaar.h"
#include "LG_Button.h"

#define playButtonID "playButton"


LG_State_Menu::LG_State_Menu(LG_Tzaar *tzaar):LG_Game_State(tzaar){


}


#pragma mark - Actions


void LG_State_Menu::drawMenu(bool selectMode){
    
    this->game->menu_anf->draw(selectMode);


}


void LG_State_Menu::buttonSelected(LG_Button *button){

    button->toggleSelected();

}

