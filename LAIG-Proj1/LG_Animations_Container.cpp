//
//  LG_AnimationsContainer.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 29/10/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_Animations_Container.h"
#include "LG_Animation.h"

#define LG_Animations_Container_ID "LG_Animations_Container_ID"


LG_Animation_Container::LG_Animation_Container(TiXmlElement *elem):LG_Parsable_Node(NULL,LG_Animations_Container_ID){


    map=new LG_Node_Map;
    
    evalElemName(LG_Animations_Container_XML_Tag_Name, elem->Value());
    
    
    TiXmlElement *childElement=elem->FirstChildElement();
    
    
    while (childElement) {
        
       
        LG_Animation *anim= LG_Animation::animationForElement(map, childElement);
        
        this->addChild(anim);
    
        childElement=childElement->NextSiblingElement();
    }
    
    
    
    
    
}

LG_Animation_Container::LG_Animation_Container():LG_Parsable_Node(NULL,LG_Animations_Container_ID){
    
    
    map=new LG_Node_Map;
    

    
    
    
}