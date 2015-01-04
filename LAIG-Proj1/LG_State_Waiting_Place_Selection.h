//
//  LG_State_Selected_Piece.h
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 29/12/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#ifndef __LAIG_Proj1__LG_State_Waiting_Place_Selection__
#define __LAIG_Proj1__LG_State_Waiting_Place_Selection__

#include <stdio.h>

#include "LG_Game_State.h"

class LG_State_Waiting_Place_Selection: public LG_Game_State{
    
    
    LG_State_Waiting_Place_Selection(LG_Tzaar *tzaar);
    
public:
    
   static LG_Game_State * state(LG_Tzaar *tzaar);
    
    LG_Game_State * currentPlayerPieceSelected(LG_Board_Place *place);
    LG_Game_State * oponentPlayerPieceSelected(LG_Board_Place *place);
    LG_Game_State * emptyPlaceSelected(LG_Board_Place *place);
    LG_Game_State * drawMenu(bool selectMode);
    
    
    LG_Game_State * validateMoveAndHandleResult();

};

#endif /* defined(__LAIG_Proj1__LG_State_Selected_Piece__) */
