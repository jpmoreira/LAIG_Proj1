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



#pragma mark - Documents name setting

void LG_Tzaar::setDocNameForScene(string name){
    
    docNameForScene=name;
}

void LG_Tzaar::setDocNameForMenu(string name){
    
    docNameForMenu=name;
}

void LG_Tzaar::setDocNameForShortMenu(string name){

    docNameForShortMenu=name;
}


#pragma mark - CGFInterface

void LG_Tzaar::processKeyboard(unsigned char key, int x, int y){
    
    printf("Processing Keyboard\n");
    
}
void LG_Tzaar::processMouse(int button, int state, int x, int y){
    
    
    this->state->processMouse(button,state,x,y);
    
    //CGFinterface::processMouse(button, state, x, y);
    
    
    printf("Processing Mouse\n");
    
    
}

void LG_Tzaar::defaultMouseProcessing(int button, int state, int x, int y){
    
    CGFinterface::processMouse(button, state, x, y);
}

#pragma mark - CGFscene


void LG_Tzaar::init() {
    
    this->state=new LG_State_Menu(this);//initial state is menu;
    
    TiXmlDocument *docForScene = new TiXmlDocument(docNameForScene.c_str());
    
    TiXmlDocument *docForMenu = new TiXmlDocument(docNameForMenu.c_str());
    
    TiXmlDocument *docForShortMenu = new TiXmlDocument(docNameForShortMenu.c_str());
    
    
    
    if(!docForScene->LoadFile()){
        
        std::cout<<"Unable to load scene in file named "<<docNameForScene<<"."<<std::endl;
        std::cout<<"Execution will be aborted"<<std::endl;
        exit(EXIT_FAILURE);
        
    }
    
    if(!docForMenu->LoadFile()){
        
        std::cout<<"Unable to load menu in file named "<<docNameForMenu<<"."<<std::endl;
        std::cout<<"Execution will be aborted"<<std::endl;
        exit(EXIT_FAILURE);
        
    }
    
    if(!docForShortMenu->LoadFile()){
        
        std::cout<<"Unable to load short menu in file named "<<docNameForShortMenu<<"."<<std::endl;
        std::cout<<"Execution will be aborted"<<std::endl;
        exit(EXIT_FAILURE);
        
    }
    
    
    
    scene_anf=LG_ANF::anfForXML(docForScene);
    menu_anf=LG_ANF::anfForXML(docForMenu);
    short_menu_anf=LG_ANF::anfForXML(docForShortMenu);
    
    

    glEnable (GL_NORMALIZE);
    
    setUpdatePeriod(20);
    
    
    scene_anf->config();
    menu_anf->config();
    short_menu_anf->config();
    
    
    
}


void LG_Tzaar::display(){
    
    
    scene_anf->selective_config();
    
    // ---- BEGIN Background, camera and axis setup
    
    // Clear image and depth buffer everytime we update the scene
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    // Initialize Model-View matrix as identity (no transformation
    glMatrixMode(GL_MODELVIEW);
    
    
    glLoadIdentity();

    this->drawMenu();
    
    CGFscene::activeCamera->applyView();

    axis.draw();
    
    scene_anf->draw();
    
    glutSwapBuffers();
    
    
}

void LG_Tzaar::update(unsigned long millis){
    
    scene_anf->getAnimations()->update(millis);
    
    scene_anf->graph->update(millis);
}


#pragma mark - State Design Pattern

void LG_Tzaar::draw(bool selectMode){
    this->state->draw(selectMode);
}
void LG_Tzaar::drawMenu(){
    this->state->drawMenu();
}
void LG_Tzaar::showMenuButtonClicked(){
    this->state->showMenuButtonClicked();
}
void LG_Tzaar::startPlaying(){
    this->state->startPlaying();
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
void LG_Tzaar::gameOverResult(bool gameover){
    this->state->gameOverResult(gameover);
}

