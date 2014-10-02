#ifndef LG_ALL_TESTS
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.h"
#define private public //disable encapsulation for following files, allowing testing to be done
#define protected public
#endif

#include "LG_Appearance.h"
#include <CGFapplication.h>


TEST_CASE("Test loading Graph Node from XML"){
    
    
    static bool called=false;
    
    
    if (!called) {//dont init various times
        
        CGFapplication app;
        
        int zero=1;
        const char * noParams[1]={"blabla"};
        app.init(&zero, (char **)noParams);
        
        called=true;
    }
    
    
    
    
    TiXmlDocument *doc=new TiXmlDocument("./testFiles/TestAppearances.xml");
    REQUIRE(doc->LoadFile());
    LG_Node_Map *map=new LG_Node_Map();
    
    
    
    TiXmlElement *firstElement=doc->FirstChildElement();
    
    
    SECTION("Testing perfectly well formed Node"){
        
        
        
    }
    
}
