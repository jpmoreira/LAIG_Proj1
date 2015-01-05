//
//  LG_VictoryCounter.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 03/01/15.
//  Copyright (c) 2015 José Pedro Moreira. All rights reserved.
//

#include "LG_VictoryCounter.h"
#include "LG_Tzaar.h"
#include "LG_Rectangle.h"

LG_VictoryCounter::LG_VictoryCounter(LG_Node_Map *map,TiXmlElement *elem):LG_Counter(map,LG_VictoryCounter_ID){

    double pt1[3]={-4.0*nrWidth,-nrHeight/2.0, 0};
    double pt2[3]={4.0*nrWidth, nrHeight/2.0, 0};
    
    double pt3[3]={-nrWidth,-nrHeight/2.0,0};
    double pt4[3]={0,nrHeight/2.0,0};
    
    double pt5[3]={3.0*nrWidth,-nrHeight/2.0,0};
    double pt6[3]={4.0*nrWidth,nrHeight/2.0,0};
    
    
    this->addChild(new LG_Rectangle(map, pt1, pt2));
    this->addChild(new LG_Rectangle(map,pt3,pt4));
    this->addChild(new LG_Rectangle(map,pt5,pt6));
    
    appForFirstPlayerVictories1=nrApps[0];

    
    appForSecondPlayerVictories1=nrApps[0];
    appForFrame=nrApps[11];
        
}


void LG_VictoryCounter::draw(bool selectMode){
    
    
    appForFrame->apply();
    this->child(0)->draw();
    appForFrame->unapply();
    
    appForFirstPlayerVictories1->apply();
    this->child(1)->draw();
    appForFirstPlayerVictories1->unapply();
    
    appForSecondPlayerVictories1->apply();
    this->child(2)->draw();
    appForSecondPlayerVictories1->unapply();


}

void LG_VictoryCounter::reset(){

    
    
    appForFirstPlayerVictories1=nrApps[0];
    
    
    appForSecondPlayerVictories1=nrApps[0];


}

void LG_VictoryCounter::updateNrVictories(int nrVictoriesA,int nrVictoriesB){

    appForFirstPlayerVictories1=nrApps[nrVictoriesA%10];
    appForSecondPlayerVictories1=nrApps[nrVictoriesB%10];

}


void LG_VictoryCounter::calculateTextureCoordinates (){


}