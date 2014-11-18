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

#include "LG_AnimationState.h"

#define LG_Graph_Node_XML_Tag_Name "node"

class LG_Appearance;
class LG_Primitive;
class LG_Transform;


class LG_Graph_Node:public LG_Parsable_Node{
    
    
private:
    
    LG_Transform *transform;
    
    LG_Appearance *appearance;
    vector<LG_AnimationState *>animations;
    int currentAnimation;
    GLint displayListID;
    
    bool isDisplayList;
    
    
    static string identifierForGraphNode(TiXmlElement *elem);
    
    void handleDescendants(LG_Node_Map *node_map,TiXmlElement *descendantsElement);
    
    
    vector<LG_Primitive *> handlePrimitives(LG_Node_Map *map,TiXmlElement *primitivesElement);
    
    
    void handleAppearance(LG_Node_Map *map,TiXmlElement *appearanceElement);
    
    void handleAnimation(LG_Node_Map *map,TiXmlElement * animationElement);
    
    
    
    
    
    
public:
    LG_Graph_Node(LG_Node_Map *map,LG_Node_Map *appearances_map,LG_Node_Map *animations_map,TiXmlElement *elem);
    LG_Graph_Node(LG_Node_Map *map,LG_Node_Map *appearances_map,LG_Node_Map *anim_map,LG_Transform *transform,vector<LG_Primitive *> &primitives,string identifier);
    
    
    void draw();
    
    void update(unsigned long);
    
    
    virtual void config();
    
};

#endif /* defined(__LAIG_Proj1__LG_Graph_Node__) */
