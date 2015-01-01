//
//  LG_Button.h
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 30/12/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#ifndef __LAIG_Proj1__LG_Button__
#define __LAIG_Proj1__LG_Button__

#include <stdio.h>
#include "LG_Graph_Node.h"

#define LG_Button_XML_Tag_Name "button"


class LG_Button: public LG_Graph_Node {
    
    
    string action;
    int param;
    
public:
    LG_Button(LG_Node_Map *map,LG_Node_Map *appearances_map,LG_Node_Map *animations_map,TiXmlElement *elem);
    
    void setSelected(bool selected);
};

#endif /* defined(__LAIG_Proj1__LG_Button__) */
