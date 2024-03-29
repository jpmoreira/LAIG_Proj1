//
//  LG_Cylinder.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 28/09/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_Cylinder.h"


#define _LG_Primitive_Name "_LG_Cylinder_"
#define LG_Cylinder_XML_Top_Att_Name "top"
#define LG_Cylinder_XML_Base_Att_Name "base"
#define LG_Cylinder_XML_Stacks_Att_Name "stacks"
#define LG_Cylinder_XML_Slices_Att_Name "slices"
#define LG_Cylinder_XML_Height_Att_Name "height"
int LG_Cylinder::_LG_classIDNr=0;

#pragma mark - Constructors
LG_Cylinder::LG_Cylinder(LG_Node_Map *map,TiXmlElement *elem):LG_Glu_Primitive(map,autoIdentifier(_LG_Primitive_Name,_LG_classIDNr)),baseRadius(LG_INVALID_DOUBLE),topRadius(LG_INVALID_DOUBLE),stacks(LG_INVALID_INT),slices(LG_INVALID_INT),height(LG_INVALID_DOUBLE){
    
    
    if (!str_eq(LG_Cylinder_XML_Tag_Name, elem->Value())) {
        throw  new LG_Parse_Exception_Wrong_Element_Name(new string(LG_Cylinder_XML_Tag_Name),new string(elem->Value()));
    }
    
    
    
    nonNegativeDouble_tryToAttributeVariable(LG_Cylinder_XML_Top_Att_Name, elem, topRadius);
    nonNegativeDouble_tryToAttributeVariable(LG_Cylinder_XML_Base_Att_Name, elem, baseRadius);
    positiveDouble_tryToAttributeVariable(LG_Cylinder_XML_Height_Att_Name, elem, height);
    positiveInt_tryToAttributeVariable(LG_Cylinder_XML_Slices_Att_Name, elem, slices);
    positiveInt_tryToAttributeVariable(LG_Cylinder_XML_Stacks_Att_Name, elem, stacks);
    
    

}

LG_Cylinder::LG_Cylinder(LG_Node_Map *map,TiXmlElement *elem,LG_Appearance *app):LG_Glu_Primitive(map,autoIdentifier(_LG_Primitive_Name,_LG_classIDNr),app),baseRadius(LG_INVALID_DOUBLE),topRadius(LG_INVALID_DOUBLE),stacks(LG_INVALID_INT),slices(LG_INVALID_INT),height(LG_INVALID_DOUBLE){
    
    
    if (!str_eq(LG_Cylinder_XML_Tag_Name, elem->Value())) {
        throw  new LG_Parse_Exception_Wrong_Element_Name(new string(LG_Cylinder_XML_Tag_Name),new string(elem->Value()));
    }
    
    
    
    nonNegativeDouble_tryToAttributeVariable(LG_Cylinder_XML_Top_Att_Name, elem, topRadius);
    nonNegativeDouble_tryToAttributeVariable(LG_Cylinder_XML_Base_Att_Name, elem, baseRadius);
    positiveDouble_tryToAttributeVariable(LG_Cylinder_XML_Height_Att_Name, elem, height);
    positiveInt_tryToAttributeVariable(LG_Cylinder_XML_Slices_Att_Name, elem, slices);
    positiveInt_tryToAttributeVariable(LG_Cylinder_XML_Stacks_Att_Name, elem, stacks);
    
    
    
}


LG_Cylinder::LG_Cylinder(LG_Node_Map *map,double base,double top,double h,int st,int sl):LG_Glu_Primitive(map,autoIdentifier(_LG_Primitive_Name,_LG_classIDNr)),baseRadius(base),topRadius(top),height(h),stacks(st),slices(sl){


}



#pragma mark - Inherited Methods

void LG_Cylinder::draw(bool selectMode) {
    
    
    LG_Primitive::draw(selectMode);
    glPushMatrix();
    glRotated(180, 1, 0, 0);
    gluDisk(quadric, 0, baseRadius, slices, stacks);
    glPopMatrix();
    gluCylinder(quadric, baseRadius, topRadius, height, slices, stacks);
    glPushMatrix();
    glTranslated(0, 0, height);
    gluDisk(quadric, 0, topRadius, slices, stacks);
    glPopMatrix();
}

#pragma mark - Helper Methods

void LG_Cylinder::calculateTextureCoordinates(){


}
