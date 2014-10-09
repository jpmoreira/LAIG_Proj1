#ifndef LG_ALL_TESTS
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.h"
#define private public //disable encapsulation for following files, allowing testing to be done
#define protected public
#endif

#include "LG_Appearance.h"
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
    
    
    
    
    TiXmlDocument *doc=new TiXmlDocument("./testFiles/TestAppearances.xml");
    REQUIRE(doc->LoadFile());
    LG_Node_Map *map=new LG_Node_Map();
    
    

    LG_Node_Map *textureMap=new LG_Node_Map();
    
    LG_Texture *text=new LG_Texture(textureMap, "someFile.txt", 10, 20, "stuff");
    
    
    
    TiXmlElement *firstElement=doc->FirstChildElement();
    TiXmlElement *secondElement=firstElement->NextSiblingElement();
    TiXmlElement *thirdElement=secondElement->NextSiblingElement();
    TiXmlElement *fourthElement=thirdElement->NextSiblingElement();
    
    
    
    SECTION("Testing perfectly well formed Appearance"){
        
        
        try {
            LG_Appearance *app=new LG_Appearance(map,firstElement,textureMap);
            REQUIRE(str_eq(app->identifier.c_str(), "appear1"));
            REQUIRE(abs(app->shininess-0.8)<=0.0001);
            REQUIRE(abs(app->ambient[0]-0.7)<=0.0001);
            REQUIRE(abs(app->ambient[1]-0.75)<=0.0001);
            REQUIRE(abs(app->ambient[2]-0.7)<=0.0001);
            REQUIRE(abs(app->ambient[3]-0.9)<=0.0001);
            
            REQUIRE(abs(app->diffuse[0]-0.9)<=0.0001);
            REQUIRE(abs(app->diffuse[1]-0.7)<=0.0001);
            REQUIRE(abs(app->diffuse[2]-0.7)<=0.0001);
            REQUIRE(abs(app->diffuse[3]-0.9)<=0.0001);
            
            REQUIRE(abs(app->specular[0]-0.6)<=0.0001);
            REQUIRE(abs(app->specular[1]-0.7)<=0.0001);
            REQUIRE(abs(app->specular[2]-0.7)<=0.0001);
            REQUIRE(abs(app->specular[3]-0.55)<=0.0001);
            
            
        } catch (LG_Parse_Exception *ex) {
            FAIL("Thrown exception while parsing perfectly good appearance");
        }
        
        
    }
    
    
    SECTION("Testing appearance with no ambient component"){
        
        
        try {
            LG_Appearance *app=new LG_Appearance(map,secondElement,textureMap);
            
            REQUIRE(app->ambient[0]==LG_INVALID_DOUBLE);
            REQUIRE(app->ambient[1]==LG_INVALID_DOUBLE);
            REQUIRE(app->ambient[2]==LG_INVALID_DOUBLE);
            REQUIRE(app->ambient[3]==LG_INVALID_DOUBLE);

        } catch (LG_Parse_Exception *ex) {
            FAIL("Thrown exception while parsing exception that is only missing an optional ambient component");
        }
        
    
    
    }
    
    
    SECTION("Testing appearance with missing id"){
    
        try {
            LG_Appearance *app=new LG_Appearance(map,thirdElement,textureMap);
            FAIL("Accepted appearance with missing ID attribute");
        } catch (LG_Parse_Exception_Missing_Attribute *ex) {
            REQUIRE(str_eq(ex->missingAttribute->c_str(), "id"));
        }
    
    }
    
    SECTION("Testing appearance with non existing texture reference"){
    
    
        try {
            LG_Appearance *app=new LG_Appearance(map,fourthElement,textureMap);
            FAIL("Failed to notice broken reference to a nonexisting texture");
        } catch (LG_Parse_Exception_Broken_Reference *ex) {
            REQUIRE(str_eq(ex->reference->c_str(), "stuff2"));
            REQUIRE(str_eq(ex->refered_Type->c_str(), "texture"));
            REQUIRE(str_eq(ex->element->c_str(), "appearXPTO"));
        }
    }
    
    
}
