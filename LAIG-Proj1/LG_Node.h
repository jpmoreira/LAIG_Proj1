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

#include <GL/glu.h>

class LG_Transform;
class LG_Appearance;




class LG_AnimationState;

class LG_Node{
    
    friend class LG_Graph;
    friend class LG_ANF;
    friend class LG_Board_Place;
    
protected:
    
    
    
    GLint displayListID;
    
    bool isDisplayList;
    
    
    LG_Transform *transform;
    
    
    
    LG_Appearance *appearance;
    
    /**
     
     A vector with all the nodes childs names
     
     */
    
    LG_ID_Vector childsIDs;
    
    
    /**
     
     The properties for this object
     
     */
    //LG_Properties *properties;
    
    

    
    
    /**
     
     The map that has all the nodes;
     
     
     */
    
    
    LG_Node_Map *map;
    
    
    vector<LG_AnimationState *>animations;
    int currentAnimation;
    
    
    
public:

    
    /**
     
     
     The identifier for this node
     
     */
    
    string identifier;
    
    
    /**
     
     Simple constructor. It automatically adds the node to the map
     
     */
    LG_Node(LG_Node_Map* theMap,string theIdentifier,LG_Transform *transform=NULL);
    
    
    
    /**
     
     
     A method to draw the node. Each Subclass should override this method.
     
     */
    
    virtual void draw();
    
    
    /*
     
     
     A method that draws all childs of the node
     
     */
    virtual void drawChilds();
    
    
    /**
     
     A method to update the graph
     
     */
    
    
    virtual void update(unsigned long);
    
    
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
    
    virtual void config();
    
    
    virtual void animationFinished(LG_AnimationState *state);
    
    bool isAnimating();
    
    
    
};



#endif /* defined(__LAIG_Proj1__LG_Node__) */


