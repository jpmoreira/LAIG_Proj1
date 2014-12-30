//
//  LG_Game_State.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 29/12/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_Game_State.h"
#include "LG_Tzaar.h"

LG_Game_State::LG_Game_State(LG_Tzaar *game):game(game){
}


void LG_Game_State::draw(bool selectMode){}
void LG_Game_State::drawMenu(){}
void LG_Game_State::showMenuButtonClicked(){}
void LG_Game_State::startPlaying(){}
void LG_Game_State::nodeSelected(LG_Node *node){}
void LG_Game_State::movementValidation(bool valid){}
void LG_Game_State::animationFinished(LG_Animation *){}
void LG_Game_State::gameOverResult(bool gameover){}

void LG_Game_State::processMouse(int button, int state, int x, int y){

    game->defaultMouseProcessing(button, state, x, y);

}