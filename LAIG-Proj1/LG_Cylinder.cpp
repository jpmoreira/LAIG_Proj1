//
//  LG_Cylinder.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 28/09/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_Cylinder.h"


#define _LG_Primitive_Name "_LG_Cylinder_"
#define LG_Cylinder_XML_Tag_Name "cylinder"
#define LG_Cylinder_XML_Top_Att_Name "top"
#define LG_Cylinder_XML_Base_Att_Name "base"
#define LG_Cylinder_XML_Stacks_Att_Name "stacks"
#define LG_Cylinder_XML_Slices_Att_Name "slices"
#define LG_Cylinder_XML_Height_Att_Name "height"
int LG_Cylinder::_LG_classIDNr=0;

#pragma mark - Constructors
LG_Cylinder::LG_Cylinder(LG_Node_Map *map,TiXmlElement *elem):LG_Primitive(map,autoIdentifier),baseRadius(LG_INVALID_DOUBLE),topRadius(LG_INVALID_DOUBLE),stacks(LG_INVALID_INT),slices(LG_INVALID_INT),height(LG_INVALID_DOUBLE){
    
    
    verifyElementName(elem);
    verifyElementAttributesAndValues(elem);


}
LG_Cylinder::LG_Cylinder(LG_Node_Map *map,double base,double top,double h,int st,int sl):LG_Primitive(map,autoIdentifier),baseRadius(base),topRadius(top),height(h),stacks(st),slices(sl){


}



#pragma mark - Inherited Methods


void LG_Cylinder::verifyElementName(TiXmlElement *element){
    
    if (!str_eq(LG_Cylinder_XML_Tag_Name, element->Value())) {
        throw  new LG_Parse_Exception_Wrong_Element_Name(new string(LG_Cylinder_XML_Tag_Name),new string(element->Value()));
    }

}

void LG_Cylinder::verifyElementAttributesAndValues(TiXmlElement *element){
    
    
    TiXmlAttribute *att=element->FirstAttribute();
    
    while (att) {
        
        
        if (str_eq(att->Name(), LG_Cylinder_XML_Top_Att_Name)) {
            
            topRadius=positiveDoubleValueForAttribute(att);
        }
        
        else if (str_eq(att->Name(), LG_Cylinder_XML_Base_Att_Name)) {
            
            baseRadius=positiveDoubleValueForAttribute(att);
        }
        
        else if (str_eq(att->Name(), LG_Cylinder_XML_Height_Att_Name)) {
            
            height=positiveDoubleValueForAttribute(att);
        }
        
        else if (str_eq(att->Name(), LG_Cylinder_XML_Stacks_Att_Name)) {
            
            stacks=positiveIntValueForAttribute(att);
        }
        
        else if (str_eq(att->Name(), LG_Cylinder_XML_Slices_Att_Name)) {
            
            slices=positiveIntValueForAttribute(att);
        }
        
        att=att->Next();
    }
    
    
    if (topRadius==LG_INVALID_DOUBLE) {
        throw new LG_Parse_Exception_Missing_Attribute(new string(LG_Cylinder_XML_Tag_Name),new string(LG_Cylinder_XML_Top_Att_Name));
    }
    
    if (baseRadius==LG_INVALID_DOUBLE) {
        throw new LG_Parse_Exception_Missing_Attribute(new string(LG_Cylinder_XML_Tag_Name),new string(LG_Cylinder_XML_Base_Att_Name));
    }
    
    if (height==LG_INVALID_DOUBLE) {
        throw new LG_Parse_Exception_Missing_Attribute(new string (LG_Cylinder_XML_Tag_Name),new string(LG_Cylinder_XML_Height_Att_Name));
    }
    
    if (slices==LG_INVALID_INT) {
        throw new LG_Parse_Exception_Missing_Attribute(new string(LG_Cylinder_XML_Tag_Name),new string(LG_Cylinder_XML_Slices_Att_Name));
    }
    
    if (stacks==LG_INVALID_INT) {
        throw new LG_Parse_Exception_Missing_Attribute(new string(LG_Cylinder_XML_Tag_Name),new string(LG_Cylinder_XML_Stacks_Att_Name));
    }
    
    
    
    

}