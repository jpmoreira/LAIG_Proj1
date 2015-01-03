//
//  LG_State_Waiting_Piece_Selection.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 29/12/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_State_Waiting_Piece_Selection.h"
#include "LG_State_Waiting_Place_Selection.cpp"
#include "LG_Board_Place.h"
#include "LG_Tzaar.h"



LG_State_Waiting_Piece_Selection::LG_State_Waiting_Piece_Selection(LG_Tzaar *tzaar):LG_Game_State(tzaar){}



void LG_State_Waiting_Piece_Selection::currentPlayerPieceSelected(LG_Board_Place *place){

    place->toggleSelected();
    
    if (place->isSelected()){
        
        game->origin=place;
        game->changeState(new LG_State_Waiting_Place_Selection(game));
        
    }

}

void LG_State_Waiting_Piece_Selection::drawMenu(bool selectMode){

    game->short_menu_anf->draw(selectMode);

}
