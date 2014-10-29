//
//  LG_Animation_Tests.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 28/10/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include <stdio.h>


#ifndef LG_ALL_TESTS
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.h"
#define private public //disable encapsulation for following files, allowing testing to be done
#define protected public
#endif


#include <CGFapplication.h>
#include "LG_LinearAnimation.h"

TEST_CASE("Basic Animation Tests"){
    
    
    static bool called=false;
    
    
    if (!called) {//dont init various times
        
        CGFapplication app;
        
        int zero=1;
        const char * noParams[1]={"blabla"};
        app.init(&zero, (char **)noParams);
        
        called=true;
    }
    
    
    
    
    TiXmlDocument *doc=new TiXmlDocument("./testFiles/TestAnimations.xml");
    REQUIRE(doc->LoadFile());
    LG_Node_Map map;
    
    TiXmlElement *firstElement=doc->FirstChildElement();
    TiXmlElement *secondElement=firstElement->NextSiblingElement();
    TiXmlElement *thirdElement=secondElement->NextSiblingElement();
    
    
    
    SECTION("Well Formed Animation"){
        
        try {
            LG_Animation *anim=LG_Animation::animationForElement(&map, firstElement);
            
            REQUIRE(str_eq(anim->identifier, "theID"));
            REQUIRE(dynamic_cast<LG_LinearAnimation *>(anim));
            REQUIRE(fabs(anim->span-2.5)<=0.0001);
        } catch (LG_Parse_Exception *ex) {
            FAIL("Thrown exception while parsing well formed linear animation");
        }
        
    }
    
    SECTION("Bad Formed Animation, missing id"){
    
        try {
            LG_Animation *anim=LG_Animation::animationForElement(&map, secondElement);
            FAIL("Failed to detect missing id field in LG_Animation");
        } catch (LG_Parse_Exception_Missing_Attribute *ex) {
            REQUIRE(str_eq("animation", ex->element));
            REQUIRE(str_eq(ex->missingAttribute, "id"));
        }
    
    }
    
    SECTION("Animation with unknown type"){
    
        try {
            LG_Animation *anim=LG_Animation::animationForElement(&map, thirdElement);
            FAIL("Failed to notice invalid animation type");
        } catch (LG_Parse_Exception_Wrong_Attribute_Value *ex) {
            REQUIRE(str_eq(ex->element, "animation"));
            REQUIRE(str_eq(ex->actualValue, "inexistentType"));
            REQUIRE(ex->expectedValues->size()==2);
            REQUIRE(str_eq(ex->expectedValues->at(0), "linear"));
            REQUIRE(str_eq(ex->expectedValues->at(1), "circular"));
            
        }
    
    }
    
    
}



TEST_CASE("Linear Animation Tests"){
    
    
    static bool called=false;
    
    
    if (!called) {//dont init various times
        
        CGFapplication app;
        
        int zero=1;
        const char * noParams[1]={"blabla"};
        app.init(&zero, (char **)noParams);
        
        called=true;
    }
    
    
    
    
    TiXmlDocument *doc=new TiXmlDocument("./testFiles/TestAnimations.xml");
    REQUIRE(doc->LoadFile());
    LG_Node_Map map;
    
    TiXmlElement *linear1=doc->FirstChildElement();
    TiXmlElement *linear2=linear1->NextSiblingElement()->NextSiblingElement()->NextSiblingElement();
    
    
    
    SECTION("Well Formed Linear Animation with 2 control points"){
        
        try {
            LG_LinearAnimation *anim=dynamic_cast<LG_LinearAnimation *>( LG_Animation::animationForElement(&map, linear1));
            
            REQUIRE(anim->controlPoints.size()==2);
            double *pt0=anim->controlPoints[0];
            double *pt1=anim->controlPoints[1];
            
            REQUIRE(fabs(pt0[0]-1)<=0.0001);
            REQUIRE(fabs(pt0[1]-3.5)<=0.0001);
            REQUIRE(fabs(pt0[2]-4.5)<=0.0001);
            
            REQUIRE(fabs(pt1[0]-5.5)<=0.0001);
            REQUIRE(fabs(pt1[1]-0.5)<=0.0001);
            REQUIRE(fabs(pt1[2]-0.45)<=0.0001);
            
            
            } catch (LG_Parse_Exception *ex) {
            FAIL("Thrown exception while parsing well formed linear animation");
        }
        
    }
    
    SECTION("Bad Formed Animation, missing id"){
        
        
        try{
            
            LG_LinearAnimation *anim=dynamic_cast<LG_LinearAnimation *>( LG_Animation::animationForElement(&map, linear2));
            FAIL("Failed to notice invalid number of control points (1!)");
        
        }catch(LG_Parse_Exception_Missing_Element *ex){
            
            REQUIRE(str_eq(ex->element,"controlpoint"));
        
        }
        
        
    }
    
    
}

