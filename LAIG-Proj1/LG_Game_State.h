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
    
    
    
    // events
    virtual void draw(bool selectMode);
    virtual void drawMenu(bool selectMode);
    virtual void update(unsigned long time);
    
    
    virtual void exitButtonClicked();
    virtual void startPlaying(int difficulty);
    virtual void gameFinished(int winner);
    
    //selection
    void nodeSelected(LG_Node *node);
    virtual void placeSelected(LG_Board_Place *place);
    virtual void currentPlayerPieceSelected(LG_Board_Place *place);
    virtual void oponentPlayerPieceSelected(LG_Board_Place *place);
    virtual void emptyPlaceSelected(LG_Board_Place *place);
    virtual void fullPlaceSelected(LG_Board_Place *place);
    virtual void buttonSelected(LG_Button *button);
    
    
    
    
    virtual void movementValidation(bool valid);
    virtual void animationFinished(LG_Animation *);
    virtual void processMouse(int button, int state, int x, int y);
    
    
    
};

#endif /* defined(__LAIG_Proj1__LG_Game_State__) */
