//
//  LG_State_Validating_Move.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 29/12/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_State_Validating_Move.h"
#include "LG_Tzaar.h"

LG_State_Validating_Move::LG_State_Validating_Move(LG_Tzaar *tzaar):LG_Game_State(tzaar){

    game->validateMove();

}