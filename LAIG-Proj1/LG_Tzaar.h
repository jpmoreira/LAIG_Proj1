//
//  LG_Tzaar.h
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 29/12/14.
//  Copyright (c) >2014 José Pedro Moreira. All rights reserved.
//

#ifndef __LAIG_Proj1__LG_Tzaar__
#define __LAIG_Proj1__LG_Tzaar__



#include <stdio.h>
#include "LG_Game_State.h"
#include <CGFscene.h>
#include <CGFinterface.h>
#include "LG_ANF.h"
#include "LG_Movement.h"
#include <vector>



class LG_Socket;


typedef enum{


	player_vs_player,
	player_vs_computer,
	computer_vs_computer

} GameMode;

typedef enum {

	easy,
	medium,
	hard


} Difficulty;

typedef enum{

	phase1,
	phase2

} GamePhase;

typedef enum {

	VicNone,
	VicWhite,
	VicBlack

} Victory;

class LG_Tzaar : public CGFscene, public CGFinterface {


    
    //state design pattern
    LG_Game_State *state;
	vector<LG_Movement> memorizedPlays;

	
    
    

    
    
public:
    
    bool cameraAnimationActive;
	string lastCommand;
    int nrVictoriesPlayerA,nrVictoriesPlayerB;
    
	static LG_Tzaar *currentTzaar;

	LG_Tzaar();


	string docNameForScene;
	string docNameForMenu;
	string docNameForShortMenu;

	std::map<string, void(LG_Tzaar::*)() > invocationMapNoArgs;
	std::map<string, void(LG_Tzaar::*)(int) > invocationMapWithArgs;


	LG_Socket *sock;


    //loading stuff
    
    void loadScene();
    void loadMenu();
    void loadShortMenu();
    
    void reloadSceneGraph();
    




    
    
	//Game settings


	GameMode mode;
	Difficulty difficulty;
	GamePhase phase;
	Color playingColor;


	//singleton
	static LG_Tzaar * getCurrentTzaar();


	LG_ANF *scene_anf;
	LG_ANF *menu_anf;
	LG_ANF *short_menu_anf;


	//movement setup
	LG_Board_Place *origin;
	LG_Board_Place *destination;





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


	//picking

	void performPicking(int x, int y);
	LG_Node* processHits(GLint hits, GLuint buffer[]);


	//actions

	void draw(bool selectMode);
	void drawMenu(bool selectMode);
	void showMenuButtonClicked();

	void nodeSelected(LG_Node *node);
	void movementValidation(bool valid);
	void animationFinished(LG_Animation *);
	void gameEnded(int winner);


	//button actions

	void changeCameraClicked();
    void exitButtonClicked();
	void changeSceneClicked();
	void playClicked(int difficulty);
	void setModeClicked(int mode);
	void undoButtonClicked();


	//reflection

	void initReflection();
	void invoke(string method, int param = 0);


	//prolog communication routines
	bool validateMove();
	bool validateMoveFOR_TESTS(int x1, int z1, int x2, int z2);

	vector<LG_Board_Place *> chooseMove();
	
	Victory gameOver();
	string gameOverFOR_TESTS(string query);

	//helper methods

	string boardString();
    
    
    void cameraAnimationFinished();


    void tellCameraToAnimate();
	void doUndo(LG_Movement mov);
    void toggleCameraAnimationActivation();

};

#endif /* defined(__LAIG_Proj1__LG_Tzaar__) */
