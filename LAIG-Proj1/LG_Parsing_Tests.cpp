#ifndef LG_ALL_TESTS
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.h"
#define private public //disable encapsulation for following files, allowing testing to be done
#endif
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

TEST_CASE("Testing parsing a valid int 2"){
    
    
    int value=LG_Parsable_Node::intValueForAttribute_("123");
    
    REQUIRE(value==123);
    
    
}



TEST_CASE("Testing parsing an invalid int"){
    
    
    TiXmlAttribute *att=new TiXmlAttribute("att","adasd");
    
    int value=LG_Parsable_Node::intValueForAttribute(att);
    
    REQUIRE(value==LG_INVALID_INT);
    
    
}
TEST_CASE("Testing parsing an invalid int 2"){
    

    
    int value=LG_Parsable_Node::intValueForAttribute_("xhdf");
    
    REQUIRE(value==LG_INVALID_INT);
    
    
}


TEST_CASE("Testing parsing a valid double"){
    
    
    TiXmlAttribute *att=new TiXmlAttribute("att","1.245");
    
    double value=LG_Parsable_Node::doubleValueForAttribute(att);
    
    double delta=abs(value-1.245);
    
    REQUIRE(delta<=0.00001);
    
    
}

TEST_CASE("Testing parsing a valid double 2"){
    
    
    
    double value=LG_Parsable_Node::doubleValueForAttribute_("1.40890");
    
    double delta=abs(value-1.40890);
    
    REQUIRE(delta<=0.00001);
    
    
}



TEST_CASE("Testing parsing an invalid double"){
    
    TiXmlAttribute *att=new TiXmlAttribute("att","ado");
    
    double value=LG_Parsable_Node::doubleValueForAttribute(att);
    
    REQUIRE(value==LG_INVALID_DOUBLE);
    
    
}

TEST_CASE("Testing parsing an invalid double 2"){
    
    double value=LG_Parsable_Node::doubleValueForAttribute_("blabla");
    
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


TEST_CASE("Testing parsing a valid string"){

    
    TiXmlAttribute *att=new TiXmlAttribute("att","aString");
    
    char * values[3];
    
    char string1[]="string1";
    char string2[]="anotherString";
    char string3[]="aString";
    values[0]=string1;
    values[1]=string2;
    values[2]=string3;
    
    int i=LG_Parsable_Node::stringValue(att, values, 3);
    
    REQUIRE(i>=0);
    
    

}


TEST_CASE("Testing parsing an invalid string"){
    
    
    TiXmlAttribute *att=new TiXmlAttribute("att","aThatIsWrong");
    
    char * values[3];
    
    char string1[]="string1";
    char string2[]="anotherString";
    char string3[]="aString";
    values[0]=string1;
    values[1]=string2;
    values[2]=string3;
    
    int i=LG_Parsable_Node::stringValue(att, values, 3);
    
    REQUIRE(i==-1);
    
    
    
}


TEST_CASE("Testing lightArray correct parsing"){


    
    TiXmlAttribute *att=new TiXmlAttribute("att","20.3 10.4 1.4 0.56");
    
    LG_LightArray array;
    
    bool correct=LG_Parsable_Node::lightArrayValue(att, array);
    
    REQUIRE(correct);
    REQUIRE(abs(array[0]-20.3)<=0.0001);
    REQUIRE(abs(array[1]-10.4)<=0.0001);
    REQUIRE(abs(array[2]-1.4)<=0.0001);
    REQUIRE(abs(array[3]-0.56)<=0.0001);
    
    
    

}

TEST_CASE("Testing lightArray incorrect parsing"){
    
    
    
    TiXmlAttribute *att=new TiXmlAttribute("att","20.3 10.4 1.4 ");//missing one element
    
    LG_LightArray array;
    
    bool correct=LG_Parsable_Node::lightArrayValue(att, array);
    
    REQUIRE(!correct);
    REQUIRE(abs(array[0]-LG_LightValue_Not_Set)<=0.00001);
    REQUIRE(abs(array[1]-LG_LightValue_Not_Set)<=0.00001);
    REQUIRE(abs(array[2]-LG_LightValue_Not_Set)<=0.00001);
    REQUIRE(abs(array[3]-LG_LightValue_Not_Set)<=0.00001);
    
    
    
}


TEST_CASE("Testing lightArray too lenghty parsing"){
    
    
    
    TiXmlAttribute *att=new TiXmlAttribute("att","20.3 10.4 1.4 1.5 3.5");//missing one element
    
    LG_LightArray array;
    
    bool correct=LG_Parsable_Node::lightArrayValue(att, array);
    
    REQUIRE(!correct);
    REQUIRE(abs(array[0]-LG_LightValue_Not_Set)<=0.00001);
    REQUIRE(abs(array[1]-LG_LightValue_Not_Set)<=0.00001);
    REQUIRE(abs(array[2]-LG_LightValue_Not_Set)<=0.00001);
    REQUIRE(abs(array[3]-LG_LightValue_Not_Set)<=0.00001);
    
    
    
}


TEST_CASE("Testing correct LG_Point"){
    
    
    TiXmlAttribute *att =new TiXmlAttribute("att","20.3 30.0 5.0");
    
    LG_Point3D pt;
    
    bool correct=LG_Parsable_Node::point3DValue(att, pt);
    
    
    REQUIRE(correct);
    REQUIRE(abs(pt[0]-20.3)<=0.0001);
    REQUIRE(abs(pt[1]-30.0)<=0.0001);
    REQUIRE(abs(pt[2]-5.0)<=0.0001);

}

TEST_CASE("Testing incorrect LG_Point3D (too short)"){
    
    
    TiXmlAttribute *att =new TiXmlAttribute("att","20.3 30.0");
    
    LG_Point3D pt;
    
    bool correct=LG_Parsable_Node::point3DValue(att, pt);
    
    
     REQUIRE(!correct);
     REQUIRE(abs(pt[0]-LG_INVALID_DOUBLE)<=0.0001);
     REQUIRE(abs(pt[1]-LG_INVALID_DOUBLE)<=0.0001);
     REQUIRE(abs(pt[2]-LG_INVALID_DOUBLE)<=0.0001);
     
    
    
    
    
}

TEST_CASE("Testing incorrect LG_Point3D (too large)"){
    
    
    TiXmlAttribute *att =new TiXmlAttribute("att","20.3 30.0 50.7 44.9");
    
    LG_Point3D pt;
    
    bool correct=LG_Parsable_Node::point3DValue(att, pt);
    
    
    REQUIRE(!correct);
    REQUIRE(abs(pt[0]-LG_INVALID_DOUBLE)<=0.0001);
    REQUIRE(abs(pt[1]-LG_INVALID_DOUBLE)<=0.0001);
    REQUIRE(abs(pt[2]-LG_INVALID_DOUBLE)<=0.0001);
    
    
    
    
    
}



