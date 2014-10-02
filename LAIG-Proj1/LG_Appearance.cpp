//
//  LG_Appearance.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 01/10/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//


#include "LG_Parsable_Node.h"
#include "LG_Appearance.h"

#define LG_Appearance_Shininess_XML_Att_Name "shininess"
#define LG_Apperance_Component_XML_Tag_Name "component"
#define LG_Apperance_Component_Type_XML_Att_Name "type"
#define LG_Apperance_Component_Value_XML_Att_Name "value"
#define LG_Apperance_Component_Type_Ambient_String "ambient"
#define LG_Apperance_Component_Type_Diffuse_String "diffuse"
#define LG_Apperance_Component_Type_Specular_String "specular"

#pragma mark - Constructors


LG_Appearance::LG_Appearance(LG_Node_Map *map,TiXmlElement *elem):LG_Parsable_Node(map,getIdentifier(elem)){
    
    if (!str_eq(LG_Appearance_XML_Tag_Name, elem->Value())) {
        throw new LG_Parse_Exception_Wrong_Element_Name(LG_Appearance_XML_Tag_Name,elem->Value());
    }
    
    positiveDouble_tryToAttributeVariable(LG_Appearance_Shininess_XML_Att_Name, elem, shininess);
    
    
    TiXmlElement *subElement=elem->FirstChildElement();
    
    while (subElement) {
        
        
        if (str_eq(subElement->Value(), LG_Apperance_Component_XML_Tag_Name)) {
            handleComponent(subElement);
        }
        
        subElement=subElement->NextSiblingElement();
    }

}

LG_Appearance::LG_Appearance(LG_Node_Map *map,LG_LightArray amb,LG_LightArray diff,LG_LightArray spec,double s,string identif):LG_Parsable_Node(map,identif),shininess(s){
    
    copyLightArrays(amb, ambient);
    copyLightArrays(diff, diffuse);
    copyLightArrays(spec, specular);

}


#pragma mark - Helper Methods

string LG_Appearance::getIdentifier(TiXmlElement *elem){

    
    string id;
    
    string_tryToAttributeVariable(LG_Appearance_ID_XML_Att_Name, elem, id);
    
    return id;

}


void LG_Appearance::handleComponent(TiXmlElement *component){

    string type;
    string_tryToAttributeVariable(LG_Apperance_Component_Type_XML_Att_Name, component, type);
    
    
    if (str_eq(type.c_str(), LG_Apperance_Component_Type_Ambient_String)) {
        
        lightArray_tryToAttributeVariable(LG_Apperance_Component_Value_XML_Att_Name, component, ambient);
    }
    
    else if (str_eq(type.c_str(), LG_Apperance_Component_Type_Diffuse_String)) {
        
        lightArray_tryToAttributeVariable(LG_Apperance_Component_Value_XML_Att_Name, component, diffuse);
    }
    else if (str_eq(type.c_str(), LG_Apperance_Component_Type_Specular_String)) {
        
        lightArray_tryToAttributeVariable(LG_Apperance_Component_Value_XML_Att_Name, component, specular);
    }
    else {
        vector<string> *possibleValue=new vector<string>();
        possibleValue->push_back(string(LG_Apperance_Component_Type_Ambient_String));
        possibleValue->push_back(string(LG_Apperance_Component_Type_Diffuse_String));
        possibleValue->push_back(string(LG_Apperance_Component_Type_Specular_String));
        
        throw new LG_Parse_Exception_Wrong_Attribute_Value(
                                                           new string(component->Value()),
                                                           new string(LG_Apperance_Component_Type_XML_Att_Name),
                                                           new string(type),possibleValue);
        
    }

}