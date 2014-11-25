//
//  LG_Graph_Node.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 01/10/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//
#ifdef _WIN32
#include <Windows.h>	//Using WINDOWS sdk tools to compile the project, Windows.h must be included before any #include <GL/*****>
#endif

#define LG_Graph_Node_Ref_XML_Tag_Name "noderef"
#define LG_Graph_Node_Ref_ID_XML_Att_Name "id"
#define LG_Graph_Node_ID_XML_Att_Name "id"
#define LG_Graph_Node_DisplayList_Att_Name "displaylist"

#define LG_Graph_Node_Descendants_Tag_Name "descendants"
#define LG_Graph_Node_Primitives_Tag_Name "primitives"
#define LG_Graph_Node_Appearances_Ref_XML_Tag_Name "appearanceref"
#define LG_Graph_Node_Animation_Ref_XML_Tag_Name "animationref"


#define LG_Appearance_Ref_Inherit_String "inherit"


#include <GL/glu.h>

#include "LG_Graph_Node.h"
#include "LG_Sphere.h"
#include "LG_Torus.h"
#include "LG_Cylinder.h"
#include "LG_Triangle.h"
#include "LG_Rectangle.h"
#include "LG_Transform.h"
#include "LG_Appearance.h"
#include "LG_Flag.h"

#include <iostream>


#pragma mark - Constructors
LG_Graph_Node::LG_Graph_Node(LG_Node_Map *map,LG_Node_Map *app_map,LG_Node_Map *anim_map, TiXmlElement *elem)
:LG_Parsable_Node(map,identifierForGraphNode(elem)),animations(vector<LG_AnimationState *>()),appearance(NULL),currentAnimation(0)
{
    
    if (!str_eq(LG_Graph_Node_XML_Tag_Name, elem->Value())) {
        
        throw new LG_Parse_Exception_Wrong_Element_Name(LG_Graph_Node_XML_Tag_Name,elem->Value());
    }
    
    try {
        bool_tryToAttributeVariable(LG_Graph_Node_DisplayList_Att_Name, elem, isDisplayList);
    } catch (LG_Parse_Exception_Missing_Attribute *ex) {
        isDisplayList=false;
    }
    catch(LG_Parse_Exception_Wrong_Attribute_Value *ex){
        
        std::cout<<"Parsing Error Found: "<<std::endl;
        std::cout<<ex->what()<<std::endl;
        std::cout<<"Error was Ignored. False value assumed."<<std::endl;
        
        
    }
    
    
    bool descendantsSet=false;
    bool transformsSet=false;
    bool primitivesSet=false;
    
    
    
    TiXmlElement *childElement=elem->FirstChildElement();
    
    
    while (childElement) {
        
        if (str_eq(LG_Graph_Node_Descendants_Tag_Name, childElement->Value())) {
            descendantsSet=true;
            handleDescendants(map, childElement);
        }
        
        else if (str_eq(LG_Transforms_XML_Tag_Name, childElement->Value())){
            
            transformsSet=true;
            transform=new LG_Transform(map,childElement);
            
        }
        else if(str_eq(LG_Graph_Node_Primitives_Tag_Name, childElement->Value())){
            primitivesSet=true;
            vector<LG_Primitive *> prims=handlePrimitives(map, childElement);
            for (unsigned int i=0; i<prims.size(); i++) {
                addChild(prims[i]);
            }
        }
        
        else if (str_eq(LG_Graph_Node_Appearances_Ref_XML_Tag_Name, childElement->Value())){
            handleAppearance(app_map, childElement);
        }
        
        else if(str_eq(LG_Graph_Node_Animation_Ref_XML_Tag_Name, childElement->Value())){
            handleAnimation(anim_map, childElement);
        }
        
        
        
        
        childElement=childElement->NextSiblingElement();
    }
    
    
    if (!transformsSet) {
        throw new LG_Parse_Exception_Missing_Element(LG_Transforms_XML_Tag_Name);
    }
    //if (!primitivesSet) {
    //    throw new LG_Parse_Exception_Missing_Element(LG_Graph_Node_Primitives_Tag_Name);
    //}
    
    
    
    
}
LG_Graph_Node::LG_Graph_Node(LG_Node_Map *map,LG_Node_Map *app_map,LG_Node_Map *anim_map, LG_Transform *t,vector<LG_Primitive *> &primitives,string identifier)
:LG_Parsable_Node(map,identifier),transform(t),animations(vector<LG_AnimationState *>()),appearance(NULL),currentAnimation(0)
{
    
    for (unsigned int i=0; i<primitives.size(); i++) {
        LG_Primitive *p=primitives[i];
        this->addChild(p);
    }
    
}


#pragma mark - Helper Methods


string LG_Graph_Node::identifierForGraphNode(TiXmlElement *elem){
    
    string ident;
    
    string_tryToAttributeVariable(LG_Graph_Node_ID_XML_Att_Name, elem, ident);
    
    return ident;
    
}


void LG_Graph_Node::handleDescendants(LG_Node_Map *map,TiXmlElement *descendantsElement){
    
    TiXmlElement *nodeRef=descendantsElement->FirstChildElement();
    
    
    while (nodeRef) {
        
        //if it's not a node ref throw exception
        if (!str_eq(LG_Graph_Node_Ref_XML_Tag_Name, nodeRef->Value())) {
            throw new LG_Parse_Exception_Wrong_Element_Name(LG_Graph_Node_Ref_XML_Tag_Name,nodeRef->Value());
        }
        
        
        
        string ident;
        
        string_tryToAttributeVariable(LG_Graph_Node_Ref_ID_XML_Att_Name,nodeRef,ident);
        
        if (str_eq(ident.c_str(), identifier.c_str())) {//if we refer ourselfs as our fathers
            
            throw new LG_Parse_Exception_Redundant_Reference(new string(identifier));
            
        }
        
        
        this->addChild(ident);
        
        
        nodeRef=nodeRef->NextSiblingElement();
        
    }
    
    
}

