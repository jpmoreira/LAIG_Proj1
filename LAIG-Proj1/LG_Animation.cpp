//
//  LG_Animation.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 28/10/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_Animation.h"
#include "LG_CircularAnimation.h"
#include "LG_LinearAnimation.h"

#include "LG_AnimationState.h"


#define LG_Animation_Span_XML_Att_Name "span"

#define LG_Animation_Type_XML_Att_Name "type"

#define LG_Animation_Type_Linear_XML_Att_Value "linear"
#define LG_Animation_Type_Circular_XML_Att_Value "circular"




typedef enum{

    LG_Animation_Type_Linear,
    LG_Animation_Type_Circular

} LG_Animation_Type;

#pragma mark - Constructors

LG_Animation::LG_Animation(LG_Node_Map *map,string identifier,double dur):LG_Parsable_Node(map,identifier),span(dur){

    
}


LG_Animation::LG_Animation(LG_Node_Map *map,TiXmlElement *elem):LG_Parsable_Node(map,extractIDForSuper(elem)),span(LG_INVALID_DOUBLE){

    
    evalElemName(LG_Animation_XML_Tag_Name, elem->Value());
    
    positiveDouble_tryToAttributeVariable(LG_Animation_Span_XML_Att_Name, elem, span);
    span *=1000;//conversion to milliseconds

}


LG_Animation * LG_Animation::animationForElement(LG_Node_Map *map,TiXmlElement *elem){
    
    evalElemName(LG_Animation_XML_Tag_Name, elem->Value());
    
    int type;
    
    vector<string> possibleTypes;
    possibleTypes.push_back(LG_Animation_Type_Linear_XML_Att_Value);
    possibleTypes.push_back(LG_Animation_Type_Circular_XML_Att_Value);
    
    
    enum_tryToAttribute(LG_Animation_Type_XML_Att_Name, elem, type, &possibleTypes);
    
    if (type==LG_Animation_Type_Linear) {
        
        return new LG_LinearAnimation(map,elem);
    }
    
    else if(type==LG_Animation_Type_Circular){
        
        return new LG_CircularAnimation(map, elem);
    }
    
    
    return NULL;//should never happen cause exception is thrown



}



#pragma mark - Helper Methods
string LG_Animation::extractIDForSuper(TiXmlElement *elem){

    
    string id;
    string_tryToAttributeVariable(LG_Animation_ID_XML_Att_Name, elem, id);
    
    return id;

}