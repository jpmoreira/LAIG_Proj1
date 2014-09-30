#ifndef LG_ALL_TESTS
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.h"
#define private public //disable encapsulation for following files, allowing testing to be done
#define protected public
#endif

#include "LG_Cylinder.h"
#include <tinyxml.h>



TEST_CASE("Testing Cylinder Parsing from XML file"){

    
    TiXmlDocument *doc=new TiXmlDocument("./testFiles/TestCylinder.xml");
    
    
    REQUIRE(doc->LoadFile());
    LG_Node_Map *map=new LG_Node_Map();
    
    TiXmlElement *firstElement=doc->FirstChildElement();
    TiXmlElement *secondElement=firstElement->NextSiblingElement();
    TiXmlElement *thirdElement=secondElement->NextSiblingElement();
    TiXmlElement *fourthElement=thirdElement->NextSiblingElement();

    
    SECTION("Test IDS"){
    
        LG_Cylinder *cyl=new LG_Cylinder(map,firstElement);
        LG_Cylinder *cyl2=new LG_Cylinder(map,firstElement);
        
        REQUIRE(str_eq(cyl->identifier.c_str(), "_LG_Cylinder_0"));
        REQUIRE(str_eq(cyl2->identifier.c_str(), "_LG_Cylinder_1"));
        
    
    }
    
    
    SECTION("Correctly formed Cylinder"){
    
    
        try {
            LG_Cylinder *cyl=new LG_Cylinder(map,firstElement);
        } catch (LG_Parse_Exception *ex) {
            FAIL("Exception thrown while parsing perfectly correct cylinder");
        }
        
    
    }
    
    
    SECTION("Incorrect cylinder with negative base radius"){
    
        try {
            LG_Cylinder *cyl=new LG_Cylinder(map,secondElement);
            FAIL("Shouldn't accept cylinder with negative radius");
        } catch (LG_Parse_Exception_Wrong_Attribute_Value *ex) {
            REQUIRE(str_eq(ex->attribute->c_str(), "base"));
        }
    
    }
    
    
    SECTION("Incorrect cylinder with zero slices"){
    
        try {
            LG_Cylinder *cyl=new LG_Cylinder(map,thirdElement);
            FAIL("Shouldn't accept cylinder with zero slices");
        } catch (LG_Parse_Exception_Wrong_Attribute_Value *ex) {
            REQUIRE(str_eq(ex->attribute->c_str(), "slices"));
        }
    
    }
    
    SECTION("Incorrect cylinder with missing top attribute"){
        
        try {
            LG_Cylinder *cyl=new LG_Cylinder(map,fourthElement);
            FAIL("Shouldn't accept cylinder with no top attribute");
        } catch (LG_Parse_Exception_Missing_Attribute *ex) {
            REQUIRE(str_eq(ex->missingAttribute->c_str(), "top"));
        }
        
    }



}