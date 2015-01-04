//
//  LG_Move_Piece_Animation.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 04/01/15.
//  Copyright (c) 2015 José Pedro Moreira. All rights reserved.
//

#include "LG_Move_Piece_Animation.h"
#define LG_Move_Animation_Identifier "LG_Move_Piece_Identif"


LG_Move_Piece_Animation::LG_Move_Piece_Animation(LG_Node_Map *map,LG_Board_Place *orig,LG_Board_Place *dest):LG_Animation(map,LG_Move_Animation_Identifier,Move_Piece_Animation_Duration),origin(orig),destination(dest){


}

void LG_Move_Piece_Animation::update(unsigned long timeNow,LG_AnimationState *state){
    
    
    

}
void LG_Move_Piece_Animation::configureInitialParameters(LG_AnimationState *state){


}