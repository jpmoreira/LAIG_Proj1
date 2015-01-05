//
//  LG_State_Animating_Move.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 29/12/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_State_Animating_Move.h"
#include "LG_Tzaar.h"
#include "LG_Board_Place.h"
#include "LG_Move_Piece_Animation_State.h"
#include "LG_Move_Piece_Animation.h"
#include "LG_State_Waiting_Piece_Selection.h"
#include "LG_State_GameOver.h"

LG_Game_State * LG_State_Animating_Move::undo(){ return NULL; }

LG_Game_State * LG_State_Animating_Move::state(LG_Tzaar *tzaar){


	return new LG_State_Animating_Move(tzaar);

}

LG_State_Animating_Move::LG_State_Animating_Move(LG_Tzaar *tzaar) :LG_Game_State(tzaar){


	game->origin->setSelected(false);//stop animation

    if(!tzaar->movieMode){
        LG_Movement movement = LG_Movement(game->origin, game->destination);
        game->memorizedPlays.push_back(movement);
    }
    else{
        printf("");
    }
	game->origin->animations.push_back(new LG_Move_Piece_Animation_State(NULL, new LG_Move_Piece_Animation(NULL, game->origin, game->destination)));



}


LG_Game_State* LG_State_Animating_Move::animationFinished(LG_Animation *anim){

	LG_Move_Piece_Animation *move_anim = dynamic_cast<LG_Move_Piece_Animation *>(anim);

	if (!move_anim)return NULL;

	string s = game->lastCommand;

	if (!game->destination->piece){//if no piece at destination
		game->destination->piece = game->origin->piece;
		game->destination->nrPieces = game->origin->nrPieces;

	}

	else if (game->destination->piece->getColor() == game->origin->piece->getColor()){

		game->destination->nrPieces += game->origin->nrPieces;
	}
	else{

		game->destination->nrPieces = game->origin->nrPieces;
		game->destination->piece = game->origin->piece;

	}



	game->origin->nrPieces = 0;
	game->origin->piece = NULL;


	if (game->phase == phase1){

		game->phase = phase2;
		return this->cameraAnimationFinished();//do whatever it does

	}

	else if (game->playingColor == White){

		game->playingColor = Black;
		game->phase = phase1;
	}
	else if (game->playingColor == Black){

		game->playingColor = White;
		game->phase = phase1;
	}



	game->tellCameraToAnimate();


	//Verify GameOver

	return NULL;



}

LG_Game_State * LG_State_Animating_Move::cameraAnimationFinished(){


	Victory v = game->gameOver();

	game->origin = NULL;
	game->destination = NULL;

	if (v == VicNone) return LG_State_Waiting_Piece_Selection::state(game);

	return LG_State_GameOver::state(game);

}

LG_Game_State * LG_State_Animating_Move::drawMenu(bool selectMode){


	game->short_menu_anf->draw(selectMode);
	return NULL;

}