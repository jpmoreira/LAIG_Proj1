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
    
    
    static unsigned int nextFreePickingID;
    
    
    unsigned int pickingID;
    
    
    
    
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
    
    A bool that states whether the node is selected
     
    */
    
    bool selected;
    
    
    int currentAnimation;
    
    
    
public:

    
    vector<LG_AnimationState *>animations;
	/**

	The map that has all the nodes;


	*/


	LG_Node_Map *map;
    
    /**
     
     
     The identifier for this node
     
     */
    
    string identifier;
    
    
    bool selectable;
    
    /**
     
     Simple constructor. It automatically adds the node to the map
     
     */
    LG_Node(LG_Node_Map* theMap,string theIdentifier,LG_Transform *transform=NULL);
    
    
    
    /**
     
     
     A method to draw the node. Each Subclass should override this method.
     
     */
    
    virtual void draw(bool selectMode=false);
    
    
    /*
     
     
     A method that draws all childs of the node
     
     */
    virtual void drawChilds(bool selectMode=false);
    
    
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
	
	A method that returns how many children this element has
	
	*/

	int getNrChildren();
    
    
    /**
     
    A method that sets the selected state of the node
     
    */
    virtual void setSelected(bool selected);
    
    
    void toggleSelected();
    
    
	string getIdentifier();
    
    virtual void config();
    
    virtual void animationFinished(LG_AnimationState *state);
    

    
    /**
    
     A method that says wether this node is animating or not.
     If the parameter subtree is set to false only the node itself is taken into account. Else, the subtree is taken into account.
     
    */
    bool isAnimating(bool subtree=true);
    
    /**
     
     
     A method that says wether this node is selected or not.
     If subtree is set to true, then a node is considered selected if it is selected or a node in it's subtree is selected. If subtree is set to false a node is considered selected only if it is itself selected.
     
     */
    bool isSelected(bool subtree=true);
    
    
    
    virtual LG_Node * nodeWithPickingID(unsigned int selectID);
    
    
    
    
};



#endif /* defined(__LAIG_Proj1__LG_Node__) */


