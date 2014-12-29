//
//  LG_Board_Place_Test.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 26/12/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//


#ifndef LG_ALL_TESTS
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.h"
#define private public //disable encapsulation for following files, allowing testing to be done
#define protected public
#endif


#include <CGFapplication.h>
#include "LG_Board_Place.h"

TEST_CASE("Testing Board Places"){
    
    
    static bool called=false;
    
    
    if (!called) {//dont init various times
        
        CGFapplication app;
        
        int zero=1;
        const char * noParams[1]={"blabla"};
        app.init(&zero, (char **)noParams);
        
        called=true;
    }
    
    LG_Node_Map map,text_map,app_map;
    
    
    TiXmlDocument *doc=new TiXmlDocument("TestPlace.xml");
    REQUIRE(doc->LoadFile());
    
    TiXmlElement *firstElement=doc->FirstChildElement();
    TiXmlElement *secondElement=firstElement->NextSiblingElement();
    TiXmlElement *thirdElement=secondElement->NextSiblingElement();
    TiXmlElement *fourthElement=thirdElement->NextSiblingElement();
    
    
    
    SECTION("Parsing well formed place for x=1 y=1"){
        
        
        
        try {
            LG_Board_Place *place1=new LG_Board_Place(&map, &app_map, &text_map, firstElement);
            LG_Board_Place *place2=new LG_Board_Place(&map,&app_map,&text_map,secondElement);
            
            REQUIRE(place1!=NULL);
            
            LG_Board_Piece *piece1=place1->piece;
            LG_Board_Piece *piece2=place2->piece;
            
            REQUIRE(piece1!=NULL);
            REQUIRE(piece2!=NULL);
            
            REQUIRE(piece1==piece2);//the object should actually be the same
            
            REQUIRE(piece1->getType()==Tzarra);
            
            REQUIRE(place1->nrPieces==1);
            REQUIRE(place2->nrPieces==3);
            
            place1->stackFrom(place2);
            
            REQUIRE(place1->nrPieces==4);
            REQUIRE(place2->nrPieces==0);
            REQUIRE(place2->piece==NULL);
            
            
            
            
            
        } catch (LG_Parse_Exception * ex) {
            FAIL("Thrown exception while parsing well formed board place with 1 tzarra in it");
        }
        
        
    }
    
    SECTION("Element with no piece"){
        
        try {
            LG_Board_Place *place=new LG_Board_Place(&map,&app_map,&text_map,thirdElement);
            
            REQUIRE(place!=NULL);
            REQUIRE(place->piece==NULL);
            REQUIRE(place->nrPieces==0);
            
        } catch (LG_Parse_Exception *ex) {
            FAIL("Thrown exception while parsing well formed board place");
        }
        
        
    }
    
    SECTION("Parsing bad formed board place"){
    
        try {
            
            LG_Board_Place *place=new LG_Board_Place(&map,&app_map,&text_map,fourthElement);
            FAIL("Failed to detect name typo in place xml tag name");

        } catch (LG_Parse_Exception_Wrong_Element_Name *ex) {
            REQUIRE(str_eq(ex->element, "placze"));
        }
    
    }
    
    
}

