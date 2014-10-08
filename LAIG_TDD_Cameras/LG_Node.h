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
#include <cstring>



#include "LG_Essentials.h"





class LG_Node{
    
    friend class LG_Graph;
    
protected:
    
    
    
    /**
     
     A vector with all the nodes childs names
     
     */
    
    LG_ID_Vector childsIDs;
    
    
    /**
     
     The properties for this object
     
     */
    //LG_Properties *properties;
    
    
    /**
     
     
     The identifier for this node
     
     */
    
    string identifier;
    
    
    /**
     
     The map that has all the nodes;
     
     
     */
    
    
    LG_Node_Map *map;
    
    
    
public:
    
    
    /**
     
     Simple constructor. It automatically adds the node to the map
     
     */
    LG_Node(LG_Node_Map* theMap,string theIdentifier);
    
    
    
    /**
     
     
     A method to draw the node. Each Subclass should override this method.
     
     */
    
    virtual void draw();
    
    
    /**
     
     A method for getting a particular child from this node. First child is child number zero.
     
     */
    LG_Node * child(int childNr);
    
    
    /**
     
     A method for adding a child
     
     
     */
    
    
    void addChild(LG_Node *childToAdd);
    
    
    /**
     
     
     A method for adding a child identified by an identifier
     
     
     */
    void addChild(string & identifOfChildToAdd);


	/**
	
	A method that retuns how many children this element has
	
	*/

	int getNrChildren();
    
    
    
	string getIdentifier();
    
    
    
};



#endif /* defined(__LAIG_Proj1__LG_Node__) */


