


#ifndef LG_ALL_TESTS
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.h"
#define private public //disable encapsulation for following files, allowing testing to be done
#define protected public
#endif


#include <CGFapplication.h>
#include <string>
#include "LG_ANF.h"

TEST_CASE("Testing hole configuration parsing"){
    
    
    static bool called=false;
    
    
    if (!called) {//dont init various times
        
        CGFapplication app;
        
        int zero=1;
        const char * noParams[1]={"blabla"};
        app.init(&zero, (char **)noParams);
        
        called=true;
    }

    
    
    TiXmlDocument *doc=new TiXmlDocument("testFiles/testANF.xml");
    
    REQUIRE(doc->LoadFile());
    
    
    TiXmlElement *firstElement=doc->FirstChildElement();
    
    
    
    SECTION("Testing well formed configuration section"){
        
        
        try {
            LG_ANF *anf=new LG_ANF(firstElement);
            
            REQUIRE(str_eq(anf->graph->root->appearance->identifier.c_str(),"appear1"));
            REQUIRE(anf->graph->childsIDs.size()==2);
            REQUIRE(anf->apperances->childsIDs.size()==1);
            REQUIRE(anf->textures->childsIDs.size()==0);
            REQUIRE(anf->lights->childsIDs.size()==2);
            REQUIRE(anf->cameras->childsIDs.size()==2);
        } catch (LG_Parse_Exception *ex) {
            
            std::cout<<string(ex->what())<<std::endl;
            FAIL("Thrown exception while parsing perfectly well formed ANF graph");
            
            
        }
        
    }
    
    
}
