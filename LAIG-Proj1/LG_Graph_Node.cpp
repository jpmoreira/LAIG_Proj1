//
//  LG_Graph_Node.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 01/10/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//


#define LG_Graph_Node_Ref_XML_Tag_Name "noderef"
#define LG_Graph_Node_Ref_ID_XML_Att_Name "id"
#define LG_Graph_Node_ID_XML_Att_Name "id"
#define LG_Graph_Node_XML_Tag_Name "node"
#define LG_Graph_Node_Descendants_Tag_Name "descendants"
#define LG_Graph_Node_Primitives_Tag_Name "primitives"


#include "LG_Graph_Node.h"
#include "LG_Sphere.h"
#include "LG_Torus.h"
#include "LG_Cylinder.h"
#include "LG_Triangle.h"
#include "LG_Rectangle.h"



#pragma mark - Constructors
LG_Graph_Node::LG_Graph_Node(LG_Node_Map *map,TiXmlElement *elem)
:LG_Parsable_Node(map,identifierForGraphNode(elem))
{
    
    if (!str_eq(LG_Graph_Node_XML_Tag_Name, elem->Value())) {
        
        throw new LG_Parse_Exception_Wrong_Element_Name(LG_Graph_Node_XML_Tag_Name,elem->Value());
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
            for (int i=0; i<prims.size(); i++) {
                addChild(prims[i]);
            }
        }
        
        
        childElement=childElement->NextSiblingElement();
    }
    
    
    if (!descendantsSet) {
        throw new LG_Parse_Exception_Missing_Element(LG_Graph_Node_Descendants_Tag_Name);
    }
    if (!transformsSet) {
        throw new LG_Parse_Exception_Missing_Element(LG_Transforms_XML_Tag_Name);
    }
    if (!primitivesSet) {
        throw new LG_Parse_Exception_Missing_Element(LG_Graph_Node_Primitives_Tag_Name);
    }
    
    
    
}
LG_Graph_Node::LG_Graph_Node(LG_Node_Map *map,LG_Transform *t,vector<LG_Primitive *> &primitives,string identifier)
:LG_Parsable_Node(map,identifier),transform(t)
{
    
    for (int i=0; i<primitives.size(); i++) {
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
        

        this->addChild(ident);
        
        
        nodeRef=nodeRef->NextSiblingElement();
    }
    

}

vector<LG_Primitive *> LG_Graph_Node::handlePrimitives(LG_Node_Map *map,TiXmlElement *primitivesElement){

    vector<LG_Primitive *> primitives;
    
    TiXmlElement *potentialPrimitive=primitivesElement->FirstChildElement();
    
    while (potentialPrimitive) {
        
        
        
        if (str_eq(LG_Torus_XML_Tag_Name, potentialPrimitive->Value())) {
            primitives.push_back(new LG_Torus(map,potentialPrimitive));
        }
        else if (str_eq(LG_Sphere_XML_Tag_Name, potentialPrimitive->Value())) {
            primitives.push_back(new LG_Sphere(map,potentialPrimitive));
        }
        else if (str_eq(LG_Cylinder_XML_Tag_Name, potentialPrimitive->Value())) {
            primitives.push_back(new LG_Cylinder(map,potentialPrimitive));
        }
        else if (str_eq(LG_Triangle_XML_Tag_Name, potentialPrimitive->Value())) {
            primitives.push_back(new LG_Triangle(map,potentialPrimitive));
        }
        else if (str_eq(LG_Rectangle_XML_Tag_Name, potentialPrimitive->Value())) {
            primitives.push_back(new LG_Rectangle(map,potentialPrimitive));
        }
        
        
        potentialPrimitive=potentialPrimitive->NextSiblingElement();
    }
    
    
    return primitives;
}
