//
//  LG_Game_State.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 29/12/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_State_Waiting_Piece_Selection.h"
#include "LG_Game_State.h"
#include "LG_Tzaar.h"
#include "LG_Board_Place.h"
#include "LG_Button.h"
#include "LG_State_Menu.h"
#include "LG_Clock.h"
#include "LG_VictoryCounter.h"

LG_Game_State::LG_Game_State(LG_Tzaar *game):game(game){
}


LG_Game_State * LG_Game_State::draw(bool selectMode){return NULL;}
LG_Game_State * LG_Game_State::drawMenu(bool selectMode){return NULL;}
LG_Game_State * LG_Game_State::update(unsigned long time){

    game->scene_anf->getAnimations()->update(time);
    game->scene_anf->graph->update(time);
    
    game->short_menu_anf->graph->update(time);
    
    game->scene_anf->getCamerasContainer()->getCurrentCamera()->update(time);
    
    return NULL;

}

LG_Game_State * LG_Game_State::gameFinished(int winner){
    
    LG_VictoryCounter* counter =dynamic_cast<LG_VictoryCounter *>( game->short_menu_anf->graph->nodeWithID(LG_VictoryCounter_ID));
    
    counter->updateNrVictories(game->nrVictoriesPlayerA, game->nrVictoriesPlayerB);
    return NULL;
}

LG_Game_State * LG_Game_State::exitButtonClicked(){

    
    game->scene_anf->replaceGraph();
    LG_Clock *clock=dynamic_cast<LG_Clock *>(game->short_menu_anf->graph->nodeWithID(LG_Clock_ID));
    clock->reset();
    game->nrVictoriesPlayerA=0;
    game->nrVictoriesPlayerB=0;
    game->phase=phase1;
    game->playingColor=White;
    
    return LG_State_Menu::state(game);

}
LG_Game_State * LG_Game_State::startPlaying(int difficulty){return NULL;}

LG_Game_State * LG_Game_State::movementValidation(bool valid){return NULL;}
LG_Game_State * LG_Game_State::animationFinished(LG_Animation *){return NULL;}

LG_Game_State * LG_Game_State::processMouse(int button, int state, int x, int y){

    game->defaultMouseProcessing(button, state, x, y);
    return NULL;

}

#pragma mark - Selection

LG_Game_State * LG_Game_State::nodeSelected(LG_Node *node){
    
    if (node==NULL)return NULL;
    
    LG_Board_Place *place=dynamic_cast<LG_Board_Place *>(node);
    LG_Button *button=dynamic_cast<LG_Button *>(node);
    
    if (place){
        
        LG_Game_State *st1,*st2,*st3 = NULL;
    
        st1=this->placeSelected(place);
        if (place->piece){
            
            
            
            st2=this->fullPlaceSelected(place);
            
            LG_Board_Piece *piece=place->piece;
            if (piece->getColor()==game->playingColor) st3=currentPlayerPieceSelected(place);
            else st3=oponentPlayerPieceSelected(place);
            
        
        }
        else st2=this->emptyPlaceSelected(place);
    
        
        
        if (st1) return st1;
        else if(st2) return st2;
        return st3;
    
    }
    else if(button) return this->buttonSelected(button);
    
    
    
    return NULL;
    
}

LG_Game_State* LG_Game_State::undo(){
	if (!(this->game->mode == computer_vs_computer))		//guarantee that exists a player
	{

		int lastPlayedIndex = game->memorizedPlays.size() - 1;

		if (this->game->mode == player_vs_computer)
		{
			while (lastPlayedIndex >= 0){
				if (game->memorizedPlays.at(lastPlayedIndex).getFrom()->piece->getColor() != White)
				{
					game->doUndo(game->memorizedPlays.at(lastPlayedIndex));
					game->memorizedPlays.pop_back();
					lastPlayedIndex--;
				}
				else{
					game->doUndo(game->memorizedPlays.at(lastPlayedIndex));
					game->memorizedPlays.pop_back();
					lastPlayedIndex--;
					break;
				}
			}
		}
		else if (lastPlayedIndex >= 0 && this->game->mode == player_vs_player)
		{
			game->doUndo(game->memorizedPlays.at(lastPlayedIndex));
			game->memorizedPlays.pop_back();
		}


	}
	//game->origin = NULL;
	//game->destination = NULL;
	return LG_State_Waiting_Piece_Selection::state(game);
}

LG_Game_State * LG_Game_State::placeSelected(LG_Board_Place *place){
    
    
    return NULL;
    

}


LG_Game_State * LG_Game_State::emptyPlaceSelected(LG_Board_Place *place){
    
    
    return NULL;

}
LG_Game_State * LG_Game_State::fullPlaceSelected(LG_Board_Place *place){
    
    return NULL;

}


LG_Game_State * LG_Game_State::currentPlayerPieceSelected(LG_Board_Place *place){
    
    return NULL;

}
LG_Game_State * LG_Game_State::oponentPlayerPieceSelected(LG_Board_Place *place){
    
    return NULL;

}
LG_Game_State * LG_Game_State::buttonSelected(LG_Button *button){


    button->setSelected(true);
    
    return NULL;
    
}

LG_Game_State::~LG_Game_State(){

}


#pragma mark - Camera


LG_Game_State * LG_Game_State::cameraAnimationFinished(){

    
    return NULL;
}


