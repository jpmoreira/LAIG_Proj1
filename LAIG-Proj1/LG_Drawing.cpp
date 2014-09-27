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


#define LG_Shading_Flat_String "flat"
#define LG_Shading_Gourad_String "gourad"

#define LG_Drawing_Node_Name "drawing"


LG_Drawing::LG_Drawing(LG_Node_Map *map,TiXmlNode *node):LG_Parsable_Node(map,_LG_Drawing_NodeID),mode(LG_Drawing_Not_Set),shading(LG_Shading_Not_Set){
    
    
    
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
    
    
    TiXmlAttribute *att=element->FirstAttribute();
    
    while (att) {
        if (strcmp(att->Name(), LG_Drawing_Mode_Att_Name)==0){
        
           
        }
        
        else if (strcmp(att->Name(), LG_Shading_Mode_Att_Name)==0){
        
        }
        
        att=att->Next();
    }
    
    if (mode==LG_Drawing_Not_Set) {
        <#statements#>
    }
    
    


}



