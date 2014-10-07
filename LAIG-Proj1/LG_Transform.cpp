//
//  LG_Transform.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 30/09/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_Transform.h"
#include <GL/glut.h>

#define LG_Individual_Transform_XML_Tag_Name "transform"
#define LG_Transform_Type_XML_Att_Name "type"
#define LG_Transform_Angle_XML_Att_Name "angle"
#define LG_Transform_Axis_XML_Att_Name "axis"
#define LG_Transform_To_XML_Att_Name "to"
#define LG_Transform_Factor_XML_Att_Name "factor"

#define LG_Transform_Type_Translation_String "translate"
#define LG_Transform_Type_Rotation_String "rotate"
#define LG_Transform_Type_Scaling_String "scale"



#define LG_Transform_Axis_X_String "x"
#define LG_Transform_Axis_Y_String "y"
#define LG_Transform_Axis_Z_String "z"



#define _LG_Primitive_Name "_LG_Transform_"

typedef enum {

    LG_X_Axis,
    LG_Y_Axis,
    LG_Z_Axis,
    LG_Invalid_Axis

}LG_Transform_Axis;



int LG_Transform::_LG_classIDNr=0;

#pragma mark - Constructors

LG_Transform::LG_Transform(LG_Node_Map *map,TiXmlElement *elem):LG_Parsable_Node(map,autoIdentifier){
    
    
    if (!str_eq(LG_Transforms_XML_Tag_Name, elem->Value())) {
        
        throw new LG_Parse_Exception_Wrong_Element_Name(LG_Transforms_XML_Tag_Name,elem->Value());
    }
    
    
    TiXmlElement *transform= elem->FirstChildElement();
    
    
    glLoadIdentity();//load identity
    
    while (transform) {
        
        
        if (str_eq(LG_Individual_Transform_XML_Tag_Name, transform->Value())) {
            
            applyMatrixForTransform(transform);
        }
        
        //if its no transform throw exception
        else throw new LG_Parse_Exception_Wrong_Element_Name(LG_Individual_Transform_XML_Tag_Name, transform->Value());
        
        
        transform=transform->NextSiblingElement();
        
    }
    
    
    glGetDoublev(GL_MODELVIEW_MATRIX, (GLdouble *)matrix);
    
    
    
}

LG_Transform::LG_Transform(LG_Node_Map *map,LG_Matrix m):LG_Parsable_Node(map,autoIdentifier){
    
    
    copyMatrix(m, matrix);
    
    
    
}



#pragma mark - Matrix Generation


void LG_Transform::applyMatrixForTransform(TiXmlElement *element){
    
    
    if (isTranslation(element)) {
        return applyTranslation(element);
    }
    else if (isRotation(element)){
        return applyRotation(element);
    }
    else if (isScale(element)){
        return applyScaling(element);
    }
    else{
        
        vector<string> *aceptableValues=new vector<string>();
        aceptableValues->push_back(string(LG_Transform_Type_Translation_String));
        aceptableValues->push_back(string(LG_Transform_Type_Rotation_String));
        aceptableValues->push_back(string(LG_Transform_Type_Scaling_String));
        
        throw new LG_Parse_Exception_Wrong_Attribute_Value(LG_Individual_Transform_XML_Tag_Name, LG_Transform_Type_XML_Att_Name, element->Attribute(LG_Transform_Type_XML_Att_Name), aceptableValues);
    }
    
    
    
    
    
}
void LG_Transform::applyRotation(TiXmlElement *element){
    
    double angle;
    int axis;
    
    vector<string> possibleAxis;
    possibleAxis.push_back(LG_Transform_Axis_X_String);
    possibleAxis.push_back(LG_Transform_Axis_Y_String);
    possibleAxis.push_back(LG_Transform_Axis_Z_String);
    enum_tryToAttribute(LG_Transform_Axis_XML_Att_Name, element, axis, &possibleAxis);
    double_tryToAttributeVariable(LG_Transform_Angle_XML_Att_Name, element, angle);
    
    if (axis==LG_X_Axis) glRotated(angle, 1, 0, 0);
    else if(axis==LG_Y_Axis) glRotated(angle, 0, 1, 0);
    else if(axis==LG_Z_Axis) glRotated(angle, 0, 0, 1);
    
    
    
    
    
    
}
void LG_Transform::applyTranslation(TiXmlElement *element){
    
    
    LG_Point3D pt;
    
    point3D_tryToAttributeVariable(LG_Transform_To_XML_Att_Name, element, pt);
    
    glTranslated(pt[0], pt[1], pt[2]);
    
    

}
void LG_Transform::applyScaling(TiXmlElement *element){

    
    LG_Point3D factor;
    
    point3D_tryToAttributeVariable(LG_Transform_Factor_XML_Att_Name, element, factor);
    
    glScaled(factor[0], factor[1], factor[2]);


}

#pragma mark - Transform type identification


bool LG_Transform::isTranslation(TiXmlElement *elem){
    
    const char * type=elem->Attribute(LG_Transform_Type_XML_Att_Name);
    if (type==NULL)return false;
    
    return str_eq(type, LG_Transform_Type_Translation_String);
    

}
bool LG_Transform::isRotation(TiXmlElement *elem){
    const char * type=elem->Attribute(LG_Transform_Type_XML_Att_Name);
    if (type==NULL)return false;
    
    return str_eq(type, LG_Transform_Type_Rotation_String);

}
bool LG_Transform::isScale(TiXmlElement *elem){
    const char * type=elem->Attribute(LG_Transform_Type_XML_Att_Name);
    if (type==NULL)return false;
    
    return str_eq(type, LG_Transform_Type_Scaling_String);


}


#pragma mark - Matrix copy


void LG_Transform::copyMatrix(LG_Matrix origin,LG_Matrix destination){

    for (int i=0; i<LG_Matrix_Dimention; i++) {
        
        for (int f; f<LG_Matrix_Dimention; f++) {
            destination[i][f]=origin[i][f];
        }
    }

}


#pragma mark - Drawing


void LG_Transform::draw(){
    
    glMultMatrixd((GLdouble *)matrix);

}
