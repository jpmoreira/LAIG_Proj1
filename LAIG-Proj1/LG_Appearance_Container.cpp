//
//  LG_Appearance_Container.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 09/10/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_Appearance_Container.h"
#define LG_Appearance_Container_ID "_LG_Appearance_Container_ID"



#pragma mark - Constructor

LG_Appearance_Container::LG_Appearance_Container(TiXmlElement *elem,LG_Node_Map *texturesMap):
LG_Parsable_Node(NULL,LG_Appearance_Container_ID){
    
    
    map=new LG_Node_Map();
    
    
    if (!str_eq(elem->Value(), LG_Apperance_Container_XML_Tag_Name)) {
        throw new LG_Parse_Exception_Wrong_Element_Name(LG_Apperance_Container_XML_Tag_Name,elem->Value());
    }
    
    
    TiXmlElement * possibleAppearance=elem->FirstChildElement();
    
    while (possibleAppearance) {
        
        
        if (str_eq(possibleAppearance->Value(), LG_Appearance_XML_Tag_Name)) {
            
            LG_Appearance *app=new LG_Appearance(map,possibleAppearance,texturesMap);
            addChild(app);
        }
        
        
        possibleAppearance=possibleAppearance->NextSiblingElement();
    }


}