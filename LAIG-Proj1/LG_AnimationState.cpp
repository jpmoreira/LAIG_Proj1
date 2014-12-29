//
//  LG_AnimationState.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 17/11/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_AnimationState.h"



LG_AnimationState::LG_AnimationState(LG_Node_Map *map,TiXmlElement *elem,LG_Node *owner):animation(LG_Animation::animationForElement(map, elem)),started(false),currentSegment(0),startTime(0),notifiedOwnerOfFinish(false),owner(owner),velocity(0),currentY(0),currentDampingFactor(1){
    
    rotate(0, 1, 0, 0);
    translate(0,0,0);
    translate_afterRotation(0, 0, 0);
    animation->configureInitialParameters(this);
    

}



LG_AnimationState::LG_AnimationState(LG_Node_Map *map,LG_Animation *anim,LG_Node *owner):animation(anim),started(false),currentSegment(0),startTime(0),notifiedOwnerOfFinish(false),owner(owner),velocity(0),currentY(0),currentDampingFactor(1){

    
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
    else if (timeNow>startTime+animation->span){
        timeNow=startTime+animation->span;
        if (owner!=NULL && !notifiedOwnerOfFinish){
            owner->animationFinished(this);
            notifiedOwnerOfFinish=true;
        }
    }

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

	if (!started)
		return false;
    return timenow-startTime>=animation->span;
    
}


bool LG_AnimationState::finished(){


    return notifiedOwnerOfFinish;
}
int LG_AnimationState::getCurrentSegment(){
    
    
    return currentSegment;
}

void LG_AnimationState::incrementCurrentSegment(){
    
    currentSegment++;
    
}