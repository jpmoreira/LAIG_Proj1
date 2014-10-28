

#ifndef LG_ALL_TESTS
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.h"
#define private public //disable encapsulation for following files, allowing testing to be done
#define protected public
#endif


#include <CGFapplication.h>
#include "LG_Plane.h"
#include "LG_Graph_Node.h"
#include "LG_Torus.h"

TEST_CASE("Test Planes stuff"){
    
    
    static bool called=false;
    
    
    if (!called) {//dont init various times
        
        CGFapplication app;
        
        int zero=1;
        const char * noParams[1]={"blabla"};
        app.init(&zero, (char **)noParams);
        
        called=true;
    }
    
    
    
    
    TiXmlDocument *doc=new TiXmlDocument("./testFiles/TestPlane.xml");
    REQUIRE(doc->LoadFile());
    
    
    TiXmlElement *firstElement=doc->FirstChildElement();
    TiXmlElement *secondElement=firstElement->NextSiblingElement();
    TiXmlElement *thirdElement=secondElement->NextSiblingElement();
    TiXmlElement *fourthElement=thirdElement->NextSiblingElement();
    
    
    SECTION("Test simple plane"){
        
        try {
            LG_Plane *plane=new LG_Plane(NULL,firstElement);
            REQUIRE(plane->parts==20);
        } catch (LG_Parse_Exception *ex) {
            FAIL("Thrown exeception while parsing perfectly fine plane element.");
        }
        
    }
    
    SECTION("Plane with typo at parts attribute"){
    
        try {
            LG_Plane *plane=new LG_Plane(NULL,secondElement);
            FAIL("Failed to notice typo in parts attribute while parsing plane element");
        } catch (LG_Parse_Exception_Missing_Attribute *ex) {
            REQUIRE(str_eq(ex->missingAttribute->c_str(),"parts"));
            REQUIRE(str_eq(ex->element->c_str(), "plane"));
        }

    
    }
    
    SECTION("Plane with string in parts attribute instead of integer"){
    
        try {
            LG_Plane *plane=new LG_Plane(NULL,thirdElement);
            FAIL("Failed to notice invalid string in parts attribute value");
        } catch (LG_Parse_Exception_Wrong_Attribute_Value *ex) {
            REQUIRE(str_eq(ex->actualValue,"xpto"));
            REQUIRE(str_eq(ex->element, "plane"));
        }
    
    }
    
    
    SECTION("Parsing of node with plane inside"){
    
    
        try {
            LG_Graph_Node *node=new LG_Graph_Node(new LG_Node_Map(),NULL,fourthElement);
            REQUIRE(node->childsIDs.size()==2);
            REQUIRE(dynamic_cast<LG_Plane *>(node->child(0)));//first child should be plane
            REQUIRE(dynamic_cast<LG_Torus *>(node->child(1)));//second child should be a torus
            
            LG_Plane *plane=(LG_Plane *)node->child(0);
            
            REQUIRE(plane->parts==10);
        } catch (LG_Parse_Exception *ex) {
            FAIL("Thrown exception while parsing well formed node");
        }
        
        
    }
    
    
    

    
    
}

