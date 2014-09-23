//
//  LG_Node.h
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 23/09/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#ifndef __LAIG_Proj1__LG_Node__
#define __LAIG_Proj1__LG_Node__

#include <stdio.h>
#include <vector>
#include <string>
#include <map>
#include "LG_Node.h"
#include "LG_Properties.h"



using  std::vector;
using std::string;
using std::map;

class LG_Node;//forward declaration for typedef


typedef map<string *, LG_Node *> LG_Node_Map;
typedef vector<string *> LG_ID_Vector;

class LG_Node{
    
    
private:
    
    
    
    /**
     
     A vector with all the nodes childs names
     
     */
    
    LG_ID_Vector childsIDs;
    
    
    /**
     
     The properties for this object
     
     */
    LG_Properties *properties;
    
    
    /**
     
     
     The identifier for this node
     
     */
    
    string *identifier;
    
    
    /**
     
     The map that has all the nodes;
     
     
     */
    
    
    LG_Node_Map *map;
    
    
    
public:
    
    
    /**
     
     Simple constructor
     
     */
    LG_Node(LG_Node_Map* theMap);
    
    
    
    /**
     
     Constructor with initial properties set
     
     */
    
    
    LG_Node(LG_Properties *properties);
    
    
    /**
     
     
     A method to draw the node. Each Subclass should override this method.
     
     */
    
    virtual void draw()=0;
    
    
    /**
     
     A method for getting a particular child from this node. First child is child number zero.
     
     */
    LG_Node * child(int childNr);
    
    
    /**
     
     A method for adding a child
     
     
     */
    
    
    void addChild(string *childID);
    
    
    
    
    
    
    
    
    
};



#endif /* defined(__LAIG_Proj1__LG_Node__) */


