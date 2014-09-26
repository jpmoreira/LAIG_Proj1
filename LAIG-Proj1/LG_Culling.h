//
//  LG_Culling.h
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 26/09/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#ifndef __LAIG_Proj1__LG_Culling__
#define __LAIG_Proj1__LG_Culling__

#include <stdio.h>


#define _LG_Drawing_NodeID "_LG_Culling"

#include "LG_Parsable_Node.h"


typedef enum {
    
    LG_Drawing_Fill,
    LG_Drawing_Line,
    LG_Drawing_Point,
    LG_Drawing_Not_Set
    
    
}LG_Drawing_Mode;

typedef enum {
    
    LG_Flat,
    LG_Gouraud,
    LG_Shading_Not_Set
    
    
}LG_Shading_Mode;

class LG_Culling : public LG_Parsable_Node{
    
private:
    LG_Drawing_Mode mode=LG_Drawing_Not_Set;
    
    LG_Shading_Mode shading=LG_Shading_Not_Set;
    
    LG_LightArray background=LG_LightList_InitialValue;
    
    
public:
    
    LG_Culling(LG_Node_Map *map,TiXmlNode *node);
    
    
    
    
    
};
#endif /* defined(__LAIG_Proj1__LG_Culling__) */
