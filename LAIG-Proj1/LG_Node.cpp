
//
//  LG_Node.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 23/09/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_Node.h"

#include "LG_AnimationState.h"
#include "LG_Appearance.h"
#include "LG_Animation.h"
#include "LG_Transform.h"



using std::vector;



#pragma mark - Constructors
LG_Node::LG_Node(LG_Node_Map *map,string theIdentifier,LG_Transform *t):childsIDs(LG_ID_Vector()),identifier(theIdentifier),map(map),animations(vector<LG_AnimationState *>()),currentAnimation(0),appearance(NULL),transform(t){
    
    if (map==NULL)return;
    LG_Node_Map_Pair pair(identifier,this);
    map->insert(pair);//add itself to the map automatically
    
    
    
}


#pragma mark - Drawing


void LG_Node::drawChilds(){

    for (unsigned int i=0; i<childsIDs.size(); i++) {
        
        child(i)->draw();
        
    }

}

void LG_Node::draw(){
    
    
    if (isDisplayList){
        
        glCallList(displayListID);
        
    }
    
    
    else{
        
        glPushMatrix();
        
        
        
        if(animations.size()>0){
            
            for (int i=currentAnimation; i>=0; i--) animations.at(i)->apply();
            
        }
        
        
        if(transform) transform->draw();
        
        
        if (appearance) appearance->apply();
        
        drawChilds();
        
        if (appearance) appearance->unapply();
        
        glPopMatrix();
        
    }



    
}


#pragma mark - Managing Childs

LG_Node * LG_Node::child(int childNr){

    
    if (!map)return NULL;
    
    
    if (childNr>=childsIDs.size())return NULL;
    string childID=childsIDs[childNr];
    
    auto it=map->find(childID);
    
    if (it==map->end()) return NULL;
    return it->second;


}




void LG_Node::addChild(LG_Node *nodeToAdd){
    
    
    
    childsIDs.push_back(nodeToAdd->identifier);


}

void LG_Node::addChild(string & identifOfChildToAdd){
    
    childsIDs.push_back(identifOfChildToAdd);
    
}


string LG_Node::getIdentifier(){
	return this->identifier;
}


int LG_Node::getNrChildren()
{
	return (int) this->childsIDs.size();
}


#pragma mark - Configuring


void LG_Node::config(){


}

void LG_Node::update(unsigned long time){
    
    
    if (str_eq(this->identifier, "vehicle"))
    {
        printf("Animacao corrente = %d\n", currentAnimation);
    }
    
    if (animations.size()>0) {
        LG_AnimationState *currentAnimationState=animations.at(currentAnimation);
        
        if (str_eq(this->identifier, "vehicle"))
        {
            printf("terminou = %d\n", currentAnimationState->finished(time));
            //printf("start time = %d")
        }
        
        if (currentAnimationState->finished(time) && currentAnimation+1<animations.size()) {//change to next animation if this one has finished (and if there is one)
            currentAnimation++;
        }
        
        animations.at(currentAnimation)->update(time);
        
        
    }
    
    for (int i=0; i<childsIDs.size(); i++) {
        
        child(i)->update(time);
    }

}

#pragma mark - Animations

void LG_Node::animationFinished(LG_AnimationState *state){

    
    printf("FINISHED");

}


bool LG_Node::isAnimating(){

    if (currentAnimation>=0 && currentAnimation<animations.size()) {
        LG_AnimationState *state=animations[currentAnimation];
        if (!state->finished())return true;
    }
    
    for (int i=0; i<childsIDs.size(); i++) {
        LG_Node *theChild=child(i);
        if (theChild->isAnimating())return true;
    }
    
    return false;
    
    

}