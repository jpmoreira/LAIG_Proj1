#ifndef LG_ALL_TESTS
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.h"
#define private public //disable encapsulation for following files, allowing testing to be done
#define protected public
#endif


#include "LG_Graph.h"
#include "LG_Appearance.h"
#include <CGFapplication.h>

TEST_CASE("Testing Graphs parsing"){


    static bool called=false;
    
    
    if (!called) {//dont init various times
        
        CGFapplication app;
        
        int zero=1;
        const char * noParams[1]={"blabla"};
        app.init(&zero, (char **)noParams);
        
        called=true;
    }
    
    
    
    
    TiXmlDocument *doc=new TiXmlDocument("./testFiles/TestGraphs.xml");
    REQUIRE(doc->LoadFile());
    LG_Node_Map *map=new LG_Node_Map();
    
    
    LG_Node_Map *appMap=new LG_Node_Map();
    LG_LightArray amb,diff,spec;
    double s;
    string identifier="uniqueExistingApp";
    LG_Appearance *app=new LG_Appearance(appMap, amb, diff, spec, s, identifier);
    
    
    TiXmlElement *firstElement=doc->FirstChildElement();
    TiXmlElement *secondElement=firstElement->NextSiblingElement();
    TiXmlElement *thirdElement=secondElement->NextSiblingElement();
    TiXmlElement *fourthElement=thirdElement->NextSiblingElement();
    
    
    SECTION("Testing well formed graph with two nodes. One child of the other"){
    
        
        try {
            LG_Graph *g=new LG_Graph(appMap,firstElement);
            REQUIRE(g->root==g->mapForNodes->find("node2")->second);
            REQUIRE(g->mapForNodes->size()==5);//1 torus 2 transforms and 2 nodes
            REQUIRE(g->root->appearance==app);
            REQUIRE(str_eq(g->root->child(0)->identifier.c_str(),"node1"));//transformsare not childs
            REQUIRE(g->root->child(0)->childsIDs.size()==1);//node1 should have 1 child, his primitive
            REQUIRE(g->root->child(0)->child(0)->childsIDs.size()==0);//primitive should have no child
            
        } catch (LG_Parse_Exception *ex) {
            FAIL("Failed to parce correctly working graph");
        }
        
    
    }
    
    
    
    SECTION("Testing graph with broken root reference"){
    
        try {
            LG_Graph *g=new LG_Graph(appMap,secondElement);
            FAIL("Failed to detect broken root reference");
        } catch (LG_Parse_Exception_Broken_Reference *ex) {
            
            REQUIRE(str_eq(ex->reference->c_str(),"node27"));
            REQUIRE(str_eq(ex->refered_Type->c_str(),"node"));
            REQUIRE(str_eq(ex->element->c_str(),"graph"));
            
        }
    
    }
    
    SECTION("Testing graph with more complex structure"){
    
    
        try {
            LG_Graph *g=new LG_Graph(appMap,thirdElement);
            
            
            LG_Node *node1=g->mapForNodes->find("node1")->second;
            LG_Node *node2=g->mapForNodes->find("node2")->second;
            LG_Node *node3=g->mapForNodes->find("node3")->second;
            
            
            REQUIRE(g->root==node2);//node2 is root
            REQUIRE(node1->childsIDs.size()==1);//one primitive child
            REQUIRE(node2->childsIDs.size()==2);//two child nodes, no primitives
            REQUIRE(node2->child(0)==node1);//node1 is first child
            REQUIRE(node2->child(1)==node3);//node3 is second and last child
            REQUIRE(node3->childsIDs.size()==1);//only one child for node3 (node1)
            REQUIRE(node3->child(0)==node1);
            
        } catch (LG_Parse_Exception *ex) {
            FAIL("Failed parsing well formed graph");
            
        }
        
    }
    
    
    SECTION("Testing graph with more complex structure"){
        
        
        try {
            LG_Graph *g=new LG_Graph(appMap,fourthElement);
            
            
            FAIL("Failed to detect broken child reference in node3");
        } catch (LG_Parse_Exception_Broken_Reference *ex) {
            REQUIRE(str_eq(ex->reference->c_str(), "node27"));
            REQUIRE(str_eq(ex->element->c_str(),"node3"));
            REQUIRE(str_eq(ex->refered_Type->c_str(), "node"));
            
        }
        
    }
    
    
}
