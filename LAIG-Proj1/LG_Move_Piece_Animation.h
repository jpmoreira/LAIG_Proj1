//
//  LG_Move_Piece_Animation.h
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 04/01/15.
//  Copyright (c) 2015 José Pedro Moreira. All rights reserved.
//

#ifndef __LAIG_Proj1__LG_Move_Piece_Animation__
#define __LAIG_Proj1__LG_Move_Piece_Animation__

#include <stdio.h>
#include "LG_Animation.h"
#define Move_Piece_Animation_Duration 2.0


class LG_Board_Place;


class LG_Move_Piece_Animation: public LG_Animation {
    
    
    
public:
    
    LG_Board_Place *origin,*destination;
    
    LG_Move_Piece_Animation(LG_Node_Map *map,LG_Board_Place *orig,LG_Board_Place *dest);
    
    void update(unsigned long timeNow,LG_AnimationState *state);
    void configureInitialParameters(LG_AnimationState *state);
    
    ~LG_Move_Piece_Animation();
};

#endif /* defined(__LAIG_Proj1__LG_Move_Piece_Animation__) */
