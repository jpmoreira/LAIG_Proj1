#ifndef LG_ALL_TESTS
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.h"

#define private public //disable encapsulation for following files, allowing testing to be done
#define protected public

#endif

#include "LG_Triangle.h"





TEST_CASE("Triangle Nodes tests"){

    LG_Node_Map *map=new LG_Node_Map();
    LG_Triangle *rootTriangle=new LG_Triangle(map,"rootTriangle");
    
    SECTION("Test placement in map"){
        
        LG_Triangle *childTriangle=new LG_Triangle(map,"childTriangle");
        
        auto it=map->find("childTriangle");
        if (it==map->end())FAIL("Triangle Not added to map");
        
        REQUIRE(childTriangle==(LG_Triangle *)it->second);
        
    }
    
    
    SECTION("Test Child operations"){
    
        
        LG_Triangle *childTriangle=new LG_Triangle(map,"childTriangle");
        
        rootTriangle->addChild(childTriangle);
        
        LG_Triangle *supposedChild=(LG_Triangle *)rootTriangle->child(0);
        
        REQUIRE(supposedChild==childTriangle);
    
    
    }
    
    SECTION("Test default point values"){
        
        

        LG_Point3D origin=LG_Origin_3D_Point;
    
        for (int i=0; i<LG_Point3D_Length; i++) REQUIRE(rootTriangle->pt1[i]==LG_INVALID_DOUBLE);
        for (int i=0; i<LG_Point3D_Length; i++) REQUIRE(rootTriangle->pt2[i]==LG_INVALID_DOUBLE);
        for (int i=0; i<LG_Point3D_Length; i++) REQUIRE(rootTriangle->pt3[i]==LG_INVALID_DOUBLE);
        
        
        
    
    }

    
    SECTION("Test point assignment in constructor"){
    
        LG_Point3D point1;
        point1[0]=1;
        point1[1]=2;
        point1[2]=4;
        
        LG_Point3D point2;
        point2[0]=123;
        point2[1]=121;
        point2[2]=435;
        LG_Point3D point3;
        point3[0]=231231;
        point3[1]=14444;
        point3[2]=1313;
        
        LG_Triangle *triangle=new LG_Triangle(map,"fantasticTriangle",point1,point2,point3);
        
        for (int i=0; i<LG_Point3D_Length; i++){
            REQUIRE(triangle->pt1[i]==point1[i]);
        }
        for (int i=0; i<LG_Point3D_Length; i++){
            REQUIRE(triangle->pt2[i]==point2[i]);
        }
        for (int i=0; i<LG_Point3D_Length; i++){
            REQUIRE(triangle->pt3[i]==point3[i]);
        }
        
    
    }
    

}


TEST_CASE("Testring triangle from file"){

    TiXmlDocument *doc=new TiXmlDocument("./testFiles/TestTriangle.xml");
    
    
    REQUIRE(doc->LoadFile());
    LG_Node_Map *map=new LG_Node_Map();
    
    TiXmlElement *aGoodTriangle=(TiXmlElement *)doc->FirstChild();
    TiXmlElement *aBadTriangle=(TiXmlElement *)aGoodTriangle->NextSibling();
    TiXmlElement *anotherBadTriangle=(TiXmlElement *)aBadTriangle->NextSibling();
    TiXmlElement *lastBadTriangle=(TiXmlElement*)anotherBadTriangle->NextSibling();
    
    //Check they all exist
    REQUIRE(aGoodTriangle!=NULL);
    REQUIRE(aBadTriangle!=NULL);
    REQUIRE(anotherBadTriangle!=NULL);
    REQUIRE(lastBadTriangle!=NULL);
    
    
    
    SECTION("Testing triangle IDS"){
        
        
        LG_Triangle *t1=new LG_Triangle(map,aGoodTriangle);
        LG_Triangle *t2=new LG_Triangle(map,aGoodTriangle);
        
        REQUIRE(str_eq(t1->identifier.c_str(), "_LG_Triangle_0"));
        REQUIRE(str_eq(t2->identifier.c_str(), "_LG_Triangle_1"));
        
    }
    
    
    SECTION("Testing Good Triangle"){
        
        try {
            LG_Triangle *t=new LG_Triangle(map,aGoodTriangle);
            
            LG_Point3D pt1={0,0,0};
            LG_Point3D pt2={0,0,10};
            LG_Point3D pt3={0,10,10};
            
            REQUIRE(LG_Primitive::equalPoints(t->pt1, pt1));
            REQUIRE(LG_Primitive::equalPoints(t->pt2, pt2));
            REQUIRE(LG_Primitive::equalPoints(t->pt3, pt3));
        } catch (LG_Parse_Exception *ex) {
            FAIL("Thrown Exception While parsing a good triangle");
        }
    
    
    }
    
    SECTION("Testing First Bad Triangle"){
    
        try {
            LG_Triangle *t=new LG_Triangle(map,aBadTriangle);
            FAIL("Didn't find out the fault but should have");
        } catch (LG_Parse_Exception_Missing_Attribute *ex) {
            REQUIRE(str_eq(ex->missingAttribute->c_str(), "xyz1"));
        }
    
    }
    
    
    SECTION("Testing Second Bad Triangle"){
        
        try {
            LG_Triangle *t=new LG_Triangle(map,anotherBadTriangle);
            FAIL("Didn't find out the fault but should have");
        } catch (LG_Parse_Exception_Missing_Attribute *ex) {
            REQUIRE(str_eq(ex->missingAttribute->c_str(), "xyz3"));
        }
    
    
    }
    SECTION("Testing Last Bad Triangle"){
    
        try {
            LG_Triangle *t=new LG_Triangle(map,lastBadTriangle);
            FAIL("Didn't find out the fault but should have");
        } catch (LG_Parse_Exception_Wrong_Element_Name *ex) {
            REQUIRE(str_eq(ex->expectedElementName->c_str(), "triangle"));
        }
        
        
    }
    
    

    
    


}



