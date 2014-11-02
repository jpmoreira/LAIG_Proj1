

#ifndef LG_ALL_TESTS
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.h"
#define private public //disable encapsulation for following files, allowing testing to be done
#define protected public
#endif

#include "LG_Essentials.h"


TEST_CASE("vector lenght computation test"){

    
    SECTION("Testing (1,0,0) lenght"){
    
        double vec1[3]={1,0,0};
        
        REQUIRE(fabs(lenght(vec1)-1.000)<=0.00001);
        
    }
    
    
    SECTION("Testing (1,1,0) lenght"){
    
        double vec2[3]={1,1,0};
        REQUIRE(fabs(lenght(vec2)-sqrt(2))<=0.0001);
    
    }
    
    SECTION("Testing (1,2,4) lenght"){
    
        double vec3[3]={1,2,4};
        
        REQUIRE(fabs(lenght(vec3)-sqrt(16+4+1))<0.0001);
    
    }
    
    
}


TEST_CASE("Testing Normalize"){



    SECTION("Normalize (1,1,0)"){
    
        double  vect[3]={1,1,0};
        
        normalize(vect);
        REQUIRE(fabs(vect[X_]-1./sqrt(2))<0.0001);
        REQUIRE(fabs(vect[Y_]-1./sqrt(2))<0.0001);
        REQUIRE(fabs(vect[Z_]-0./sqrt(2))<0.0001);
        
        
    
    }
    
    SECTION("Normalize  (3,4,5)");
    
    
    double vect[3]={3,4,5};
    
    normalize(vect);
    
    REQUIRE(fabs(vect[X_]-3./sqrt(9+16+25))<=0.0001);
    REQUIRE(fabs(vect[Y_]-4./sqrt(9+16+25))<=0.0001);
    REQUIRE(fabs(vect[Z_]-5./sqrt(9+16+25))<=0.0001);

}

TEST_CASE("Test dot product"){
    
    

    SECTION("(1,0,0).(0,0,1)"){
    
    
        double vec1[3]={1,0,0};
        double vec2[3]={0,0,1};
        
        double dot=dotProduct(vec1, vec2);
        
        REQUIRE(fabs(dot-0.00)<=0.00001);
    
    }
    
    SECTION("(1,0,1).(1,0,1)"){
    
        double vect1[3]={1,0,1};
        
        double dot=dotProduct(vect1, vect1);
        
        REQUIRE(fabs(dot-2)<=0.00001);
        
    }
    
    SECTION("(1,0,0).(5,5,5)"){
    
        double vect1[3]={1,0,0};
        double vect2[3]={5,5,5};
        
        double dot=dotProduct(vect1, vect2);
        
        REQUIRE(fabs(dot-vect2[Y_])<=0.0001);
    }
    
    
}


TEST_CASE("Angle between vectors"){

    
    SECTION("angle between axis"){
        
        double vect[3]={1,0,0};
        double vect2[3]={0,1,0};
        double vect3[3]={0,0,5};
        
        double angle1=angleBetween(vect, vect2);
        double angle2=angleBetween(vect2, vect3);
        
        REQUIRE(fabs(angle1-M_PI/2.0)<0.0001);
        REQUIRE(fabs(angle2-M_PI/2.0)<0.0001);
        
        
        
    
    }
    SECTION("angle between same vector whith different lenghts"){
    
    
        double vect[3]={0,5,0};
        double vect2[3]={0,3,0};
        
        double angle=angleBetween(vect, vect2);
        REQUIRE(fabs(angle-0.0)<=0.001);
    
    }
    
    
    SECTION("angle between diametrally opposite vectors"){
    
        double vect[3]={0,5,0};
        double vect2[3]={0,-10,0};
        
        double angle=angleBetween(vect, vect2);
        REQUIRE(fabs(angle-M_PI)<=0.001);
    
    }
    
   
}


TEST_CASE("Testing cross product"){
    
    
    SECTION("Testing X x Y"){
        
        double x_vector[3]={1,0,0};
        double y_vector[3]={0,1,0};
        
        vector<double> cross =crossProduct(x_vector, y_vector);
    
    
        REQUIRE(fabs(cross[X_]-0.0)<=0.0001);
        REQUIRE(fabs(cross[Y_]-0.0)<=0.0001);
        REQUIRE(fabs(cross[Z_]-1.0)<=0.0001);
    }
    
    SECTION("Testing X x Y is indeed -(Y x X)"){
    
        
        double v1[3]={5,3,5};
        double v2[3]={8,25,6};
        
        vector<double> cross =crossProduct(v1, v2);
        vector<double> cross2=crossProduct(v2, v1);
        
        REQUIRE(fabs(cross[X_]+cross2[X_])<=0.0001);
        REQUIRE(fabs(cross[Y_]+cross2[Y_])<=0.0001);
        REQUIRE(fabs(cross[Z_]+cross2[Z_])<=0.0001);

    }
    
    SECTION("Testing cross product of a vector with himself"){
    
    
        double v1[3]={3,5,6};
        
        vector<double> cross=crossProduct(v1, v1);
        
        REQUIRE(fabs(cross[X_]-0.00)<0.0001);
        REQUIRE(fabs(cross[Y_]-0.00)<0.0001);
        REQUIRE(fabs(cross[Z_]-0.00)<0.0001);
    
    }
    
    
    
    
    
}
