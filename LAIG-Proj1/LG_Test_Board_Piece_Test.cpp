
#ifndef LG_ALL_TESTS
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.h"
#define private public //disable encapsulation for following files, allowing testing to be done
#define protected public
#endif


#include <CGFapplication.h>
#include "LG_Board_Piece.h"

TEST_CASE("Test Board Piece Loading"){
    
    
    static bool called=false;
    
    
    if (!called) {//dont init various times
        
        CGFapplication app;
        
        int zero=1;
        const char * noParams[1]={"blabla"};
        app.init(&zero, (char **)noParams);
        
        called=true;
    }
    
    
    
    
    TiXmlDocument *doc=new TiXmlDocument("TestPieceLoad1.xml");
    REQUIRE(doc->LoadFile());
    
    
    TiXmlElement *firstElement=doc->FirstChildElement();
    TiXmlElement *secondElement=firstElement->NextSiblingElement();
    TiXmlElement *thirdElement=secondElement->NextSiblingElement();
    TiXmlElement *fourthElement=thirdElement->NextSiblingElement();
    TiXmlElement *fifthElement=fourthElement->NextSiblingElement();
    TiXmlElement *sixthElement=fifthElement->NextSiblingElement();
    TiXmlElement *seventhElement=sixthElement->NextSiblingElement();
    
    TiXmlElement *eightElement=seventhElement->NextSiblingElement();
    
    
    LG_Node_Map map;
    LG_Node_Map appMap;
    LG_Node_Map textureMap;
    
    
    
    SECTION("Missing colour attribute"){
    
        
        try {
            
            LG_Board_Piece::pieceForElement(&map, &appMap, &textureMap, firstElement);
            
        } catch (LG_Parse_Exception_Missing_Attribute *ex) {
            
            REQUIRE(str_eq(ex->missingAttribute, "color"));
            
        }
        
    }
    
    SECTION("Loading White Tzarra"){
        
        
        try {
            
            REQUIRE(map.size()==0);
            LG_Board_Piece *p=LG_Board_Piece::pieceForElement(&map, &appMap, &textureMap, secondElement);
            
            REQUIRE(p!=NULL);
            REQUIRE(p->childsIDs.size()==1);
            
            
            LG_Node *root=p->child(0);
            REQUIRE(str_eq(root->identifier, "white_tzarra"));
            REQUIRE(root->childsIDs.size()==2);
            LG_Node *base=root->child(0);
            LG_Node *top=root->child(1);
            REQUIRE(str_eq(base->identifier,"white_base_white_tzarra"));
            REQUIRE(str_eq(top->identifier,"white_tzarra_top"));
            REQUIRE(appMap.size()==1);
            REQUIRE(textureMap.size()==1);
            REQUIRE(map.size()==9);//two cylinders + 3 transforms + piece itself + root + base + top
            
            
        } catch (LG_Parse_Exception *ex) {
            
            FAIL("Thrown exception while parsing perfectly well formed taar piece");
            
            
        }
        
        
    }
    
    SECTION("Loading white Tott"){
        
        
        
        try {
            LG_Board_Piece *p=LG_Board_Piece::pieceForElement(&map, &appMap, &textureMap, thirdElement);
            REQUIRE(p!=NULL);
            
            REQUIRE(p->childsIDs.size()==1);
            
            
            LG_Node *root=p->child(0);
            REQUIRE(str_eq(root->identifier, "white_tott"));
            REQUIRE(root->childsIDs.size()==2);
            LG_Node *base=root->child(0);
            LG_Node *top=root->child(1);
            REQUIRE(str_eq(base->identifier,"white_base_white_tott"));
            REQUIRE(str_eq(top->identifier,"white_tott_top"));
            REQUIRE(appMap.size()==1);
            REQUIRE(textureMap.size()==1);
            REQUIRE(map.size()==9);//two cylinders + 3 transforms + piece itself + root + base + top
            

            
            
        } catch (LG_Parse_Exception *ex) {
            
            FAIL("Thrown exception while parsing perfectly well formed Tott");
        }

        
    }
    
    
    SECTION("Loading white Tzaar"){
        
        
        
        try {
            LG_Board_Piece *p=LG_Board_Piece::pieceForElement(&map, &appMap, &textureMap, fourthElement);
            REQUIRE(p!=NULL);
            
            REQUIRE(p->childsIDs.size()==1);
            
            
            LG_Node *root=p->child(0);
            REQUIRE(str_eq(root->identifier, "white_tzaar"));
            REQUIRE(root->childsIDs.size()==2);
            LG_Node *base=root->child(0);
            LG_Node *top=root->child(1);
            REQUIRE(str_eq(base->identifier,"white_base_white_tzaar"));
            REQUIRE(str_eq(top->identifier,"white_tzaar_top"));
            REQUIRE(appMap.size()==1);
            REQUIRE(textureMap.size()==1);
            REQUIRE(map.size()==9);//two cylinders + 3 transforms + piece itself + root + base + top
            
            
            
            
        } catch (LG_Parse_Exception *ex) {
            
            FAIL("Thrown exception while parsing perfectly well formed Tzaar");
        }
        
        
    }
    
    
    
    
    SECTION("Loading black Tzarra"){
        
        
        
        try {
            LG_Board_Piece *p=LG_Board_Piece::pieceForElement(&map, &appMap, &textureMap, fifthElement);
            REQUIRE(p!=NULL);
            
            REQUIRE(p->childsIDs.size()==1);
            
            
            LG_Node *root=p->child(0);
            REQUIRE(str_eq(root->identifier, "black_tzarra"));
            REQUIRE(root->childsIDs.size()==2);
            LG_Node *base=root->child(0);
            LG_Node *top=root->child(1);
            REQUIRE(str_eq(base->identifier,"black_base_black_tzarra"));
            REQUIRE(str_eq(top->identifier,"black_tzarra_top"));
            REQUIRE(appMap.size()==1);
            REQUIRE(textureMap.size()==1);
            REQUIRE(map.size()==9);//two cylinders + 3 transforms + piece itself + root + base + top
            
            
            
            
        } catch (LG_Parse_Exception *ex) {
            
            FAIL("Thrown exception while parsing perfectly well formed black Tzarra");
        }
        
        
    }
    
    
    SECTION("Loading black Tzaar"){
        
        
        
        try {
            LG_Board_Piece *p=LG_Board_Piece::pieceForElement(&map, &appMap, &textureMap, sixthElement);
            REQUIRE(p!=NULL);
            
            REQUIRE(p->childsIDs.size()==1);
            
            
            LG_Node *root=p->child(0);
            REQUIRE(str_eq(root->identifier, "black_tzaar"));
            REQUIRE(root->childsIDs.size()==2);
            LG_Node *base=root->child(0);
            LG_Node *top=root->child(1);
            REQUIRE(str_eq(base->identifier,"black_base_black_tzaar"));
            REQUIRE(str_eq(top->identifier,"black_tzaar_top"));
            REQUIRE(appMap.size()==1);
            REQUIRE(textureMap.size()==1);
            REQUIRE(map.size()==9);//two cylinders + 3 transforms + piece itself + root + base + top
            
            
            
            
        } catch (LG_Parse_Exception *ex) {
            
            FAIL("Thrown exception while parsing perfectly well formed black Tzaar");
        }
        
        
    }
    
    SECTION("Loading black Tott"){
        
        
        
        try {
            LG_Board_Piece *p=LG_Board_Piece::pieceForElement(&map, &appMap, &textureMap, seventhElement);
            REQUIRE(p!=NULL);
            
            REQUIRE(p->childsIDs.size()==1);
            
            
            LG_Node *root=p->child(0);
            REQUIRE(str_eq(root->identifier, "black_tott"));
            REQUIRE(root->childsIDs.size()==2);
            LG_Node *base=root->child(0);
            LG_Node *top=root->child(1);
            REQUIRE(str_eq(base->identifier,"black_base_black_tott"));
            REQUIRE(str_eq(top->identifier,"black_tott_top"));
            REQUIRE(appMap.size()==1);
            REQUIRE(textureMap.size()==1);
            REQUIRE(map.size()==9);//two cylinders + 3 transforms + piece itself + root + base + top
            
            
            
            
        } catch (LG_Parse_Exception *ex) {
            
            FAIL("Thrown exception while parsing perfectly well formed black Tott");
        }
        
        
    }

    
    
}
