


#ifndef LG_ALL_TESTS
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.h"
#define private public //disable encapsulation for following files, allowing testing to be done
#define protected public
#endif


#include <CGFapplication.h>
#include "LG_Config.h"

TEST_CASE("Testing hole configuration parsing"){
    
    
    
    
    TiXmlDocument *doc=new TiXmlDocument("testFiles/testConfig.xml");
    
    REQUIRE(doc->LoadFile());
    
    
    TiXmlElement *firstElement=doc->FirstChildElement();
    
    
    
    SECTION("Testing well formed configuration section"){
        
        
    }
    
    
}
