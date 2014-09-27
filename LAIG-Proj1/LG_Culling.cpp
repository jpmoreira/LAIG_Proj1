//
//  LG_Culling.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 26/09/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_Culling.h"

#include "LG_Parsable_Node.h"




LG_Culling::LG_Culling(LG_Node_Map *map,TiXmlNode *node):LG_Parsable_Node(map,_LG_Culling_NodeID),face(LG_Culling_Face_Not_Set),order(LG_Culling_Order_Not_Set){

    

}
LG_Culling::LG_Culling(LG_Node_Map *map,TiXmlNode *node,LG_Culling_Order ord,LG_Culling_Face f):LG_Parsable_Node(map,_LG_Culling_NodeID),face(f),order(ord){
    

}

