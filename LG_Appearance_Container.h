//
//  LG_Appearance_Container.h
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 09/10/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#ifndef __LAIG_Proj1__LG_Appearance_Container__
#define __LAIG_Proj1__LG_Appearance_Container__

#include <stdio.h>
#include "LG_Appearance.h"

class LG_Appearance_Container:public LG_Parsable_Node {
    
public:
    
    
    LG_Appearance_Container(LG_Node_Map *map,TiXmlElement *elem,LG_Node_Map *texturesMap);
    
    
    
    
};

#endif /* defined(__LAIG_Proj1__LG_Appearance_Container__) */