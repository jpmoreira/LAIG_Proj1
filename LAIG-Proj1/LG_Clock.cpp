//
//  LG_Clock.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 03/01/15.
//  Copyright (c) 2015 José Pedro Moreira. All rights reserved.
//

#include "LG_Clock.h"
#include "LG_Rectangle.h"




LG_Clock::LG_Clock(LG_Node_Map *map,TiXmlElement *elem):LG_Counter(map,LG_Clock_ID),seconds(0),minutes(0),started(false){
    
    
    evalElemName(LG_Clock_XML_Tag_Name, elem->Value());
    
    appForHours1=nrApps[0];
    appForHours2=nrApps[0];
    appForSeconds1=nrApps[0];
    appForSeconds2=nrApps[0];
    appSeparator=nrApps[10];
    
    
    double pt1[3]={-nrWidth/2.0,-nrHeight/2., 0};
    double pt2[3]={nrWidth/2.0, nrHeight/2.0, 0};
    
    this->addChild(new LG_Rectangle(map, pt1, pt2));
    
    

}


void LG_Clock::draw(bool selectMode){

    if (selectMode)return;
    
    

    glPushMatrix();
    
    glTranslated(2*nrWidth, 0, 0);
    
    appForSeconds1->apply();
    
    this->child(0)->draw();
    
    appForSeconds1->unapply();
    
    glTranslated(-nrWidth, 0, 0);
    
    appForSeconds2->apply();
    
    this->child(0)->draw();
    
    appForSeconds2->unapply();
    
    glTranslated(-nrWidth, 0, 0);
    
    appSeparator->apply();
    
    this->child(0)->draw();
    
    appSeparator->unapply();
    
    glTranslated(-nrWidth, 0, 0);
    
    appForHours1->apply();
    
    this->child(0)->draw();
    
    appForHours1->unapply();
    
    glTranslated(-nrWidth, 0, 0);
    
    appForHours2->apply();
    
    this->child(0)->draw();
    
    appForHours2->unapply();
    
    
    
    glPopMatrix();
    
    
}

void LG_Clock::update(unsigned long timeNow){
    
    
    if (!started) {
        startTime=timeNow;
        started=true;
    }
    
    int timeSinceStart=(int)((timeNow-startTime)/1000);
    
    
    int nrSeconds=timeSinceStart%60;
    int nrHours=timeSinceStart/60;
    
    int unitsSeconds=nrSeconds%10;
    int tenthSeconds=nrSeconds/10;
    
    int unitsHours=nrHours%10;
    int tenthHours=nrHours/10;
    
    appForSeconds1=LG_Counter::nrApps[unitsSeconds];
    appForSeconds2=LG_Counter::nrApps[tenthSeconds];
    
    appForHours1=LG_Counter::nrApps[unitsHours];
    
    
    appForHours2=LG_Counter::nrApps[tenthHours];
    

}

void LG_Clock::calculateTextureCoordinates(){

    

}

void LG_Clock::reset(){

    started=false;
    
    appForHours1=nrApps[0];
    appForHours2=nrApps[0];
    appForSeconds1=nrApps[0];
    appForSeconds2=nrApps[0];

}