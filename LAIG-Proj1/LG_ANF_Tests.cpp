


//#ifndef LG_ALL_TESTS
//#define CATCH_CONFIG_RUNNER  // This tells Catch to provide a main() - only do this in one cpp file
//#include "catch.h"
//#define private public //disable encapsulation for following files, allowing testing to be done
//#define protected public
//#endif


#include <CGFapplication.h>
#include <iostream>
#include <string>
#include "LG_ANF.h"
#include "LG_Scene.h"
//
//TEST_CASE("Testing hole configuration parsing"){
//    
//    
//    TiXmlDocument *doc=new TiXmlDocument("testFiles/testANF.xml");
//    
//    REQUIRE(doc->LoadFile());
//    
//    
//    TiXmlElement *firstElement=doc->FirstChildElement();
//    
//    
//    
//    SECTION("Testing well formed configuration section"){
//        
//        
//        try {
//            LG_ANF *anf=new LG_ANF(firstElement);
//            
//            REQUIRE(str_eq(anf->graph->root->appearance->identifier.c_str(),"appear1"));
//            REQUIRE(anf->apperances->childsIDs.size()==1);
//            REQUIRE(anf->textures->childsIDs.size()==0);
//            REQUIRE(anf->lights->childsIDs.size()==2);
//            REQUIRE(anf->cameras->childsIDs.size()==2);
//        
//            std::cout<<anf->graph->child(0)->identifier<<std::endl;
//            REQUIRE(anf->graph->childsIDs.size()==1);
//        
//        } catch (LG_Parse_Exception *ex) {
//            
//            std::cout<<string(ex->what())<<std::endl;
//            FAIL("Thrown exception while parsing perfectly well formed ANF graph");
//            
//            
//        }
//        
//    }
//    
//    
//}



int main(int argc, char * argv[]){

    
    
    
    CGFapplication app = CGFapplication();
    
    int result=0;
    
    try {
        app.init(&argc, argv);
        
        LG_Scene *scene=new LG_Scene();
#ifdef _WIN32
        scene->setDocName("TestANF.xml");
#else
        scene->setDocName("./testFiles/TestANF.xml");
#endif
        
        
        app.setScene(scene);
        app.setInterface(new CGFinterface());
        //app.setInterface(new TPinterface());
        
        //result=Catch::Session().run(argc, argv);//run tests before starting app
        
        app.run();
    }
    catch(GLexception& ex) {
       cout << "Erro: " << ex.what();
        return -1;
    }
    catch(exception& ex) {
        cout << "Erro inesperado: " << ex.what();
        return -1;
    }
    
    
    
    return result;

}