vector<LG_Primitive *> LG_Graph_Node::handlePrimitives(LG_Node_Map *map, TiXmlElement *primitivesElement){
    
    vector<LG_Primitive *> primitives;
    
    TiXmlElement *potentialPrimitive = primitivesElement->FirstChildElement();
    
    while (potentialPrimitive) {
        
        
        
        if (str_eq(LG_Torus_XML_Tag_Name, potentialPrimitive->Value())) {
            primitives.push_back(new LG_Torus(map, potentialPrimitive));
        }
        else if (str_eq(LG_Sphere_XML_Tag_Name, potentialPrimitive->Value())) {
            primitives.push_back(new LG_Sphere(map, potentialPrimitive));
        }
        else if (str_eq(LG_Cylinder_XML_Tag_Name, potentialPrimitive->Value())) {
            primitives.push_back(new LG_Cylinder(map, potentialPrimitive));
        }
        else if (str_eq(LG_Triangle_XML_Tag_Name, potentialPrimitive->Value())) {
            primitives.push_back(new LG_Triangle(map, potentialPrimitive));
        }
        else if (str_eq(LG_Rectangle_XML_Tag_Name, potentialPrimitive->Value())) {
            primitives.push_back(new LG_Rectangle(map, potentialPrimitive));
        }
        else if (str_eq(LG_Plane_XML_Tag_Name, potentialPrimitive->Value())){
            
            primitives.push_back(new LG_Plane(map, potentialPrimitive));
        }
        else if (str_eq(LG_Patch_XML_Tag_Name, potentialPrimitive->Value())){
            primitives.push_back(new LG_Patch(map, potentialPrimitive));
        }
        else if (str_eq(LG_Flag_XML_Tag_Name, potentialPrimitive->Value())){
            primitives.push_back(new LG_Flag(map, potentialPrimitive));
        }
        potentialPrimitive = potentialPrimitive->NextSiblingElement();
    }
    
    
    return primitives;
}


void LG_Graph_Node::handleAppearance(LG_Node_Map *map,TiXmlElement *appearanceElement){
    
    string id;
    string_tryToAttributeVariable(LG_Appearance_ID_XML_Att_Name, appearanceElement, id);
    
    if (str_eq(id.c_str(), LG_Appearance_Ref_Inherit_String))appearance=NULL;
    
    else{
        
        auto it=map->find(id);
        
        
        
        if (it==map->end()) {
            throw new LG_Parse_Exception_Broken_Reference(LG_Graph_Node_XML_Tag_Name,id.c_str(),LG_Appearance_XML_Tag_Name);
        }
        else appearance=(LG_Appearance *)it->second;
        
    }
    
    
}

void LG_Graph_Node::handleAnimation(LG_Node_Map *map, TiXmlElement *animationElement){
    
    string id;
    
    string_tryToAttributeVariable(LG_Animation_ID_XML_Att_Name, animationElement, id);
    
    auto it=map->find(id);
    
    if (it==map->end()) {
        throw new LG_Parse_Exception_Broken_Reference(LG_Graph_Node_XML_Tag_Name,id.c_str(),LG_Animation_XML_Tag_Name);
    }
    else animations.push_back(new LG_AnimationState(this->map,(LG_Animation *)it->second));
}

#pragma mark - Drawing


void LG_Graph_Node::draw(){
    
    
    
    if (isDisplayList){
        
        glCallList(displayListID);
        
    }
    
    
    else{
        
        glPushMatrix();
        
        
       
        
        
        if(animations.size()>0){
            
            for (int i=currentAnimation; i>=0; i--) {
                
                animations.at(i)->apply();
                
            }
        }
        
        
         transform->draw();
        
        
        if (appearance) appearance->apply();
        
        
        for (unsigned int i=0; i<childsIDs.size(); i++) {
            
            child(i)->draw();
            
        }
        
        if (appearance) appearance->unapply();
        
        glPopMatrix();
        
    }
    
    
    
}

#pragma mark - Configuration


void LG_Graph_Node::config(){
    
    if (isDisplayList) {
        
        displayListID=glGenLists(1);
        
        glNewList(displayListID, GL_COMPILE);
        
        isDisplayList=false;//force displaylist to be false so draw is performed
        
        draw();
        
        isDisplayList=true;//displaylist value back to correct one
        
        glEndList();
        
    }
    
    
    for (int i=0; i<childsIDs.size(); i++) {
        
        child(i)->config();
    }
    
    
}


void LG_Graph_Node::update(unsigned long time){


    
    
    if (animations.size()>0) {
        LG_AnimationState *currentAnimationState=animations.at(currentAnimation);
        
        if (currentAnimationState->finished(time) && currentAnimation+1<animations.size()) {//change to next animation if this one has finished (and if there is one)
            currentAnimation++;
        }
        
        animations.at(currentAnimation)->update(time);
        

    }
    
    for (int i=0; i<childsIDs.size(); i++) {
        
        child(i)->update(time);
    }
    
}



