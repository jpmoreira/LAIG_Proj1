//
//  LG_Tzaar.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 29/12/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_Tzaar.h"
#include <iostream>
#include "LG_State_Menu.h"
#include "LG_State_Waiting_Piece_Selection.h"
#include <regex>
#include <sstream>
#include "LG_Socket.h"

#include "LG_Board_Place.h"

#define BUFSIZE 10
GLuint selectBuf[BUFSIZE];

#define PL_NO "no."
#define PL_FUNC_goodMoveForPhase "goodMoveForPhase"
#define PL_FUNC_chooseMove2 "chooseMove2"
#define PL_FUNC_gameOver "gameOver"


LG_Tzaar * LG_Tzaar::currentTzaar = NULL;


#pragma mark - Loading

void LG_Tzaar::loadScene(){


	if (scene_anf)delete scene_anf;
	TiXmlDocument *docForScene = new TiXmlDocument(docNameForScene.c_str());

	if (!docForScene->LoadFile()){

		std::cout << "Unable to load scene in file named " << docNameForScene << "." << std::endl;
		std::cout << "Execution will be aborted" << std::endl;
		exit(EXIT_FAILURE);

	}



	scene_anf = LG_ANF::anfForXML(docForScene);
	scene_anf->config();


}
void LG_Tzaar::loadMenu(){

	TiXmlDocument *docForMenu = new TiXmlDocument(docNameForMenu.c_str());

	if (!docForMenu->LoadFile()){

		std::cout << "Unable to load menu in file named " << docNameForMenu << "." << std::endl;
		std::cout << "Execution will be aborted" << std::endl;
		exit(EXIT_FAILURE);

	}
	menu_anf = LG_ANF::anfForXML(docForMenu);

}
void LG_Tzaar::loadShortMenu(){


	TiXmlDocument *docForShortMenu = new TiXmlDocument(docNameForShortMenu.c_str());

	if (!docForShortMenu->LoadFile()){

		std::cout << "Unable to load short menu in file named " << docNameForShortMenu << "." << std::endl;
		std::cout << "Execution will be aborted" << std::endl;
		exit(EXIT_FAILURE);

	}

	short_menu_anf = LG_ANF::anfForXML(docForShortMenu);

}

#pragma mark - Singleton

LG_Tzaar::LG_Tzaar():CGFscene(),CGFinterface(),scene_anf(NULL),menu_anf(NULL),short_menu_anf(NULL),nrVictoriesPlayerA(0),nrVictoriesPlayerB(0){

}

LG_Tzaar * LG_Tzaar::getCurrentTzaar(){

	if (currentTzaar == NULL) currentTzaar = new LG_Tzaar();
	return currentTzaar;

}

#pragma mark - Documents name setting

void LG_Tzaar::setDocNameForScene(string name){

	docNameForScene = name;
}

void LG_Tzaar::setDocNameForMenu(string name){

	docNameForMenu = name;
}

void LG_Tzaar::setDocNameForShortMenu(string name){

	docNameForShortMenu = name;
}


#pragma mark - CGFInterface

void LG_Tzaar::processKeyboard(unsigned char key, int x, int y){

	printf("Processing Keyboard\n");

}
void LG_Tzaar::processMouse(int button, int state, int x, int y){


	this->state->processMouse(button, state, x, y);

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		this->performPicking(x, y);


}
void LG_Tzaar::defaultMouseProcessing(int button, int state, int x, int y){

	CGFinterface::processMouse(button, state, x, y);
}

#pragma mark - CGFscene


void LG_Tzaar::init() {


	initReflection();

	this->state = new LG_State_Menu(this);//initial state is menu;
	this->mode = player_vs_player;
	this->difficulty = easy;
	this->phase = phase1;
	this->playingColor = White;


	loadScene();
	loadMenu();
	loadShortMenu();

	glEnable(GL_NORMALIZE);

	setUpdatePeriod(20);

}


