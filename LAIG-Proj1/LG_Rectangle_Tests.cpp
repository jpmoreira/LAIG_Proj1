#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.h"
#define private public //disable encapsulation for following files, allowing testing to be done
#define protected public
#include "LG_Rectangle.h"
#include <tinyxml.h>



TEST_CASE("Testing parsing from XML"){

    TiXmlDocument *doc=new TiXmlDocument("./testFiles/TestRectangle.xml");
    
    
    REQUIRE(doc->LoadFile());
    LG_Node_Map *map=new LG_Node_Map();
    
    TiXmlElement *firstElement=doc->FirstChildElement();
    TiXmlElement *secondElement=firstElement->NextSiblingElement();
    TiXmlElement *thirdElement=secondElement->NextSiblingElement();
    TiXmlElement *fourthElement=thirdElement->NextSiblingElement();
    
    
    SECTION("Testing Rectangle IDS"){
    
        LG_Rectangle *rect=new LG_Rectangle(map,firstElement);
        LG_Rectangle *rect2=new LG_Rectangle(map,firstElement);
        
        REQUIRE(str_eq(rect->identifier.c_str(), "_LG_Rectangle_0"));
        REQUIRE(str_eq(rect2->identifier.c_str(), "_LG_Rectangle_1"));
    
    }

    SECTION("Testing correct element"){
    
        
        try {
            LG_Rectangle *rect=new LG_Rectangle(map,firstElement);
            
            LG_Point3D pt1;
            pt1[0]=23;
            pt1[1]=50;
            pt1[2]=0.0;
            LG_Point3D pt2;
            pt2[0]=60;
            pt2[1]=24.5;
            pt2[2]=0.0;
            
            REQUIRE(LG_Primitive::equalPoints(pt1, rect->pt1));
            REQUIRE(LG_Primitive::equalPoints(pt2, rect->pt2));
        
        
        } catch (LG_Parse_Exception *ex) {
            FAIL("Exception Thrown when parsing correctly formed rectangle");
        }
    
    
    }
    
    
    SECTION("Testing rectangle with 2d point as a 3d point "){
    
        try {
            LG_Rectangle *rect=new LG_Rectangle(map,secondElement);
            FAIL("Didn't throw exception for 3D point instead of 2D but should have done so!");
        } catch (LG_Parse_Exception_Missing_Attribute *ex) {
            REQUIRE(str_eq(ex->missingAttribute->c_str(), "xy2"));
        }
        
      
        
    
    }
    
    
    SECTION("Testing rectangle with typo in element name"){
        
        
        try {
            LG_Rectangle *rect=new LG_Rectangle(map,thirdElement);
            
            FAIL("Should have thrown exception for wrong rectangle tag name");
            
        } catch (LG_Parse_Exception_Wrong_Element_Name *ex) {
            
            REQUIRE(str_eq(ex->expectedElementName->c_str(), "rectangle"));
            REQUIRE(str_eq(ex->element->c_str(), "rectagle"));
        }
        
    }
    
    
    SECTION("Testing Rectangle with missing attribute"){
    
    
        try {
            LG_Rectangle *rect=new LG_Rectangle(map,fourthElement);
            FAIL("Should have thrown exception for missing parameter in rectangle element");
        } catch (LG_Parse_Exception_Missing_Attribute *ex) {
            REQUIRE(str_eq(ex->missingAttribute->c_str(), "xy1"));
        }
    
    }
    

    
    

    
    
    


}
