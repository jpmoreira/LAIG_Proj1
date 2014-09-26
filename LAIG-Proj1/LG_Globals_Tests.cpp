#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.h"
#define private public //disable encapsulation for following files, allowing testing to be done

#include <tinyxml.h>
#include <LG_Lighting.h>

TEST_CASE("Testing lighting"){


    TiXmlDocument *doc=new TiXmlDocument("./testFiles/TestGlobals.xml");

    
    REQUIRE(doc->LoadFile());
    
    
    TiXmlElement *ele=(TiXmlElement *)doc->FirstChild();
   

    LG_Parsable_Node *node=new LG_Parsable_Node(NULL,"ola");
    
    int cmp=strcmp(ele->Value(), "lighting");
    
    REQUIRE(cmp==0);
}


