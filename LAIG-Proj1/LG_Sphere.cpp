//
//  LG_Sphere.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 28/09/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_Sphere.h"

#define _LG_Primitive_Name "_LG_Sphere_"


#define LG_Sphere_XML_Slices_Att_Name "slices"
#define LG_Sphere_XML_Stacks_Att_Name "stacks"
#define LG_Sphere_XML_Radius_Att_Name "radius"

int LG_Sphere::_LG_classIDNr=0;

#pragma mark - Constructors
LG_Sphere::LG_Sphere(LG_Node_Map *map,TiXmlElement *elem):LG_Glu_Primitive(map,autoIdentifier(_LG_Primitive_Name,_LG_classIDNr)),radius(LG_INVALID_DOUBLE),slices(LG_INVALID_INT),stacks(LG_INVALID_INT){
    
    
    
    if (!str_eq(LG_Sphere_XML_Tag_Name, elem->Value())) {
        throw new LG_Parse_Exception_Wrong_Element_Name(new string(LG_Sphere_XML_Tag_Name),new string(elem->Value()));
    }
    
    
    positiveDouble_tryToAttributeVariable(LG_Sphere_XML_Radius_Att_Name, elem, radius);
    
    positiveInt_tryToAttributeVariable(LG_Sphere_XML_Slices_Att_Name, elem, slices);
    positiveInt_tryToAttributeVariable(LG_Sphere_XML_Stacks_Att_Name, elem, stacks);
    
}


LG_Sphere::LG_Sphere(LG_Node_Map *map,TiXmlElement *elem,LG_Appearance *app):LG_Glu_Primitive(map,autoIdentifier(_LG_Primitive_Name,_LG_classIDNr),app),radius(LG_INVALID_DOUBLE),slices(LG_INVALID_INT),stacks(LG_INVALID_INT){

    if (!str_eq(LG_Sphere_XML_Tag_Name, elem->Value())) {
        throw new LG_Parse_Exception_Wrong_Element_Name(new string(LG_Sphere_XML_Tag_Name),new string(elem->Value()));
    }
    
    
    positiveDouble_tryToAttributeVariable(LG_Sphere_XML_Radius_Att_Name, elem, radius);
    
    positiveInt_tryToAttributeVariable(LG_Sphere_XML_Slices_Att_Name, elem, slices);
    positiveInt_tryToAttributeVariable(LG_Sphere_XML_Stacks_Att_Name, elem, stacks);


}
LG_Sphere::LG_Sphere(LG_Node_Map *map,double r,int st,int sl):LG_Glu_Primitive(map,autoIdentifier(_LG_Primitive_Name,_LG_classIDNr)),radius(r),slices(sl),stacks(st){


}


#pragma mark - Inherited Methods


void LG_Sphere::draw() {
    
    LG_Primitive::draw();
    
    gluSphere(quadric, radius, slices, stacks);
}


void LG_Sphere::calculateTextureCoordinates(){


}
