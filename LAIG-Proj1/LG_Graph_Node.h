//
//  LG_Graph_Node.h
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 01/10/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#ifndef __LAIG_Proj1__LG_Graph_Node__
#define __LAIG_Proj1__LG_Graph_Node__

#include "LG_Parsable_Node.h"
#include "LG_Transform.h"
#include "LG_Primitive.h"

class LG_Graph_Node:public LG_Parsable_Node{
    
    
private:
    
    static string identifierForGraphNode(TiXmlElement *elem);
    
    void handleDescendants(LG_Node_Map *map,TiXmlElement *descendantsElement);
    vector<LG_Primitive *> handlePrimitives(LG_Node_Map *map,TiXmlElement *primitivesElement);
    
    LG_Transform *transform;
    
    
public:
    LG_Graph_Node(LG_Node_Map *map,TiXmlElement *elem);
    LG_Graph_Node(LG_Node_Map *map,LG_Transform *transform,vector<LG_Primitive *> &primitives,string identifier);
};

#endif /* defined(__LAIG_Proj1__LG_Graph_Node__) */
