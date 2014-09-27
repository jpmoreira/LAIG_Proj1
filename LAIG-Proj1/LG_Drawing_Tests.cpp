#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.h"
#define private public //disable encapsulation for following files, allowing testing to be done

#include "LG_Drawing.h"
#include <tinyxml.h>



TEST_CASE("Case 1"){
    
    
    TiXmlDocument *doc=new TiXmlDocument("./testFiles/TestDrawing.xml");
    
    
    REQUIRE(doc->LoadFile());
    LG_Node_Map *map=new LG_Node_Map();
    
    TiXmlElement *ele=(TiXmlElement *)doc->FirstChild();
    
    
    try {
        LG_Drawing *newDrawingNode=new LG_Drawing(map,ele);
    } catch (LG_Parse_Exception *ex) {
        FAIL("Exception Thrown");
    }
    
    REQUIRE(1==1);


}