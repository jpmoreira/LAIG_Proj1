//
//  LG_State_Waiting_Piece_Selection.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 29/12/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_State_Waiting_Piece_Selection.h"

#include "LG_State_Waiting_Place_Selection.h"
#include "LG_State_Animating_Move.h"
#include "LG_Board_Place.h"
#include "LG_Tzaar.h"



LG_Game_State * LG_State_Waiting_Piece_Selection::state(LG_Tzaar *tzaar){

    bool computerPlaying=tzaar->mode==player_vs_computer && tzaar->playingColor==Black;
    computerPlaying = (computerPlaying || tzaar->mode==computer_vs_computer);
    
    if (!computerPlaying) {
        return new LG_State_Waiting_Piece_Selection(tzaar);
    }
    
    else{
    
        vector<LG_Board_Place *> moves=tzaar->chooseMove();
        
        tzaar->origin=moves[0];
        tzaar->destination=moves[1];
        
        return LG_State_Animating_Move::state(tzaar);
        
    
    }


}

LG_State_Waiting_Piece_Selection::LG_State_Waiting_Piece_Selection(LG_Tzaar *tzaar):LG_Game_State(tzaar){


    

}



LG_Game_State * LG_State_Waiting_Piece_Selection::currentPlayerPieceSelected(LG_Board_Place *place){

    place->toggleSelected();
    
    if (place->isSelected()){
        
        game->origin=place;
        return LG_State_Waiting_Place_Selection::state(game);
        
    }
    
    return NULL;

}

LG_Game_State * LG_State_Waiting_Piece_Selection::drawMenu(bool selectMode){

    game->short_menu_anf->draw(selectMode);
    
    return NULL;

}
