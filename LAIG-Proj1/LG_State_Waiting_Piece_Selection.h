//
//  LG_State_Waiting_Piece_Selection.h
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 29/12/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#ifndef __LAIG_Proj1__LG_State_Waiting_Piece_Selection__
#define __LAIG_Proj1__LG_State_Waiting_Piece_Selection__

#include <stdio.h>

#include "LG_Game_State.h"

class LG_State_Waiting_Piece_Selection: public LG_Game_State {
    
    
    LG_State_Waiting_Piece_Selection(LG_Tzaar *tzaar);
    
public:
    

    
    static LG_Game_State * state(LG_Tzaar *tzaar);
    
    LG_Game_State * currentPlayerPieceSelected(LG_Board_Place *place);
    LG_Game_State * drawMenu(bool selectMode);
    
    
};
#endif /* defined(__LAIG_Proj1__LG_State_Waiting_Piece_Selection__) */
