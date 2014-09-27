//
//  LG_Drawing.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 26/09/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_Drawing.h"

#define LG_Drawing_Fill_String "fill"
#define LG_Drawing_Line_String "line"
#define LG_Drawing_Point_String "point"

#define LG_Drawing_Mode_Att_Name "mode"

#define LG_Shading_Mode_Att_Name "shading"

#define LG_Background_Att_Name "background"


#define LG_Shading_Flat_String "flat"
#define LG_Shading_Gourad_String "gourad"

#define LG_Drawing_Node_Name "drawing"





LG_Drawing::LG_Drawing(LG_Node_Map *map,TiXmlNode *node):LG_Parsable_Node(map,_LG_Drawing_NodeID),mode(LG_Drawing_Not_Set),shading(LG_Shading_Not_Set){
    
    
    
    
    verifyElementAttributesAndValues(node);
    verifyElementAttributesAndValues(node);
    
}

LG_Drawing::LG_Drawing(LG_Node_Map *map,LG_Drawing_Mode md,LG_Shading_Mode shading,LG_LightArray bkg):LG_Parsable_Node(map,_LG_Drawing_NodeID),mode(md),shading(shading){
    
    for (int i=0; i<4; i++) {
        background[i]=bkg[i];
    }
    
    
}


void verifyElementName(TiXmlElement *element){
    
    if(strcmp(element->Value(), LG_Drawing_Node_Name)==0)return;
    
    
    string *expected=new string(LG_Drawing_Node_Name);
    string *actual=new string(element->Value());
    throw new LG_Parse_Exception_Wrong_Element_Name(expected,actual);
    

}

void verifyElementAttributesAndValues(TiXmlElement *element){
    
    
    TiXmlAttribute *att=element->FirstAttribute();//get first attribute
    
    while (att) {
        
        str_eq(att->Name(), LG_Drawing_Mode_Att_Name)
        if (str_eq(att->Name(), LG_Drawing_Mode_Att_Name)){
        
            
            char * values[3];
            
            values[0]=LG_Drawing_Fill_String;
            values[1]=LG_Drawing_Line_String;
            values[2]=LG_Drawing_Point_String;
            
            int value=LG_Parsable_Node::stringValue(att, values, 3);
            if (value>=0) this->mode=(LG_Drawing_Mode)value;//possible to cast right away
           
            
        }
        
        else if (str_eq(att->Name(), LG_Shading_Mode_Att_Name)){
            
            char * values[2];
            
            values[0]=LG_Shading_Flat_String;
            values[1]=LG_Shading_Gourad_String;
            
            int value=LG_Parsable_Node::stringValue(att, values, 2);
            if (values>=0) this->mode=(LG_Shading_Mode)value;

        
        }
        
        else if(str_eq(att->Name(), LG_Background_Att_Name)){
        
            
            LG_Parsable_Node::lightArrayValue(att, this->background);
        }
        
        att=att->Next();
    }
    
    
    //if any parameter is not set then this attribute is missing
    if (mode==LG_Drawing_Not_Set)
        throw new LG_Parse_Exception_Missing_Attribute(LG_Drawing_Node_Name,LG_Drawing_Mode_Att_Name);
   
    else if(shading==LG_Shading_Not_Set)
        throw new LG_Parse_Exception_Missing_Attribute(LG_Drawing_Node_Name,LG_Shading_Mode_Att_Name);
    
    else if(background[0]==LG_LightValue_Not_Set)
        throw new LG_Parse_Exception_Missing_Attribute(LG_Drawing_Node_Name,LG_Background_Att_Name);
    


}



