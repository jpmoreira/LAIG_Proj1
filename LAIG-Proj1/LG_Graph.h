//
//  LG_Graph.h
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 01/10/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#ifndef __LAIG_Proj1__LG_Graph__
#define __LAIG_Proj1__LG_Graph__

#include <stdio.h>

#include "LG_Graph_Node.h"
#define LG_Graph_XML_Tag_Name "graph"

class LG_Graph: public LG_Node{
    
    
    
public:
    
    void draw();
    void config();
    
    void update(unsigned long);
    
    LG_Graph_Node *root;
    
private:
    
    

    LG_Node_Map *appearancesMap;
    LG_Node_Map *animationsMap;
    
    
    
    /**
     
     A method that verifies if the root attribute is set, and if it exists. In case it is not mentioned or it does not exist the appropriate exception is thrown.
     
     
     */
    void handleRootNode(TiXmlElement *graphElement);
    
    /**
     
     A method to be called after all nodes are created. All it does it to verify that all the references present in every node are not broken. 
     If any is broken an LG_Parse_Exception_Broken_Reference exception is thrown.
     
     */
    void verifyNodeReferences(TiXmlElement *graphElement);
    
    
    
    
    
    
public:
    LG_Graph(LG_Node_Map *appearancesMap,LG_Node_Map *animationMap,TiXmlElement *elem);
    LG_Graph(LG_Node_Map *appearancesMap,LG_Node_Map *animationsMap,TiXmlElement *elem,LG_Node_Map *map);
    
  
    
    
};

#endif /* defined(__LAIG_Proj1__LG_Graph__) */
