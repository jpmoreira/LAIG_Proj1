
//
//  LG_Node.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 23/09/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_Node.h"

using std::vector;



#pragma mark - Constructors
LG_Node::LG_Node(LG_Node_Map *map,string theIdentifier):childsIDs(LG_ID_Vector()),identifier(theIdentifier),map(map){
    
    if (map==NULL)return;
    LG_Node_Map_Pair pair(identifier,this);
    map->insert(pair);//add itself to the map automatically
    
    
    
}


#pragma mark - Drawing

void LG_Node::draw(){

    
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