//
//  LG_Texture_Container.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 09/10/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_Texture_Container.h"

#define LG_Texture_Containter_ID "_LG_Texture_Container"



#pragma mark - Constructor

LG_Texture_Container::LG_Texture_Container(TiXmlElement *elem):LG_Parsable_Node(NULL,LG_Texture_Containter_ID) {
    
    map=new LG_Node_Map();
    
    if (!str_eq(elem->Value(), LG_Texture_Container_XML_Tag_Name)) {
        throw new LG_Parse_Exception_Wrong_Element_Name(LG_Texture_Container_XML_Tag_Name,elem->Value());
    }
    
    
    TiXmlElement *subElem=elem->FirstChildElement();
    
    while (subElem) {
        
        
        
        if (str_eq(subElem->Value(), LG_TEXTURE_XML_TAG_NAME)) {
            
            LG_Texture* text=new LG_Texture(map,subElem);
            addChild(text);
        }
        
        
        
        subElem=subElem->NextSiblingElement();
    }
    
    
    
}


LG_Texture_Container::~LG_Texture_Container(){

    for (auto pair: *map) {
        
        delete pair.second;
    }


}


