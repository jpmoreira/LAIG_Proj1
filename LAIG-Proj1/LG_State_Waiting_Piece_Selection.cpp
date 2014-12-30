//
//  LG_State_Waiting_Piece_Selection.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 29/12/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_State_Waiting_Piece_Selection.h"
#include "LG_Board_Place.h"
#include "LG_Tzaar.h"



LG_State_Waiting_Piece_Selection::LG_State_Waiting_Piece_Selection(LG_Tzaar *tzaar):LG_Game_State(tzaar){}


void LG_State_Waiting_Piece_Selection::nodeSelected(LG_Node *node){

    if (node==NULL)return;
    
    
    
    LG_Board_Place *place=dynamic_cast<LG_Board_Place *>(node);
    if (place) {
    
        LG_Board_Piece *piece=place->piece;
        
        if(!piece || piece->getColor()!=game->playingColor)return;//if there is no piece or the piece selected is not one we are supposed to select
        
        place->toggleSelected();
        
    }
    
    else{
    
    
    }

}