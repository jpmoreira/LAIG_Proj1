//
//  LG_Game_State.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 29/12/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_Game_State.h"
#include "LG_Tzaar.h"
#include "LG_Board_Place.h"
#include "LG_Button.h"

LG_Game_State::LG_Game_State(LG_Tzaar *game):game(game){
}


void LG_Game_State::draw(bool selectMode){}
void LG_Game_State::drawMenu(bool selectMode){}
void LG_Game_State::showMenuButtonClicked(){}
void LG_Game_State::startPlaying(){}

void LG_Game_State::movementValidation(bool valid){}
void LG_Game_State::animationFinished(LG_Animation *){}
void LG_Game_State::gameOverResult(bool gameover){}

void LG_Game_State::processMouse(int button, int state, int x, int y){

    game->defaultMouseProcessing(button, state, x, y);

}

#pragma mark - Selection

void LG_Game_State::nodeSelected(LG_Node *node){
    
    if (node==NULL)return;
    
    LG_Board_Place *place=dynamic_cast<LG_Board_Place *>(node);
    LG_Button *button=dynamic_cast<LG_Button *>(node);
    
    if (place){
    
        this->placeSelected(place);
        if (place->piece){
            this->fullPlaceSelected(place);
            
            LG_Board_Piece *piece=place->piece;
            if (piece->getColor()==game->playingColor) currentPlayerPieceSelected(place);
            else oponentPlayerPieceSelected(place);
            
        
        }
        else this->emptyPlaceSelected(place);
    
    
    }
    else if(button) this->buttonSelected(button);
    
    
    
}


void LG_Game_State::placeSelected(LG_Board_Place *place){
    

}


void LG_Game_State::emptyPlaceSelected(LG_Board_Place *place){

}
void LG_Game_State::fullPlaceSelected(LG_Board_Place *place){

}


void LG_Game_State::currentPlayerPieceSelected(LG_Board_Place *place){

}
void LG_Game_State::oponentPlayerPieceSelected(LG_Board_Place *place){

}
void LG_Game_State::buttonSelected(LG_Button *button){


}


