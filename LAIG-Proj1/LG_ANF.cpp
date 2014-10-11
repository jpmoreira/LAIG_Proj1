//
//  LG_Config.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 10/10/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_ANF.h"

#define LG_ANF_XML_TAG_NAME "anf"
#define LG_ANF_GLOBALS_XML_TAG_NAME "globals"




LG_ANF::LG_ANF(TiXmlElement *elem):map(new LG_Node_Map()) {
    
    
    if (!str_eq(elem->Value(), LG_ANF_XML_TAG_NAME)) {
        
        throw new LG_Parse_Exception_Wrong_Element_Name(LG_ANF_XML_TAG_NAME,elem->Value());
        
    }
    
    
    
    TiXmlElement *subElement=elem->FirstChildElement();
    
    
    while (subElement) {
        
 
        if(str_eq(subElement->Value(), LG_ANF_GLOBALS_XML_TAG_NAME)){
            
            handleGlobals(subElement);
        }
        
        else if(str_eq(subElement->Value(), LG_CAMERAS_XML_TAG_NAME)){
            
            cameras=new LG_Cameras_Container(map,subElement);
        }
        
        else if(str_eq(subElement->Value(), LG_LIGHTS_XML_TAG_NAME)){
            
            lights=new LG_Lights_Container(map,subElement);
        }
        
        else if(str_eq(subElement->Value(), LG_Texture_Container_XML_Tag_Name)){
            
            textures=new LG_Texture_Container(map,subElement);

        }
        
        else if(str_eq(subElement->Value(),LG_Apperance_Container_XML_Tag_Name)){
            
            apperances=new LG_Appearance_Container(map,subElement,map);
        }
        
        
        else if(str_eq(subElement->Value(),LG_Graph_XML_Tag_Name)){
            
            graph=new LG_Graph(map,subElement);
        }
        
        
        subElement=subElement->NextSiblingElement();
    }
    
    
    
    verifyDataMembersValues();
    
    
    
    
    
}


#pragma mark - Helper methods


void LG_ANF::handleGlobals(TiXmlElement *elem) {
    
    
    TiXmlElement *child=elem->FirstChildElement();
    
    while (child) {
        
        if(str_eq(LG_Drawing_XML_Tag_Name, child->Value())){
            
            drawingConfig=new LG_Drawing(map,child);
        }
        
        else if(str_eq(LG_CULLING_XML_TAG_NAME, child->Value())){
            
            cullingConfig=new LG_Culling(map,child);
        }
        
        else if(str_eq(LG_LIGHTING_XML_TAG_NAME, child->Value())){
            
            lightingConfig=new LG_Lighting(map,child);
        }
        
        child=child->NextSiblingElement();
    }
    
}


void LG_ANF::verifyDataMembersValues() {

    
    if (!lightingConfig && !cullingConfig && !drawingConfig) {
        throw new LG_Parse_Exception_Missing_Element(LG_ANF_GLOBALS_XML_TAG_NAME);
    }
    
    if(!lightingConfig){
    
        throw new LG_Parse_Exception_Missing_Element(LG_LIGHTING_XML_TAG_NAME);
    }

    if(!cullingConfig){
        
        throw new LG_Parse_Exception_Missing_Element(LG_CULLING_XML_TAG_NAME);
    }
    
    if(!drawingConfig){
        
        throw new LG_Parse_Exception_Missing_Element(LG_Drawing_XML_Tag_Name);
    }
    
    if(!cameras){
        
        throw new LG_Parse_Exception_Missing_Element(LG_CAMERAS_XML_TAG_NAME);
    }
    
    if (!lights) {
        throw new LG_Parse_Exception_Missing_Element(LG_LIGHTS_XML_TAG_NAME);
    }
    
    
    if (!textures) {
        throw new LG_Parse_Exception_Missing_Element(LG_TEXTURE_XML_TAG_NAME);
    }
    
    
    if (!apperances) {
        throw new LG_Parse_Exception_Missing_Element(LG_Appearance_XML_Tag_Name);
    }
    
    
    if (!graph) {
        throw new LG_Parse_Exception_Missing_Element(LG_Graph_XML_Tag_Name);
    }
}