//
//  LG_AnimationsContainer.h
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 29/10/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#ifndef __LAIG_Proj1__LG_AnimationsContainer__
#define __LAIG_Proj1__LG_AnimationsContainer__

#include <stdio.h>
#include "LG_Parsable_Node.h"

#define LG_Animations_Container_XML_Tag_Name "animations"


class LG_Animation_Container: public LG_Parsable_Node {
    
    
    
public:
    
    LG_Animation_Container(TiXmlElement *elem);
    LG_Animation_Container();
    
    
    void update(unsigned long timeNow);
};

#endif /* defined(__LAIG_Proj1__LG_AnimationsContainer__) */
