#ifndef LG_ALL_TESTS
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.h"
#define private public //disable encapsulation for following files, allowing testing to be done
#define protected public
#endif

#include "LG_Transform.h"
#include <CGFapplication.h>



TEST_CASE("Testing Transforms"){


    static bool called=false;
    
    
    if (!called) {//dont init various times
        
        CGFapplication app;
        
        int zero=1;
        const char * noParams[1]={"blabla"};
        app.init(&zero, (char **)noParams);

        called=true;
    }
    
    
    
    
    TiXmlDocument *doc=new TiXmlDocument("./testFiles/TestTransforms.xml");
    REQUIRE(doc->LoadFile());
    LG_Node_Map *map=new LG_Node_Map();
    
    TiXmlElement *firstElement=doc->FirstChildElement();
    TiXmlElement *secondElement=firstElement->NextSiblingElement();
    TiXmlElement *thirdElement=secondElement->NextSiblingElement();
    TiXmlElement *fourthElement=thirdElement->NextSiblingElement();

    
    SECTION("Test Transform with no transforms"){
    
    
        try {
            LG_Transform * t=new LG_Transform(map,firstElement);

            for (int i=0;i<LG_Matrix_Dimention; i++) {
                for (int f=0; f<LG_Matrix_Dimention; f++) {
                    if (i==f) {
                        REQUIRE(abs(t->matrix[i][f]-1)<=0.0001);//require diagonal as 1
                    }
                    else REQUIRE(abs(t->matrix[i][f]-0)<=0.0001);
                }
            }

        } catch (LG_Parse_Exception *ex) {
            
            FAIL("Thrown exception while parsing perfectly well formed transform block");
        }
    }
    
    
    SECTION("Test Transform with one Translation"){
        
        
        try {
            LG_Transform * t=new LG_Transform(map,secondElement);
            
            for (int i=0;i<LG_Matrix_Dimention; i++) {
                for (int f=0; f<LG_Matrix_Dimention; f++) {
                    if (i==f) {
                        REQUIRE(abs(t->matrix[i][f]-1)<=0.0001);//require diagonal as 1
                    }
                    else if(i==3 && f==0)REQUIRE(abs(t->matrix[i][f]-50)<=0.0001);
                    else REQUIRE(abs(t->matrix[i][f]-0)<=0.0001);
                }
            }
            
        } catch (LG_Parse_Exception *ex) {
            
            FAIL("Thrown exception while parsing perfectly well formed transform block");
        }
    }
    
    
    SECTION("Test Transform with invalid scaling"){
        
        
        try {
            LG_Transform * t=new LG_Transform(map,thirdElement);
            
            FAIL("Didnt throw exception while parsing translation block with invalid scale translation in it");
        } catch (LG_Parse_Exception_Missing_Attribute *ex) {
            
            REQUIRE(str_eq(ex->missingAttribute->c_str(), "factor"));
        }
    }
    
    
    SECTION("Test Transform with valid Scaling followed by a translation"){
        
        
        try {
            LG_Transform * t=new LG_Transform(map,fourthElement);
            
            for (int i=0;i<LG_Matrix_Dimention; i++) {
                for (int f=0; f<LG_Matrix_Dimention; f++) {
                    if (i==f && f==0) {
                        REQUIRE(abs(t->matrix[i][f]-50)<=0.0001);//require diagonal as 1
                    }
                    else if (i==f && f==1) {
                        REQUIRE(abs(t->matrix[i][f]-30)<=0.0001);//require diagonal as 1
                    }
                    else if (i==f && f==2) {
                        REQUIRE(abs(t->matrix[i][f]-40)<=0.0001);//require diagonal as 1
                    }
                    else if (i==f) {
                        REQUIRE(abs(t->matrix[i][f]-1)<=0.0001);//require diagonal as 1
                    }
                    else if(i==3 && f==0) REQUIRE(abs(t->matrix[i][f]-3)<=0.0001);
                    else REQUIRE(abs(t->matrix[i][f]-0)<=0.0001);
                }
            }

        } catch (LG_Parse_Exception_Missing_Attribute *ex) {
            
            FAIL("Thrown exception while parsing perfectly working transformation");
        }
    }
    


    
    
    
}


