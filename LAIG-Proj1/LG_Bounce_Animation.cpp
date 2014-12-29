//
//  LG_Bounce_Animation.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 28/12/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_Bounce_Animation.h"
#include "LG_AnimationState.h"

#define LG_Bounce_Animation_ID_Prefix "LG_Bounce_Anim_"
#define LG_Bounce_Animation_Duration 10000000

#define initialVelocity 6.0
#define gravityConstant 9.8
#define dampeningFactorPerBounce 0.6
#define maxHeightCuttOff 0.05

int LG_Bounce_Animation::animNr=0;


LG_Bounce_Animation::LG_Bounce_Animation(LG_Node_Map *map):LG_Animation(map,identifForAnim(),LG_Bounce_Animation_Duration){


}


string LG_Bounce_Animation::identifForAnim(){


    char buffer[50];
    sprintf(buffer, "%s%d",LG_Bounce_Animation_ID_Prefix,animNr);
    
    return string(buffer);

}

#pragma mark - Inherit Methods

void LG_Bounce_Animation::update(unsigned long timeNow,LG_AnimationState *state){
    
    double timePassed=(state->timePassed(timeNow)/1000.);
    
    
    
    
    
    
    //notice that vi in this bounce is always initialVelocity*currentDampingFactor
    
    state->velocity=initialVelocity*state->currentDampingFactor-gravityConstant*timePassed;//v=vi-gt
    state->currentY=(initialVelocity*state->currentDampingFactor+state->velocity)/2.*timePassed;//y=(vi+v)*t/2
    
    
    
    
    //if it hitted the ground
    if (state->currentY<=0) {
        state->startTime=timeNow;
        state->currentY=0;//dont let it go below zero
        state->currentDampingFactor*=dampeningFactorPerBounce;//update dampening factor
        state->velocity=initialVelocity*state->currentDampingFactor;
    }
    
    double maximumHeight=(state->currentDampingFactor*initialVelocity)*(state->currentDampingFactor*initialVelocity)/(2*gravityConstant);//ymax=(vi*vi)/2g
    
    if (maximumHeight<maxHeightCuttOff) {//if the cutoff maxHeight has been reached restart the animation
        state->velocity=0;
        state->currentY=0;
        state->startTime=timeNow;
        state->currentDampingFactor=1.0;
    }
    

    state->translate(0, state->currentY, 0);
    
    

}
void LG_Bounce_Animation::configureInitialParameters(LG_AnimationState *state){


}