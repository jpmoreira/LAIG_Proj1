//
//  LG_Move_Piece_Animation_State.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 04/01/15.
//  Copyright (c) 2015 José Pedro Moreira. All rights reserved.
//

#include "LG_Move_Piece_Animation_State.h"
#include "LG_Board_Place.h"
#include "LG_Tzaar.h"
#include "LG_Move_Piece_Animation.h"
#include <math.h>


LG_Move_Piece_Animation_State::LG_Move_Piece_Animation_State(LG_Node_Map *map,LG_Move_Piece_Animation *anim):LG_AnimationState(map,anim,(LG_Node *)anim->origin){



    double xOrigin=0.1157*anim->origin->x+0.1157/2.0*abs(anim->origin->y-5);
    double xDest=0.1157*anim->destination->x+0.1157/2.0*abs(anim->destination->y-5);
    
    double zOrigin=0.2004*anim->origin->y;
    double zDest=0.2004*anim->destination->y;
    
    dx=xDest-xOrigin;
    dz=zDest-zOrigin;
    
    
    
}


void LG_Move_Piece_Animation_State::update(unsigned long timeNow){

    if (!started){
        started=true;
        startTime=timeNow;
    }
    
    if (timeNow>startTime+1000*Move_Piece_Animation_Duration) {
        notifyOfFinish();
        return;
    }
    
    
    
    
    double percentagePassed=(timeNow-startTime)/1000.;
    percentagePassed/=Move_Piece_Animation_Duration;
    
    
    double dy=0.5*sin(M_PI*percentagePassed);

    translate(2*dx*percentagePassed, dy, dz*percentagePassed);
    
    
    
    

    

}