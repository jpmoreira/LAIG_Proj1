


#ifndef LG_ALL_TESTS
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.h"
#define private public //disable encapsulation for following files, allowing testing to be done
#define protected public
#endif


#include <CGFapplication.h>
#include "LG_Texture.h"

TEST_CASE("Testing texture parsing from XML"){
    
    
    static bool called=false;
    
    
    if (!called) {//dont init various times
        
        CGFapplication app;
        
        int zero=1;
        const char * noParams[1]={"blabla"};
        app.init(&zero, (char **)noParams);
        
        called=true;
    }
    
    
    
    LG_Node_Map map;
    
    TiXmlDocument *doc=new TiXmlDocument("testFiles/TestTextures.xml");
    REQUIRE(doc->LoadFile());
    
    
    TiXmlElement *firstElement=doc->FirstChildElement();
    TiXmlElement *secondElement=firstElement->NextSiblingElement();
    TiXmlElement *thirdElement=secondElement->NextSiblingElement();
    
    
    SECTION("Testing perfectly well formed texture"){
        
        
        try {
            LG_Texture *tx=new LG_Texture(&map,firstElement);
            REQUIRE(str_eq(tx->identifier.c_str(), "texture1"));
            REQUIRE(abs(tx->texlength_s-3.1)<=0.0001);
            REQUIRE(abs(tx->texlength_t-2.1)<=0.0001);
            REQUIRE(str_eq(tx->file.c_str(), "tex1.png"));
        } catch (LG_Parse_Exception *ex) {
            FAIL("Trown exception while parsing well formed texture");
        }
        
        
    }
    
    
    SECTION("Testing texture with missing file specification"){
    
    
        try {
            LG_Texture *tx=new LG_Texture(&map,secondElement);
            FAIL("Failed to notice missing file attribute");
        } catch (LG_Parse_Exception_Missing_Attribute *ex) {
            REQUIRE(str_eq(ex->missingAttribute->c_str(), "file"));
        }
        
        
    
    }
    
    SECTION("Testing texture with wrong element name"){
    
        try {
            LG_Texture *tx=new LG_Texture(&map,thirdElement);
            FAIL("Failed to notice typo in texture element name");
        } catch (LG_Parse_Exception_Wrong_Element_Name *ex) {
            REQUIRE(str_eq(ex->expectedElementName->c_str(), "texture"));
            REQUIRE(str_eq(ex->element->c_str(), "textue"));//notice typo
        }
    }
    
    

    
    
}
