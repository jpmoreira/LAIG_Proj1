//
//  LG_Parsable_Node.h
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 24/09/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#ifndef __LAIG_Proj1__LG_Parsable_Node__
#define __LAIG_Proj1__LG_Parsable_Node__

#include <stdio.h>
#include "LG_Node.h"
#include <tinyxml.h>
#include <limits.h>
#include <math.h>
#include <cfloat>

using std::exception;


#define LG_INVALID_INT INT_MAX
#define LG_INVALID_DOUBLE DBL_MAX //didn't use NaN because checking nan==nan always returns false


typedef enum{

    LG_False,
    LG_True,
    LG_Invalid_Bool

} LG_BOOL;



#define LG_BOOL_STRING_TRUE "true"
#define LG_BOOL_STRING_FALSE "false"


class LG_Parsable_Node : LG_Node{

public:
    /**
     
     
     Simple Constructor, that simply calls the superclass constructor with the same parameters
     
     */
    
    LG_Parsable_Node(LG_Node_Map *map,string identif);
    
protected:
    
    /**
     
     
     A virtual method to be implemented by all subclasses. It's supposed to verify that this element is indeed the supposed one for the specified subclass.
     This method is called in the LG_Parsable_Node constructor.
     
     */
    virtual void verifyElementName(TiXmlElement *element)=0;
    
    /**
     
     
     A virtual method to be implemented by all subclasses. It's supposed to verify that this element does indeed have the supposed properties with the allowed values.
     This method is called in the LG_Parsable_Node constructor.
     
     */
    virtual void verifyElementAttributesAndValues(TiXmlElement *element)=0;
    
    
public:
    
    /**
     
     A method that extracts the int value from an attribute. If the value isn't an int than
     
     LG_INVALID_INT is returned.
     
     */
    static inline int intValueForAttribute(TiXmlAttribute *att){
        
        int value;
        int result=att->QueryIntValue(&value);
        
        if (result==TIXML_SUCCESS)return value;
        
        return LG_INVALID_INT;
        
        
        
        
    }

    
    
    /**
     
     A method that extracts the bool value from an attribute. If the bool is true LG_True is returned, if false LG_False is returned. In case an invalid bool is present LG_Invalid_Bool is returned.
     */
    
    static inline LG_BOOL boolValueForAttribute(TiXmlAttribute *att){
        
        
        const char * value=att->Value();
        
        int compareResult=strcmp(value, LG_BOOL_STRING_TRUE);
        if (compareResult==0) return LG_True;
        compareResult=strcmp(value, LG_BOOL_STRING_FALSE);
        if (compareResult==0)return LG_False;
        return LG_Invalid_Bool;
        
    }
    
    /**
     
     
     A method that extracts the double value from an attribute. In case an invalid double is present, LG_INVALID_DOUBLE is returned.
     
     */
    
    static inline double doubleValueForAttribute(TiXmlAttribute *att){
        
        
        
        double value;
        int result=att->QueryDoubleValue(&value);
        if (result==TIXML_SUCCESS)return value;
        return LG_INVALID_DOUBLE;
        
        
    }
    
    


};




class LG_Parse_Exception: exception{
    
    
protected:
    string* element;
    
public:
    LG_Parse_Exception(string* elem);
    virtual ~LG_Parse_Exception();
    
};


class LG_Parse_Exception_Wrong_Attribute_Value: LG_Parse_Exception{

private:
    string* attribute;
    string* actualValue;
    vector<string> *expectedValues;
    
public:
    
    LG_Parse_Exception_Wrong_Attribute_Value(string *elem,string* attrib,string* value,vector<string> *expected);
    ~LG_Parse_Exception_Wrong_Attribute_Value();
    char* what();

    
    

};


class LG_Parse_Exception_Missing_Attribute: LG_Parse_Exception{
private:
    string* missingAttribute;
    
public:
    LG_Parse_Exception_Missing_Attribute(string *elementName,string * missingAtt);
    
    char * what();
    
    ~LG_Parse_Exception_Missing_Attribute();


};



class LG_Parse_Exception_Wrong_Element_Name: LG_Parse_Exception{

public:
    LG_Parse_Exception_Wrong_Element_Name(string * expectedElementName, string * actualElementName);
    
    ~LG_Parse_Exception_Wrong_Element_Name();
    
    char * what();

private:
    string *expectedElementName;
    
};


class LG_Parse_Exception_Missing_Element: LG_Parse_Exception{


    LG_Parse_Exception_Missing_Element(string *elem);

};

#endif /* defined(__LAIG_Proj1__LG_Parsable_Node__) */
