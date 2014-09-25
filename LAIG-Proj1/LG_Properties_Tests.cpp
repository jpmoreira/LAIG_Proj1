#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.h"
#include "LG_Properties.h"



TEST_CASE( "test constructor") {
    
    
    LG_Matrix matrix={{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
    LG_LightArray array1={0.99,0.98,0.97,1.0};
    LG_LightArray array2={0.95,0.97,0.95,1.2};
    LG_LightArray array3={0.9,0.88,0.67,1.1};
    
    LG_Properties *prop=new LG_Properties(matrix,array1,array2,array3,27);
    
    
    
    SECTION("Test ambient array"){
    
        
        for (int i=0; i<4; i++) REQUIRE(prop->ambient[i]==array1[i]);
        
    
    }
    
    
    SECTION("Test diffuse array"){
    
        for (int i=0; i<4; i++) REQUIRE(prop->diffuse[i]==array2[i]);
    
        
    }
    
    SECTION("Test specular array"){
        
        for (int i=0; i<4; i++) REQUIRE(prop->specular[i]==array3[i]);
        
        
    }
    
    
    SECTION("Test shininess"){
        
        REQUIRE(prop->shininess==27);
        
        
    }
    
    SECTION("Test matrix"){
        
        for (int i=0; i<4; i++) {
            for (int f=0; f<4; f++)REQUIRE(prop->matrix[i][f]==matrix[i][f]);
        }
        
    }
    
    
    

    
    

    
}