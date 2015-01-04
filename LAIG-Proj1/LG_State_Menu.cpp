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
#include "LG_State_Waiting_Piece_Selection.h"

#define playButtonID "playButton"


LG_State_Menu::LG_State_Menu(LG_Tzaar *tzaar):LG_Game_State(tzaar){
    


}


#pragma mark - Actions


LG_Game_State * LG_State_Menu::drawMenu(bool selectMode){
    
    this->game->menu_anf->draw(selectMode);
    
    return NULL;


}


LG_Game_State * LG_State_Menu::update(unsigned long time){
    
    return NULL;

}


LG_Game_State * LG_State_Menu::startPlaying(int difficulty)
{
	switch (difficulty)
	{
	case 1:
		game->difficulty = easy;
		break;
	case 2:
		game->difficulty = medium;
		break;
	default:
		game->difficulty = hard;
	}
	
    return LG_State_Waiting_Piece_Selection::state(game);
}

LG_Game_State * LG_State_Menu::processMouse(int button, int state, int x, int y){

    return NULL;
}


LG_Game_State * LG_State_Menu::exitButtonClicked(){

    exit(0);//exit program
    return NULL;

}