void LG_Tzaar::display(){


	scene_anf->selective_config();

	// ---- BEGIN Background, camera and axis setup

	// Clear image and depth buffer everytime we update the scene
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Initialize Model-View matrix as identity (no transformation
	glMatrixMode(GL_MODELVIEW);


	bool selectMode = false;
	GLint mode;
	glGetIntegerv(GL_RENDER_MODE, &mode);

	if (mode == GL_SELECT){

		selectMode = true;

	}
	glLoadIdentity();

	this->drawMenu(selectMode);

	CGFscene::activeCamera->applyView();

	axis.draw();

	scene_anf->draw(selectMode);

	glutSwapBuffers();

	//cout << boardString() << endl;

#pragma region TEST_ZONE
	//if (!validateMoveFOR_TESTS(2, 3, 3, 3))
	//{
	//	std::cout << "Valid Movement: [2,3] to [3,3]" << endl;
	//}


	//vector<LG_Board_Place *> move = chooseMove();

	//std::cout << "moving: " << move[0]->toString() << " to " << move[1]->toString() << endl
	//	<< "positions: x1= " << move[0]->getX() << " z1= " << move[0]->getY() << endl
	//	<< "positions: x2= " << move[1]->getX() << " z2= " << move[1]->getY() << endl;
#pragma endregion



}

void LG_Tzaar::update(unsigned long millis){
    
    this->state->update(millis);

}


#pragma mark - Picking

void LG_Tzaar::performPicking(int x, int y)
{
	// Sets the buffer to be used for selection and activate selection mode
	glSelectBuffer(BUFSIZE, selectBuf);
	glRenderMode(GL_SELECT);

	// Initialize the picking name stack
	glInitNames();

	// The process of picking manipulates the projection matrix
	// so we will be activating, saving and manipulating it
	glMatrixMode(GL_PROJECTION);

	//store current projmatrix to restore easily in the end with a pop
	glPushMatrix();

	//get the actual projection matrix values on an array of our own to multiply with pick matrix later
	GLfloat projmat[16];
	glGetFloatv(GL_PROJECTION_MATRIX, projmat);

	// reset projection matrix
	glLoadIdentity();

	// get current viewport and use it as reference for
	// setting a small picking window of 5x5 pixels around mouse coordinates for picking
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	// this is multiplied in the projection matrix
	gluPickMatrix((GLdouble)x, (GLdouble)(CGFapplication::height - y), 5.0, 5.0, viewport);

	// multiply the projection matrix stored in our array to ensure same conditions as in normal render
	glMultMatrixf(projmat);

	// force scene drawing under this mode
	// only the names of objects that fall in the 5x5 window will actually be stored in the buffer
	scene->display();

	// restore original projection matrix
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glFlush();

	// revert to render mode, get the picking results and process them
	GLint hits;
	hits = glRenderMode(GL_RENDER);
	LG_Node *node = processHits(hits, selectBuf);
	this->state->nodeSelected(node);
}

LG_Node * LG_Tzaar::processHits(GLint hits, GLuint buffer[])
{
	GLuint *ptr = buffer;
	GLuint mindepth = 0xFFFFFFFF;
	GLuint *selected = NULL;
	GLuint nselected;

	// iterate over the list of hits, and choosing the one closer to the viewer (lower depth)
	for (int i = 0; i < hits; i++) {
		int numNames = *ptr; ptr++;
		GLuint z1 = *ptr; ptr++;
		ptr++;
		if (z1 < mindepth && numNames>0) {
			mindepth = z1;
			selected = ptr;
			nselected = numNames;
		}
		for (int j = 0; j < numNames; j++)
			ptr++;
	}

	// if there were hits, the one selected is in "selected", and it consist of nselected "names" (integer ID's)
	if (selected != NULL)
	{

		GLuint idSelected = selected[0];


		LG_Node * node = this->scene_anf->nodeWithPickingID(idSelected);
		if (!node) node = this->menu_anf->nodeWithPickingID(idSelected);
		if (!node) node = this->short_menu_anf->nodeWithPickingID(idSelected);

		return node;

		/*
		// this should be replaced by code handling the picked object's ID's (stored in "selected"),
		// possibly invoking a method on the scene class and passing "selected" and "nselected"
		printf("Picked ID's: ");
		for (int i=0; i<nselected; i++)
		printf("%d ",selected[i]);
		printf("\n");

		*/
	}
	else
		printf("Nothing selected while picking \n");

	return NULL;
}




#pragma mark - State Design Pattern


void LG_Tzaar::changeState(LG_Game_State *newState){

	if (this->state) delete this->state;
	this->state = newState;


}


void LG_Tzaar::draw(bool selectMode){
	this->state->draw(selectMode);
}
void LG_Tzaar::drawMenu(bool selectMode){
	this->state->drawMenu(selectMode);
}
void LG_Tzaar::exitButtonClicked(){
	this->state->exitButtonClicked();
}

void LG_Tzaar::nodeSelected(LG_Node* node){
	this->state->nodeSelected(node);
}
void LG_Tzaar::movementValidation(bool valid){
	this->state->movementValidation(valid);
}
void LG_Tzaar::animationFinished(LG_Animation *anim){
	this->state->animationFinished(anim);
}
void LG_Tzaar::gameEnded(int winner){
    if (winner==1) nrVictoriesPlayerA++;
    else nrVictoriesPlayerB++;
	this->state->gameFinished(winner);
}



#pragma mark - Button Actions


void LG_Tzaar::playClicked(int difficulty){
	this->state->startPlaying(difficulty);
}

void LG_Tzaar::changeCameraClicked(){


}


void LG_Tzaar::setModeClicked(int mode){

	if (mode == 1)this->mode = player_vs_player;
	else if (mode == 2)this->mode = player_vs_computer;
	else this->mode = computer_vs_computer;

}

#pragma mark - Reflection


void LG_Tzaar::initReflection(){



	invocationMapNoArgs["changeCameraClicked"] = &LG_Tzaar::changeCameraClicked;
	invocationMapNoArgs["exitButtonClicked"] = &LG_Tzaar::exitButtonClicked;

	invocationMapWithArgs["playClicked"] = &LG_Tzaar::playClicked;
	invocationMapWithArgs["setModeClicked"] = &LG_Tzaar::setModeClicked;



}
void LG_Tzaar::invoke(string methodName, int param){


	auto method = invocationMapNoArgs[methodName];
	if (method != NULL) {

		(this->*method)();
	}
	auto methodWithArgs = invocationMapWithArgs[methodName];

	if (methodWithArgs != NULL) {
		(this->*methodWithArgs)(param);
	}


}


#pragma mark - Prolog Communication Routines


bool LG_Tzaar::validateMove(){

	ostringstream oss;
	string sep = ",";

	string qst, ans;
	oss << PL_FUNC_goodMoveForPhase << "(" << boardString() << sep << origin->getX() - 1 << sep << origin->getY() - 1
		<< sep << destination->getX() - 1 << sep << destination->getY() - 1 << sep << this->phase + 1 << ").\n";

	qst = oss.str();
	sock->write(qst);
	ans = sock->read();

	return str_eq(ans, PL_NO);
}

bool LG_Tzaar::validateMoveFOR_TESTS(int x1, int z1, int x2, int z2){

	ostringstream oss;
	string sep = ",";

	string qst, ans;
	oss << PL_FUNC_goodMoveForPhase << "(" << boardString() << sep << x1 << sep << z1
		<< sep << x2 << sep << z2 << sep << this->phase + 1 << ").\n";

	qst = oss.str();
	sock->write(qst);
	ans = sock->read();

	std::cout << ans << endl;

	return str_eq(ans, PL_NO);

}

vector<LG_Board_Place *> LG_Tzaar::chooseMove(){
	vector<LG_Board_Place *> move;

	ostringstream oss;
	string sep(","), prefix("LG_Board_Place_");;

	string qst, ans;
	//TODO replace hardcoded value 3 to game mode when playing against a.i.
	oss << PL_FUNC_chooseMove2 << "('" << 3 << "'" + sep << this->boardString() << sep << "NextBoard, SelectedMove, Result).";
	qst = oss.str() + "\n";
	sock->write(qst);
	ans = sock->read();

	oss.str(std::string());
	oss.clear();

	int x1, x2, z1, z2;
	sscanf(ans.c_str(), "[%d,%d,%d,%d]", &x1, &z1, &x2, &z2);
	x1++; x2++; z1++; z2++;

	oss << prefix << x1 << "_" << z1;
	auto it = this->scene_anf->graph->map->find(oss.str());

	if (it != this->scene_anf->graph->map->end())
		move.push_back(dynamic_cast<LG_Board_Place *>(it->second));

	oss.str(std::string());
	oss.clear();
	oss << prefix << x2 << "_" << z2;

	it = this->scene_anf->graph->map->find(oss.str());

	if (it != this->scene_anf->graph->map->end())
		move.push_back(dynamic_cast<LG_Board_Place *>(it->second));

	return move;


}


#pragma mark - Helper Methods


string LG_Tzaar::boardString(){

	string board("["), //start board declaration
		prefix("LG_Board_Place_");
	//5 5 does not exist

	LG_Board_Place *place;


	//todo erase aux board and aux_oss
	//string aux_board;
	//ostringstream aux_oss;

	for (int z = 1; z < 5; z++){ //taking care of the top 4 rows, z stands for row, x for diagonal
		board += "[";	//start a line
		for (int x = 1; x < z + 5; x++){
			ostringstream current_id;
			
			//aux_oss << "[ " << x << ", " << z << " ]";
			current_id << prefix << x << "_" << z;

			auto it = this->scene_anf->graph->map->find(current_id.str());

			if (it != this->scene_anf->graph->map->end()){
				place = dynamic_cast<LG_Board_Place *>(it->second);
				board += place->toString();
				if (x != z + 4)
					board += ","; //comma for the next position in line until there's none
			}

		}
		//aux_oss << endl;
		board += "],"; //close line and give a comma for the next one
	}

	//special case, middle row
	board += "[";
	for (int x = 1, z = 5; x < 10; x++) //z for row, x for diagonal
	{
		if (x == 5)		//it's a hole
			continue;

		ostringstream current_id;
		current_id << prefix << x << "_" << z;
		auto it = this->scene_anf->graph->map->find(current_id.str());

		if (it != this->scene_anf->graph->map->end()){
			place = dynamic_cast<LG_Board_Place *>(it->second);
			board += place->toString();
			if (x != 9)
				board += ","; //comma for the next position in line until there's none
		}

		//aux_oss << "[ " << x << ", " << z << " ]";

	}
	board += "],"; //close line and give a comma for the next one
	//aux_oss << endl;

	int aux = 9;
	/*Z reachs a max value of 9rows, and x always ends at 9, varying the starting index*/
	for (int z = 6; z < 10; z++){ //taking care of the bottom 4 rows, z stands for row, x for diagonal

		board += "[";	//start a line
		for (int x = 1; x < aux; x++){
			ostringstream current_id;
			current_id << prefix << x << "_" << z;
			//aux_oss << "[ " << x << ", " << z << " ]";
			auto it = this->scene_anf->graph->map->find(current_id.str());

			if (it != this->scene_anf->graph->map->end()){
				place = dynamic_cast<LG_Board_Place *>(it->second);
				board += place->toString();
				if (x < aux - 1)
					board += ","; //comma for the next position in line until there's none
			}
		}
		board += "],"; //close line
		aux--;
		//aux_oss << endl;

	}
	ostringstream oss;
	oss << "['@info'," << this->playingColor + 1 << "," << this->phase + 1 << ",['" << this->difficulty + 1 << "']]]";
	board += oss.str(); //last line, close and terminate string
	
	//aux_board = aux_oss.str();
	//cout << aux_board;

	return board;

}

#pragma mark - Camera Animation

void LG_Tzaar::cameraAnimationFinished(){

}
