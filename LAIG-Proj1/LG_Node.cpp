
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
LG_Node::LG_Node(LG_Node_Map *map):childsIDs(LG_ID_Vector()),properties(new LG_Properties()){
    
    
    
    
}


LG_Node::LG_Node(LG_Properties *propertiesToDuplicate):childsIDs(LG_ID_Vector()),properties(propertiesToDuplicate->clone()){


}


#pragma mark - Managing Childs

LG_Node * LG_Node::child(int childNr){

    
    
    string* childID=childsIDs[childNr];
    
      return map->find(childID)->second;


}




void LG_Node::addChild(string *childID){
    
    
    
    childsIDs.push_back(childID);


}




