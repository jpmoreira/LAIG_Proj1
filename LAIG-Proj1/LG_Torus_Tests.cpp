#ifndef LG_ALL_TESTS
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.h"
#define private public //disable encapsulation for following files, allowing testing to be done
#define protected public
#endif

#include "LG_Torus.h"
#include <tinyxml.h>



TEST_CASE("Test Torus Parsing"){


    TiXmlDocument *doc=new TiXmlDocument("./testFiles/TestTorus.xml");
    
    
    REQUIRE(doc->LoadFile());
    LG_Node_Map *map=new LG_Node_Map();
    
    TiXmlElement *firstElement=doc->FirstChildElement();
    TiXmlElement *secondElement=firstElement->NextSiblingElement();
    TiXmlElement *thirdElement=secondElement->NextSiblingElement();
    TiXmlElement *fourthElement=thirdElement->NextSiblingElement();


    
    
    SECTION("Test perfectly well formed Torus"){
    
        
        try {
            LG_Torus * to=new LG_Torus(map,firstElement);
            
            REQUIRE((to->innerRadius-30.0)<=0.0001);
            REQUIRE((to->outerRadius-40.0)<=0.0001);
            REQUIRE(to->slices==3);
            REQUIRE(to->loops==4);
        } catch (LG_Parse_Exception *ex) {
            FAIL("Thrown exception while parsing correct Torus");
        }
        
    
    
    }
    
    
    SECTION("Test node with wrong slices value"){
    
        
        
        try {
            LG_Torus * to=new LG_Torus(map,secondElement);
            FAIL("Accepted Torus with wrong slices value");
        } catch (LG_Parse_Exception_Wrong_Attribute_Value *ex) {
           REQUIRE(str_eq(ex->attribute->c_str(),"slices"));
        }
    
    }
    
    SECTION("Test node with missing loops value"){
        
        
        
        try {
            LG_Torus * to=new LG_Torus(map,thirdElement);
            FAIL("Accepted Torus with missing loops value");
        } catch (LG_Parse_Exception_Missing_Attribute *ex) {
            REQUIRE(str_eq(ex->missingAttribute->c_str(),"loops"));
        }
        
    }

}
