#ifndef LG_ALL_TESTS
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.h"
#define private public //disable encapsulation for following files, allowing testing to be done
#define protected public
#endif

#include "LG_Graph_Node.h"
#include "LG_Appearance.h"
#include "LG_Transform.h"
#include "LG_Sphere.h"
#include "LG_Torus.h"
#include <CGFapplication.h>


TEST_CASE("Test loading Graph Node from XML"){


    static bool called=false;
    
    
    if (!called) {//dont init various times
        
        CGFapplication app;
        
        int zero=1;
        const char * noParams[1]={"blabla"};
        app.init(&zero, (char **)noParams);
        
        called=true;
    }
    
    
    
    
    TiXmlDocument *doc=new TiXmlDocument("./testFiles/TestGraphNodes.xml");
    REQUIRE(doc->LoadFile());
    LG_Node_Map *map=new LG_Node_Map();
    
    LG_Node_Map *appMap=new LG_Node_Map();
    
    LG_LightArray_f amb,diff,spec;
    float s;
    string identifier="appID";
    LG_Appearance *app=new LG_Appearance(appMap, amb, diff, spec, s, identifier,NULL);
    
    TiXmlElement *firstElement=doc->FirstChildElement();
    TiXmlElement *secondElement=firstElement->NextSiblingElement();
    TiXmlElement *thirElement=secondElement->NextSiblingElement();
    TiXmlElement *fourthElement=thirElement->NextSiblingElement();
    TiXmlElement *fifthElement=fourthElement->NextSiblingElement();
    TiXmlElement *sixthElement=fifthElement->NextSiblingElement();
    TiXmlElement *seventhElement=sixthElement->NextSiblingElement();
    TiXmlElement *eightElement=seventhElement->NextSiblingElement();
    
    
    
    
    SECTION("Testing perfectly well formed Node"){
    
        
        try {
            LG_Graph_Node *node1=new LG_Graph_Node(map, appMap, firstElement);
            
            REQUIRE(node1->transform->matrix[0][0]==3);
            REQUIRE(node1->transform->matrix[1][1]==4);
            REQUIRE(node1->transform->matrix[2][2]==5);
            
            REQUIRE((dynamic_cast<LG_Sphere *>(node1->child(0))!=NULL));
            REQUIRE((dynamic_cast<LG_Torus *>(node1->child(1))!=NULL));
            
            REQUIRE(str_eq(node1->identifier.c_str(),"myID"));
        } catch (LG_Parse_Exception *ex) {
            FAIL("Thrown Exception while parsing perfectly fine Graph Node");
        }
        
        
        
        
        
    }
    
    SECTION("Testing node with reference to nonExisting appearance"){
    
    
        
        try {
            LG_Graph_Node *node=new LG_Graph_Node(map,appMap,secondElement);
            FAIL("Failed to find reference to nonExisting appearance");
        } catch (LG_Parse_Exception_Broken_Reference *ex) {
            
            REQUIRE(str_eq(ex->refered_Type->c_str(),"appearance"));
            REQUIRE(str_eq(ex->reference->c_str(),"blabla"));
            REQUIRE(str_eq(ex->element->c_str(), "node"));
            
        }
    }
    
    
    SECTION("Testing decendants"){
        
        
        try {
            
            LG_Graph_Node *child=new LG_Graph_Node(map, appMap, firstElement);
            LG_Graph_Node *node=new LG_Graph_Node(map,appMap,thirElement);
            
            REQUIRE(node->child(2)==child);
        } catch (LG_Parse_Exception *ex) {
            FAIL("Thrown exception while parsing perfectly well formed node");
        }
    
    
    }
    
    
    SECTION("Testing missing decendants block"){
    
    
        try {
            LG_Graph_Node *node=new LG_Graph_Node(map,appMap,fourthElement);
            REQUIRE(node->childsIDs.size()==2);//all the childs are the primitives
            REQUIRE(dynamic_cast<LG_Primitive *>(node->child(0)));
            REQUIRE(dynamic_cast<LG_Primitive *>(node->child(1)));
            
        } catch (LG_Parse_Exception_Missing_Element *ex) {
            FAIL("Didnt allow node witout descendants block");        }
    }
    
    
    
    SECTION("Testing setting oursef as our descendant"){
    
    
        try {
            LG_Graph_Node *node=new LG_Graph_Node(map,appMap,fifthElement);
            FAIL("Failed to notice redundant reference to ourselfs as our childs");
            
        } catch (LG_Parse_Exception_Redundant_Reference *ex) {
            REQUIRE(str_eq(ex->element->c_str(), "node1"));
        }
    }
    
    
    SECTION("Testing inherit appearance"){
        
        
        try {
            LG_Graph_Node *node=new LG_Graph_Node(map,appMap,sixthElement);
            REQUIRE(node->appearance==NULL);//should be set to null now cause of inherit
            
            REQUIRE(!node->isDisplayList);
            
        } catch (LG_Parse_Exception *ex) {
            FAIL("Thrown exception while parsing well formed node");
        }
    }
    
    
    SECTION("Texting displaylist parameter to true"){
    
        
        try {
            LG_Graph_Node *node=new LG_Graph_Node(map,appMap,seventhElement);
            REQUIRE(node->appearance==NULL);//should be set to null now cause of inherit
            REQUIRE(node->isDisplayList);
            
        } catch (LG_Parse_Exception *ex) {
            FAIL("Thrown exception while parsing well formed node");
        }
    
    }
    
    SECTION("Texting displaylist parameter to false"){
        
        
        try {
            LG_Graph_Node *node=new LG_Graph_Node(map,appMap,eightElement);
            REQUIRE(node->appearance==NULL);//should be set to null now cause of inherit
            REQUIRE(!node->isDisplayList);
            
        } catch (LG_Parse_Exception *ex) {
            FAIL("Thrown exception while parsing well formed node");
        }
        
    }
    
}
