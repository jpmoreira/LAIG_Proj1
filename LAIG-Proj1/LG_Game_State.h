//
//  LG_Game_State.h
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 29/12/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#ifndef __LAIG_Proj1__LG_Game_State__
#define __LAIG_Proj1__LG_Game_State__

#include <stdio.h>


class LG_Node;
class LG_Tzaar;
class LG_Animation;
class LG_Board_Place;
class LG_Button;
class LG_Game_State {

protected:
    
    LG_Tzaar *game;
    
public:
    
    LG_Game_State(LG_Tzaar *game);
    
	virtual LG_Game_State *undo();
    
    
    // events
    virtual LG_Game_State * draw(bool selectMode);
    virtual LG_Game_State * drawMenu(bool selectMode);
    virtual LG_Game_State * update(unsigned long time);
    
    
    virtual LG_Game_State * exitButtonClicked();
    virtual LG_Game_State * startPlaying(int difficulty);
    virtual LG_Game_State * gameFinished(int winner);
    
    //selection
    LG_Game_State * nodeSelected(LG_Node *node);
    virtual LG_Game_State * placeSelected(LG_Board_Place *place);
    virtual LG_Game_State * currentPlayerPieceSelected(LG_Board_Place *place);
    virtual LG_Game_State * oponentPlayerPieceSelected(LG_Board_Place *place);
    virtual LG_Game_State * emptyPlaceSelected(LG_Board_Place *place);
    virtual LG_Game_State * fullPlaceSelected(LG_Board_Place *place);
    virtual LG_Game_State * buttonSelected(LG_Button *button);
    
    
    
    
    virtual LG_Game_State * movementValidation(bool valid);
    virtual LG_Game_State * animationFinished(LG_Animation *);
    virtual LG_Game_State * processMouse(int button, int state, int x, int y);
    
    
    virtual LG_Game_State * cameraAnimationFinished();
    
    
    virtual ~LG_Game_State();
    
    
    
};

#endif /* defined(__LAIG_Proj1__LG_Game_State__) */
