//
//  LG_State_Checking_GameOver.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 29/12/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_State_GameOver.h"
#include "LG_Tzaar.h"
#include "LG_Clock.h"
#include "LG_State_Waiting_Piece_Selection.h"



LG_State_GameOver::LG_State_GameOver(LG_Tzaar *tzaar):LG_Game_State(tzaar){
    
    



}


LG_Game_State * LG_State_GameOver::state(LG_Tzaar *tzaar){

    
    Victory v=tzaar->gameOver();
    
    tzaar->scene_anf->replaceGraph();
    LG_Clock *clock=dynamic_cast<LG_Clock *>(tzaar->short_menu_anf->graph->nodeWithID(LG_Clock_ID));
    clock->reset();
    tzaar->playingColor=White;
    tzaar->phase=phase1;
    
    
    if(tzaar->origin)tzaar->origin->setSelected(false);
    if(tzaar->destination)tzaar->destination->setSelected(false);
    
    
    if (v==VicWhite) {
        tzaar->nrVictoriesPlayerA++;
    }
    else{
        tzaar->nrVictoriesPlayerB++;
    }
    
    printf("gameover with phase=%d turn=%d\n",tzaar->phase, tzaar->playingColor);
    
    return LG_State_Waiting_Piece_Selection::state(tzaar);

}