//
//  LG_Parsable_Node.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 24/09/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//


#include "LG_Parsable_Node.h"



LG_Parsable_Node::LG_Parsable_Node(LG_Node_Map *map, string identif) :LG_Node(map, identif){


}



#pragma mark - Generic Parse Exception


LG_Parse_Exception::LG_Parse_Exception(string *elem) :element(elem){


}

LG_Parse_Exception::~LG_Parse_Exception(){

	delete element;

}

#pragma mark - Wrong Attribute Value Exception


const char * LG_Parse_Exception_Wrong_Attribute_Value::what(){


	string tempMessage = "Wrong Attribute Value on Element " + *element + ".\nValue: " + *actualValue + "\n";
    
    if (expectedValues!=NULL) {
        
        tempMessage=tempMessage.append("Expected: [");
        int i;
        for (i = 0; i < expectedValues->size() - 1; i++) {
            tempMessage += expectedValues->at(i) + " or ";//add each element but the last one, with the "or" after
        }
        
        tempMessage += expectedValues->at(i) + "].";//add last element and close brackets
        
        
    }
	


	return strdup(tempMessage.c_str());//create copy on the heap and return

}


LG_Parse_Exception_Wrong_Attribute_Value::LG_Parse_Exception_Wrong_Attribute_Value(string* elem, string* attrib, string* value, vector<string> *expected) :LG_Parse_Exception(elem), attribute(attrib), actualValue(value), expectedValues(expected){


}






LG_Parse_Exception_Wrong_Attribute_Value::LG_Parse_Exception_Wrong_Attribute_Value(const char *elem,const char * att,const char *value,vector<string> *expected):LG_Parse_Exception(new string(elem)), attribute(new string(att))
, actualValue(new string(value)), expectedValues(expected)
{

}

LG_Parse_Exception_Wrong_Attribute_Value::LG_Parse_Exception_Wrong_Attribute_Value(string* elem, string* attrib, string* value) :LG_Parse_Exception(elem), attribute(attrib), actualValue(value), expectedValues(NULL){
    
    
    
    
}

LG_Parse_Exception_Wrong_Attribute_Value::LG_Parse_Exception_Wrong_Attribute_Value(const char *elem, const char* attrib, const char* value) :LG_Parse_Exception(new string(elem)), attribute(new string(attrib)), actualValue(new string(value)){

}


LG_Parse_Exception_Wrong_Attribute_Value::~LG_Parse_Exception_Wrong_Attribute_Value(){

	delete attribute;
	delete expectedValues;
	delete actualValue;

}



#pragma mark - Wrong Element Name Exception


LG_Parse_Exception_Wrong_Element_Name::LG_Parse_Exception_Wrong_Element_Name(string * expectedElementName, string * actualElementName) :LG_Parse_Exception(actualElementName), expectedElementName(expectedElementName){




}

LG_Parse_Exception_Wrong_Element_Name::LG_Parse_Exception_Wrong_Element_Name(const char * expectedElementName, const char * actualElementName) :LG_Parse_Exception(new string(actualElementName)), expectedElementName(new string(expectedElementName)){


}

LG_Parse_Exception_Wrong_Element_Name::~LG_Parse_Exception_Wrong_Element_Name(){

	delete expectedElementName;

}


const char * LG_Parse_Exception_Wrong_Element_Name::what(){


	string tempMessage = "Wrong Element Name. Expected " + *expectedElementName + ".\nBut Got: " + *element + ".";


	return strdup(tempMessage.c_str());


}


#pragma mark - Missing Attribute Name Exception


LG_Parse_Exception_Missing_Attribute::LG_Parse_Exception_Missing_Attribute(string *elementName, string * missingAtt) :LG_Parse_Exception(elementName), missingAttribute(missingAtt){


}

const char * LG_Parse_Exception_Missing_Attribute::what(){

	string message = "Missing attribute " + *missingAttribute + " for element " + *element + ".";

	return strdup(message.c_str());
}

LG_Parse_Exception_Missing_Attribute::~LG_Parse_Exception_Missing_Attribute(){

	delete missingAttribute;


}

#pragma mark - Missing Element Exception

LG_Parse_Exception_Missing_Element::LG_Parse_Exception_Missing_Element(string *elem) :LG_Parse_Exception(elem){


}
LG_Parse_Exception_Missing_Element::LG_Parse_Exception_Missing_Element(const char *elem) : LG_Parse_Exception(new string(elem)){
}


#pragma mark - Wrong Element Type Exception

LG_Parse_Exception_Wrong_Elem_Type::LG_Parse_Exception_Wrong_Elem_Type(string *expected_type) :LG_Parse_Exception(expected_type){
	this->expected_type = expected_type;
}


LG_Parse_Exception_Wrong_Elem_Type::~LG_Parse_Exception_Wrong_Elem_Type(){
}


#pragma mark - Broken Reference Exception


const char * LG_Parse_Exception_Broken_Reference::what(){

    string message= "Broken Reference to Element of Type "+*refered_Type+" with ID="+*reference+" while parsing element "+*element;
    
    return strdup(message.c_str());
}
LG_Parse_Exception_Broken_Reference::LG_Parse_Exception_Broken_Reference(string * elementWhereErrorOccured, string * reference,string *referedElementName):LG_Parse_Exception(elementWhereErrorOccured),reference(reference),refered_Type(referedElementName){

}


LG_Parse_Exception_Broken_Reference::LG_Parse_Exception_Broken_Reference(const char * elementWhereErrorOccured, const char * reference,const char *referedElementName):LG_Parse_Exception(new string(elementWhereErrorOccured)),reference(new string(reference)),refered_Type(new string(referedElementName)){
    
    
}

LG_Parse_Exception_Broken_Reference::~LG_Parse_Exception_Broken_Reference(){

    delete reference;
    delete refered_Type;

}



#pragma mark - Redundant Reference Exception

LG_Parse_Exception_Redundant_Reference::LG_Parse_Exception_Redundant_Reference(string *element):LG_Parse_Exception(element){
}
LG_Parse_Exception_Redundant_Reference::LG_Parse_Exception_Redundant_Reference(const char *element):LG_Parse_Exception(new string(element)){


}
