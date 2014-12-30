//
//  LG_Tzaar.h
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 29/12/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#ifndef __LAIG_Proj1__LG_Tzaar__
#define __LAIG_Proj1__LG_Tzaar__

#include <stdio.h>
#include "LG_Game_State.h"
#include <CGFscene.h>
#include <CGFinterface.h>
#include "LG_ANF.h"



class LG_Tzaar: public CGFscene , public CGFinterface {
    
    LG_Game_State *state;

    
    string docNameForScene;
    string docNameForMenu;
    string docNameForShortMenu;
    
public:
    
    
    LG_ANF *scene_anf;
    LG_ANF *menu_anf;
    LG_ANF *short_menu_anf;
    
    
    //GCFscene
    
    void init();
    void display();
    void update(unsigned long millis);
    
    
    //CGFInterface
    void processKeyboard(unsigned char key, int x, int y);
    void processMouse(int button, int state, int x, int y);
    
    void defaultMouseProcessing(int button, int state, int x, int y);
    
    //setting names
    void setDocNameForScene(string name);
    void setDocNameForMenu(string name);
    void setDocNameForShortMenu(string name);
    
    
    //actions
    
    void draw(bool selectMode);
    void drawMenu();
    void showMenuButtonClicked();
    void startPlaying();
    void nodeSelected(LG_Node *node);
    void movementValidation(bool valid);
    void animationFinished(LG_Animation *);
    void gameOverResult(bool gameover);


};

#endif /* defined(__LAIG_Proj1__LG_Tzaar__) */
