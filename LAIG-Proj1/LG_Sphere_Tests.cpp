#ifndef LG_ALL_TESTS
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.h"
#define private public //disable encapsulation for following files, allowing testing to be done
#define protected public
#endif

#include "LG_Sphere.h"
#include <tinyxml.h>



TEST_CASE("Testing Cylinder Parsing from XML file"){
    
    
    TiXmlDocument *doc=new TiXmlDocument("./testFiles/TestSphere.xml");
    
    
    REQUIRE(doc->LoadFile());
    LG_Node_Map *map=new LG_Node_Map();
    
    TiXmlElement *firstElement=doc->FirstChildElement();
    TiXmlElement *secondElement=firstElement->NextSiblingElement();
    TiXmlElement *thirdElement=secondElement->NextSiblingElement();
    TiXmlElement *fourthElement=thirdElement->NextSiblingElement();
    
    
    SECTION("TEST Correct sphere"){
    
        try {
            LG_Sphere *sphere=new LG_Sphere(map,firstElement);
            
            REQUIRE(sphere->stacks==20);
            REQUIRE(sphere->slices==10);
            REQUIRE(abs(sphere->radius-30.f)<=0.00001);
        } catch (LG_Parse_Exception *ex) {
            FAIL("Thrown exception while parsing correct Sphere");
        }
        
        
    
    }
    
    
    SECTION("Test Sphere with negative stack number"){
    
        try {
            LG_Sphere *sphere=new LG_Sphere(map,secondElement);
            FAIL("Accepted Sphere with negative number of stacks");
        } catch (LG_Parse_Exception_Missing_Attribute *ex) {
         
            REQUIRE(str_eq(ex->missingAttribute->c_str(), "stacks"));
        }

    
    }

}