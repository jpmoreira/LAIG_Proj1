//
//  LG_State_Selected_Piece.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 29/12/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_State_Waiting_Place_Selection.h"
#include "LG_State_Waiting_Piece_Selection.h"
#include "LG_State_Validating_Move.h"
#include "LG_Board_Place.h"
#include "LG_Tzaar.h"
#include "LG_State_Animating_Move.h"


LG_State_Waiting_Place_Selection::LG_State_Waiting_Place_Selection(LG_Tzaar *tzaar):LG_Game_State(tzaar){}


void LG_State_Waiting_Place_Selection::currentPlayerPieceSelected(LG_Board_Place *place){

    if(place->isSelected()){
        
        place->toggleSelected();
        game->changeState(new LG_State_Waiting_Piece_Selection(game));
    
    }
    
    else if (!place->isSelected() && game->phase==phase1)return;//if we are on phase 1 and trying to reforce a piece of our own
    else{
    
        game->destination=place;
        
        this->validateMoveAndHandleResult();
        
    
    }
    

}
void LG_State_Waiting_Place_Selection::oponentPlayerPieceSelected(LG_Board_Place *place){
    
    game->destination=place;
    
    this->validateMoveAndHandleResult();
    

}
void LG_State_Waiting_Place_Selection::emptyPlaceSelected(LG_Board_Place *place){
    
    game->destination=place;
    
    this->validateMoveAndHandleResult();

}
void LG_State_Waiting_Place_Selection::drawMenu(bool selectMode){

    game->short_menu_anf->draw(selectMode);
}


#pragma mark - Helper Methods

void LG_State_Waiting_Place_Selection::validateMoveAndHandleResult(){
    
    bool valid=game->validateMove();
    
    if (valid && game->destination!=NULL) game->changeState(new LG_State_Animating_Move(game));
    
    else game->changeState(new LG_State_Waiting_Piece_Selection(game));
    
    

}