#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.h"
#define private public //disable encapsulation for following files, allowing testing to be done

#include "LG_Drawing.h"
#include <tinyxml.h>



TEST_CASE("Case 1"){
    
    
    TiXmlDocument *doc=new TiXmlDocument("./testFiles/TestDrawing.xml");
    
    
    REQUIRE(doc->LoadFile());
    LG_Node_Map *map=new LG_Node_Map();
    
    TiXmlElement *correct=(TiXmlElement *)doc->FirstChild();
    TiXmlElement *incorrect=(TiXmlElement *)doc->LastChild();
    
    
    
    SECTION("Testing correct one"){
    
        LG_Drawing *newDrawingNode;
        try {
            newDrawingNode=new LG_Drawing(map,correct);
        } catch (LG_Parse_Exception *ex) {
            FAIL("Exception Thrown");
        }
        
        REQUIRE(newDrawingNode->mode==LG_Drawing_Fill);
        REQUIRE(newDrawingNode->shading==LG_Gouraud);
        REQUIRE(abs(newDrawingNode->background[0]-3.7)<=0.0001);
        REQUIRE(abs(newDrawingNode->background[1]-2.8)<=0.0001);
        REQUIRE(abs(newDrawingNode->background[2]-2.8)<=0.0001);
        REQUIRE(abs(newDrawingNode->background[3]-0)<=0.0001);
        
        
        
    }
    
    SECTION("Testing incorrect one"){
    
        LG_Drawing *newDrawingNode;
        
        try {
            newDrawingNode=new LG_Drawing(map,incorrect);
        } catch (LG_Parse_Exception_Missing_Attribute *ex) {
            
            
            char message[200];
            sprintf(message,"Catched exception with message: %s", ex->what());
            
            SUCCEED(message);
        }
    
    }
    
    


}