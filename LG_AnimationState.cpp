//
//  LG_AnimationState.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 17/11/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_AnimationState.h"



LG_AnimationState::LG_AnimationState(LG_Node_Map *map,TiXmlElement *elem):animation(LG_Animation::animationForElement(map, elem)),started(false){
    
    rotate(0, 1, 0, 0);
    translate(0,0,0);
    translate_afterRotation(0, 0, 0);
    animation->configureInitialParameters(this);
    

}



LG_AnimationState::LG_AnimationState(LG_Node_Map *map,LG_Animation *anim):animation(anim),started(false){

    
    rotate(0, 1, 0, 0);
    translate(0,0,0);
    translate_afterRotation(0, 0, 0);
    animation->configureInitialParameters(this);

    
    
}

void LG_AnimationState::apply(){

    glMultMatrixd((GLdouble *)post_rotation_translation_matrix);
    glMultMatrixd((GLdouble *)rotation_matrix);
    glMultMatrixd((GLdouble *)translation_matrix);

    
    
}


void LG_AnimationState::update(unsigned long timeNow){

    if (!started) {
        started=true;
        startTime=timeNow;
        return;
    }
    else if (timeNow>startTime+animation->span) timeNow=startTime+animation->span;

    animation->update(timeNow, this);

}


void LG_AnimationState::rotate(double angle,double x,double y,double z){

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotated(angle, x, y, z);
    glGetDoublev(GL_MODELVIEW_MATRIX, (GLdouble *)rotation_matrix);

    
}
void LG_AnimationState::translate(double x,double y,double z){
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslated(x, y, z);
    glGetDoublev(GL_MODELVIEW_MATRIX, (GLdouble *)translation_matrix);

}

void LG_AnimationState::translate_afterRotation(double x,double y,double z){
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslated(x, y, z);
    glGetDoublev(GL_MODELVIEW_MATRIX, (GLdouble *)post_rotation_translation_matrix);
    
}



unsigned long LG_AnimationState::timePassed(unsigned long timeNow){

    return timeNow-startTime;
}


bool LG_AnimationState::finished(unsigned long timenow){

    
    return timenow-startTime>=animation->span;
    
}