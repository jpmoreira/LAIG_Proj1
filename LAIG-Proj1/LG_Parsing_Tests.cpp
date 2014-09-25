#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.h"
#define private public //disable encapsulation for following files, allowing testing to be done

#include "LG_Parsable_Node.h"

TEST_CASE("Wrong attribute value Exception"){


    string elem="ElemX";
    string actualValue="Actual";
    string attrib="Attribute";
    vector<string> expected={"value1","value2","value3"};
    LG_Parse_Exception_Wrong_Attribute_Value *ex=new LG_Parse_Exception_Wrong_Attribute_Value(&elem,&attrib,&actualValue,&expected);
    
    char * actual=ex->what();
    
    int compare=strcmp(actual, "Wrong Attribute Value on Element ElemX.\nValue: Actual\nExpected: [value1 or value2 or value3].");
    
    REQUIRE(compare==0);
    



}


TEST_CASE("Wrong ELement name Exception"){
    
    
    string elem="ExpectedName";
    string actual="ActualName";
    LG_Parse_Exception_Wrong_Element_Name *ex=new LG_Parse_Exception_Wrong_Element_Name(&elem,&actual);
    
    char * actualWhat=ex->what();
    
    int compare=strcmp(actualWhat, "Wrong Element Name. Expected ExpectedName.\nBut Got: ActualName.");



    REQUIRE(compare==0);

}



TEST_CASE("Missing Attribute Exception"){


    string attribute="Attrib";
    string elemName="ELEMX";
    LG_Parse_Exception_Missing_Attribute *ex=new LG_Parse_Exception_Missing_Attribute(&elemName,&attribute);
    
    
    char * whatMessage=ex->what();
    
    int compare=strcmp(whatMessage, "Missing attribute Attrib for element ELEMX.");
    
    REQUIRE(compare==0);
    
}



TEST_CASE("Testing parsing a valid int"){
    
    TiXmlAttribute *att=new TiXmlAttribute("att","123");
    
   int value=LG_Parsable_Node::intValueForAttribute(att);
    
    REQUIRE(value==123);


}



TEST_CASE("Testing parsing an invalid int"){
    
    
    TiXmlAttribute *att=new TiXmlAttribute("att","adasd");
    
    int value=LG_Parsable_Node::intValueForAttribute(att);
    
    REQUIRE(value==LG_INVALID_INT);
    
    
}


TEST_CASE("Testing parsing a valid double"){
    
    
    TiXmlAttribute *att=new TiXmlAttribute("att","1.245");
    
    double value=LG_Parsable_Node::doubleValueForAttribute(att);
    
    double delta=abs(value-1.245);
    
    REQUIRE(delta<=0.00001);
    
    
}



TEST_CASE("Testing parsing an invalid double"){
    
    TiXmlAttribute *att=new TiXmlAttribute("att","ado");
    
    double value=LG_Parsable_Node::doubleValueForAttribute(att);
    
    REQUIRE(value==LG_INVALID_DOUBLE);
    
    
}
TEST_CASE("Testing parsing a valid bool"){
    
    
    TiXmlAttribute *att=new TiXmlAttribute("att","true");
    
    LG_BOOL value=LG_Parsable_Node::boolValueForAttribute(att);
    
    REQUIRE(value==LG_True);
    
}



TEST_CASE("Testing parsing an invalid bool"){
    
    TiXmlAttribute *att=new TiXmlAttribute("att","justGarbage");
    
    LG_BOOL value=LG_Parsable_Node::boolValueForAttribute(att);
    
    REQUIRE(value==LG_Invalid_Bool);
    
    
}