//
//  LG_Button.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 30/12/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_Button.h"
#include "LG_Tzaar.h"


#define LG_Button_Action_XML_Att_Name "action"
#define LG_Button_Param_XML_Att_Name "param"


LG_Button::LG_Button(LG_Node_Map *map,LG_Node_Map *appearances_map,LG_Node_Map *animations_map,TiXmlElement *elem):LG_Graph_Node(map,appearances_map,animations_map,elem,false){
    
    selectable=true;
    
    evalElemName(LG_Button_XML_Tag_Name, elem->Value());
    
	string_tryToAttributeVariable(LG_Button_Action_XML_Att_Name, elem, action);
    
    
    try {
        int_tryToAttributeVariable(LG_Button_Param_XML_Att_Name, elem, param);
    } catch (LG_Parse_Exception_Missing_Attribute *ex) {
        param=0;
    }
    
}


void LG_Button::setSelected(bool selected){

    LG_Node::setSelected(selected);
    
    LG_Tzaar::getCurrentTzaar()->invoke(action,param);

}



