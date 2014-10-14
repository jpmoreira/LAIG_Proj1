//
//  LG_Torus.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 29/09/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_Torus.h"

#define _LG_Primitive_Name "_LG_Torus_"
#define LG_Torus_XML_Inner_Att_Name "inner"
#define LG_Torus_XML_Outer_Att_Name "outer"
#define LG_Torus_XML_Slices_Att_Name "slices"
#define LG_Torus_XML_Loops_Att_Name "loops"

int LG_Torus::_LG_classIDNr=0;

LG_Torus::LG_Torus(LG_Node_Map *map,TiXmlElement *elem):LG_Primitive(map,autoIdentifier){
    
    
    //verify element name
    if (!str_eq(elem->Value(), LG_Torus_XML_Tag_Name)) {
        throw  new LG_Parse_Exception_Wrong_Element_Name(new string(LG_Torus_XML_Tag_Name),new string(elem->Value()));
    }
    
    
    positiveDouble_tryToAttributeVariable(LG_Torus_XML_Inner_Att_Name, elem, innerRadius);
    positiveDouble_tryToAttributeVariable(LG_Torus_XML_Outer_Att_Name, elem, outerRadius);
    positiveInt_tryToAttributeVariable(LG_Torus_XML_Slices_Att_Name, elem, slices);
    positiveInt_tryToAttributeVariable(LG_Torus_XML_Loops_Att_Name, elem, loops);
    
    
    
    

}

LG_Torus::LG_Torus(LG_Node_Map *map,TiXmlElement *elem,LG_Appearance *app):LG_Primitive(map,autoIdentifier,app){
    
    
    //verify element name
    if (!str_eq(elem->Value(), LG_Torus_XML_Tag_Name)) {
        throw  new LG_Parse_Exception_Wrong_Element_Name(new string(LG_Torus_XML_Tag_Name),new string(elem->Value()));
    }
    
    
    positiveDouble_tryToAttributeVariable(LG_Torus_XML_Inner_Att_Name, elem, innerRadius);
    positiveDouble_tryToAttributeVariable(LG_Torus_XML_Outer_Att_Name, elem, outerRadius);
    positiveInt_tryToAttributeVariable(LG_Torus_XML_Slices_Att_Name, elem, slices);
    positiveInt_tryToAttributeVariable(LG_Torus_XML_Loops_Att_Name, elem, loops);
    
    
    
    
    
}



LG_Torus::LG_Torus(LG_Node_Map *map,double inner,double outer,int sl,int loop):LG_Primitive(map,autoIdentifier){


}


#pragma mark - Inherited Methods
void LG_Torus::draw()
{
    
    LG_Primitive::draw();
	glutSolidTorus(this->innerRadius, this->outerRadius, this->slices, this->loops);
}


void LG_Torus::calculateTextureCoordinates(){


}