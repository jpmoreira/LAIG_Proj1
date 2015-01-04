//
//  LG_State_Selected_Piece.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 29/12/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_State_Waiting_Place_Selection.h"
#include "LG_Board_Place.h"
#include "LG_Tzaar.h"
#include "LG_State_Animating_Move.h"




LG_State_Waiting_Place_Selection::LG_State_Waiting_Place_Selection(LG_Tzaar *tzaar):LG_Game_State(tzaar){}




LG_Game_State * LG_State_Waiting_Place_Selection::state(LG_Tzaar *tzaar){
    
    return new LG_State_Waiting_Place_Selection(tzaar);
    
    
}

LG_Game_State * LG_State_Waiting_Place_Selection::currentPlayerPieceSelected(LG_Board_Place *place){

    if(place->isSelected()){
        
        place->toggleSelected();
        return new LG_State_Waiting_Piece_Selection(game);
    
    }
    
    else if (!place->isSelected() && game->phase==phase1)return NULL;//if we are on phase 1 and trying to reforce a piece of our own
    else{
    
        game->destination=place;
        
        return this->validateMoveAndHandleResult();
        
    
    }
    
    return NULL;

}
LG_Game_State * LG_State_Waiting_Place_Selection::oponentPlayerPieceSelected(LG_Board_Place *place){
    
    game->destination=place;
    
    return this->validateMoveAndHandleResult();
    
    
    

}
LG_Game_State * LG_State_Waiting_Place_Selection::emptyPlaceSelected(LG_Board_Place *place){
    
    game->destination=place;
    
    return this->validateMoveAndHandleResult();
    

}
LG_Game_State * LG_State_Waiting_Place_Selection::drawMenu(bool selectMode){

    game->short_menu_anf->draw(selectMode);
    
    return NULL;
}


#pragma mark - Helper Methods

LG_Game_State * LG_State_Waiting_Place_Selection::validateMoveAndHandleResult(){
    
    bool valid=game->validateMove();
    
    if (valid && game->destination!=NULL) return new LG_State_Animating_Move(game);
    
    else return new LG_State_Waiting_Piece_Selection(game);
    
    

}