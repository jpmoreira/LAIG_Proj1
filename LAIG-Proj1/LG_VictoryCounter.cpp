//
//  LG_VictoryCounter.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 03/01/15.
//  Copyright (c) 2015 José Pedro Moreira. All rights reserved.
//

#include "LG_VictoryCounter.h"
#include "LG_Tzaar.h"

LG_VictoryCounter::LG_VictoryCounter(LG_Node_Map *map,TiXmlElement *elem):LG_Counter(map,LG_VictoryCounter_ID){

    double pt1[3]={-nrWidth/2.0,-nrHeight/2., 0};
    double pt2[3]={nrWidth/2.0, nrHeight/2.0, 0};
    
    this->addChild(new LG_Rectangle(map, pt1, pt2));
    
    appForFirstPlayerVictories1=nrApps[0];
    appForFirstPlayerVictories2=nrApps[0];
    
    appForSecondPlayerVictories1=nrApps[0];
    appForSecondPlayerVictories2=nrApps[0];
    
}


void LG_VictoryCounter::draw(bool selectMode){


}

void LG_VictoryCounter::reset(){

    
    
    appForFirstPlayerVictories1=nrApps[0];
    appForFirstPlayerVictories2=nrApps[0];
    
    appForSecondPlayerVictories1=nrApps[0];
    appForSecondPlayerVictories2=nrApps[0];

}

void LG_VictoryCounter::updateNrVictories(int nrVictoriesA,int nrVictoriesB){

    appForFirstPlayerVictories1=nrApps[nrVictoriesA%10];
    appForFirstPlayerVictories2=nrApps[nrVictoriesA/10];
    
    appForSecondPlayerVictories1=nrApps[nrVictoriesB%10];
    appForSecondPlayerVictories2=nrApps[nrVictoriesB/10];

}