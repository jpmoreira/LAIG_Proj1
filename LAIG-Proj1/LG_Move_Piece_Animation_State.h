//
//  LG_Move_Piece_Animation_State.h
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 04/01/15.
//  Copyright (c) 2015 José Pedro Moreira. All rights reserved.
//

#ifndef __LAIG_Proj1__LG_Move_Piece_Animation_State__
#define __LAIG_Proj1__LG_Move_Piece_Animation_State__

#include <stdio.h>
#include "LG_AnimationState.h"

class LG_Board_Place;
class LG_Tzaar;
class LG_Move_Piece_Animation;

class LG_Move_Piece_Animation_State:public LG_AnimationState {
    
    

    
    double dx,dz;
    
public:
    LG_Move_Piece_Animation_State(LG_Node_Map *map,LG_Move_Piece_Animation *anim);
    void update(unsigned long timeNow);
};

#endif /* defined(__LAIG_Proj1__LG_Move_Piece_Animation_State__) */
