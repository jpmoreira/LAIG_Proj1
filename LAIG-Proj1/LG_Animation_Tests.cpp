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
#include "LG_Animations_Container.h"
#include "LG_LinearAnimation.h"

TEST_CASE("Basic Animation Parsing Tests"){
    
    
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
            REQUIRE(fabs(anim->span-2500)<=0.0001);
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



TEST_CASE("Linear Animation Parsing Tests"){
    
    
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
    
    SECTION("Only one control point in linear animation"){
        
        
        try{
            
            LG_LinearAnimation *anim=dynamic_cast<LG_LinearAnimation *>( LG_Animation::animationForElement(&map, linear2));
            FAIL("Failed to notice invalid number of control points (1!)");
        
        }catch(LG_Parse_Exception_Missing_Element *ex){
            
            REQUIRE(str_eq(ex->element,"controlpoint"));
        
        }
        
        
    }
    
    
    
    
    
}


TEST_CASE("Testing Animation Contaniner Parsing"){


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
    
    TiXmlElement *container=(TiXmlElement *)doc->LastChild();
    
    
    
    SECTION("Formed Container with two animations"){
        
        try {
            LG_Animation_Container *containerNode=new LG_Animation_Container(container);
            REQUIRE(containerNode->childsIDs.size()==2);
            REQUIRE(str_eq(containerNode->child(0)->identifier,"firstAnim"));
            REQUIRE(str_eq(containerNode->child(1)->identifier,"secondAnim"));
        } catch (LG_Parse_Exception *ex) {
            FAIL("Thrown exception while parsing well formed linear animation");
        }
        
    }

    
    
}



TEST_CASE("Testing Linear Animation Processing"){

    
    TiXmlDocument *doc=new TiXmlDocument("./testFiles/TestAnimations2.xml");
    REQUIRE(doc->LoadFile());
    LG_Node_Map map;
    
    TiXmlElement *linear1=doc->FirstChildElement();
    
    
    double identity[4][4];
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glGetDoublev(GL_MODELVIEW, (GLdouble *)identity);
    double translate1InX[4][4];
    glTranslated(1, 0, 0);
    glGetDoublev(GL_MODELVIEW, (GLdouble *)translate1InX);
    glLoadIdentity();
    double translateToPlaceAfter3Units[4][4];
    glLoadIdentity();
    glTranslated(1+1./5.*3., 0, 0);
    glGetDoublev(GL_MODELVIEW, (GLdouble *)translateToPlaceAfter3Units);
    double rotateInZ90[4][4];
    glLoadIdentity();
    glRotated(90, 0, 0, 1);
    glGetDoublev(GL_MODELVIEW, (GLdouble *)rotateInZ90);
    
    double translateToPlaceAfter6TimeUnits[4][4];
    glLoadIdentity();
    glTranslated(2, 1./5, 0);
    glGetDoublev(GL_MODELVIEW, (GLdouble *)translateToPlaceAfter6TimeUnits);
    
    double translateToEnd[4][4];
    glLoadIdentity();
    glTranslated(2, 1, 0);
    glGetDoublev(GL_MODELVIEW, (GLdouble *)translateToEnd);
    
    
    LG_LinearAnimation *anim;
    try {
        anim=(LG_LinearAnimation *)LG_Animation::animationForElement(&map, linear1);
        
        
        
        
    } catch (LG_Parse_Exception *ex) {
        FAIL("Failed while parsing perfectly well formed linear animation");
    }

    
    
    SECTION("Testing start conditions"){
        
        REQUIRE(fabs(anim->velocity-1./5000)<=0.0000001);
        REQUIRE(fabs(anim->timeToSwitchSegment-5000)<=0.0001);
        REQUIRE(fabs(anim->totalDistance-2.)<=0.0001);
        REQUIRE(anim->currentSegment==0);
        REQUIRE(fabs(anim->directionVector[X_]-1.0)<=0.0001);
        REQUIRE(fabs(anim->directionVector[Y_]-0.0)<=0.00001);
        REQUIRE(fabs(anim->directionVector[Z_]-0.0)<=0.00001);
        REQUIRE(fabs(anim->controlPointHitTime[0]-0.000)<=0.00001);
        REQUIRE(fabs(anim->controlPointHitTime[1]-5000)<=0.00001);
        REQUIRE(fabs(anim->controlPointHitTime[2]-anim->span)<=0.00001);
        
        
        
        
        for (int i=0; i<4; i++) {
            for (int f=0; f<4; f++) {
                REQUIRE(fabs(identity[i][f]-anim->rotation_matrix[i][f])<=0.0001);
            }
        }
        
        
        for (int i=0; i<4; i++) {
            for (int f=0; f<4; f++) {
                REQUIRE(fabs(translate1InX[i][f]-anim->translation_matrix[i][f])<=0.0001);
            }
        }
        
    
    
    }

    
    
    SECTION("Testing conditions after initialization"){
    
    
        
        anim->update(10);
        
        REQUIRE(fabs(anim->startTime-10.0)<=0.0001);
        double *directionVect=anim->directionVector;
        
        REQUIRE(fabs(directionVect[X_]-1.00)<=0.0001);
        REQUIRE(fabs(directionVect[Y_]-0.00)<=0.0001);
        REQUIRE(fabs(directionVect[Z_]-0.00)<=0.0001);
        
        
        //matrixes should not be altered at this point since is first update!!!
        
        for (int i=0; i<4; i++) {
            for (int f=0; f<4; f++) {
                REQUIRE(fabs(anim->rotation_matrix[i][f]-identity[i][f])<=0.0001);
            }
        }
        
        for (int i=0; i<4; i++) {
            for (int f=0; f<4; f++) {
                REQUIRE(fabs(anim->translation_matrix[i][f]-translate1InX[i][f])<=0.0001);
            }
        }
        
        
    
        
    
    }
    
    
    SECTION("Verfications before second control point"){
    
    
        anim->update(10000);//start
        
        anim->update(13000);//3 time units after
        
        REQUIRE(anim->currentSegment==0);
        
        for(int i=0;i<4;i++){
            for (int f=0; f<4; f++) {
                REQUIRE(fabs(anim->rotation_matrix[i][f]-identity[i][f])<=0.00001);
            }
        }
        
        for(int i=0;i<4;i++){
            for (int f=0; f<4; f++) {
                REQUIRE(fabs(anim->translation_matrix[i][f]-translateToPlaceAfter3Units[i][f])<=0.00001);
                
            }
        }
        
        
    
    }
    
    SECTION("Verifications After second control point"){
    
    
        anim->update(10000);
        anim->update(16000);
        
        REQUIRE(anim->currentSegment==1);
        
        
        for(int i=0;i<4;i++){
            for (int f=0; f<4; f++) {
                REQUIRE(fabs(anim->rotation_matrix[i][f]-rotateInZ90[i][f])<=0.00001);
                
            }
        }
        
        for(int i=0;i<4;i++){
            for (int f=0; f<4; f++) {
                REQUIRE(fabs(anim->translation_matrix[i][f]-translateToPlaceAfter6TimeUnits[i][f])<=0.00001);
                
            }
        }
        
        
        
        
    
    
    }
    
    SECTION("Verification After animation end"){
    
        anim->update(10000);
        anim->update(50000);//way after animation end
        
        REQUIRE(anim->currentSegment==1);
        
        
        for(int i=0;i<4;i++){
            for (int f=0; f<4; f++) {
                REQUIRE(fabs(anim->rotation_matrix[i][f]-rotateInZ90[i][f])<=0.00001);
                
            }
        }
        
        for(int i=0;i<4;i++){
            for (int f=0; f<4; f++) {
                REQUIRE(fabs(anim->translation_matrix[i][f]-translateToEnd[i][f])<=0.00001);
                
            }
        }

    
    
    }

}
