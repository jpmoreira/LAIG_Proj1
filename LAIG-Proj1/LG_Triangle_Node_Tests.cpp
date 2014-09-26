#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.h"
#define private public //disable encapsulation for following files, allowing testing to be done

#include "LG_Triangle.h"


TEST_CASE("Triangle Nodes tests"){

    LG_Node_Map *map=new LG_Node_Map();
    LG_Triangle *rootTriangle=new LG_Triangle(map,"rootTriangle");
    
    SECTION("Test placement in map"){
        
        LG_Triangle *childTriangle=new LG_Triangle(map,"childTriangle");
        
        auto it=map->find("childTriangle");
        if (it==map->end())FAIL("Triangle Not added to map");
        
        REQUIRE(childTriangle==it->second);
        
    }
    
    
    SECTION("Test Child operations"){
    
        
        LG_Triangle *childTriangle=new LG_Triangle(map,"childTriangle");
        
        rootTriangle->addChild(childTriangle);
        
        LG_Triangle *supposedChild=(LG_Triangle *)rootTriangle->child(0);
        
        REQUIRE(supposedChild==childTriangle);
    
    
    }
    
    SECTION("Test default point values"){
        
        

        LG_Point origin=LG_Origin_3D_Point;
    
        for (int i=0; i<3; i++) REQUIRE(rootTriangle->pt1[i]==origin[i]);
        for (int i=0; i<3; i++) REQUIRE(rootTriangle->pt2[i]==origin[i]);
        for (int i=0; i<3; i++) REQUIRE(rootTriangle->pt3[i]==origin[i]);
        
        
        
    
    }

    
    SECTION("Test point assignment in constructor"){
    
        LG_Point point1={1,2,4};
        LG_Point point2={123,121,435};
        LG_Point point3={231231,14444,1313};
        
        LG_Triangle *triangle=new LG_Triangle(map,"fantasticTriangle",point1,point2,point3);
        
        for (int i=0; i<3; i++)REQUIRE(triangle->pt1[i]==point1[i]);
        for (int i=0; i<3; i++)REQUIRE(triangle->pt2[i]==point2[i]);
        for (int i=0; i<3; i++)REQUIRE(triangle->pt3[i]==point3[i]);
        
        
    
    }

}

