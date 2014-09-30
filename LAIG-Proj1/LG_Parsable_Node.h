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
#include <vector>

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


class LG_Parse_Exception : exception{


protected:
	string* element;

public:
	LG_Parse_Exception(string* elem);
	virtual ~LG_Parse_Exception();

};

class LG_Parse_Exception_Wrong_Attribute_Value :public LG_Parse_Exception{

private:
	string* attribute;
	string* actualValue;
	vector<string> *expectedValues;

public:

	LG_Parse_Exception_Wrong_Attribute_Value(string *elem, string* attrib, string* value, vector<string> *expected);
	~LG_Parse_Exception_Wrong_Attribute_Value();
	char* what();




};


class LG_Parse_Exception_Wrong_Elem_Type : LG_Parse_Exception{
private:
	string *expected_type;

public:
	LG_Parse_Exception_Wrong_Elem_Type(char *expected_type);
	LG_Parse_Exception_Wrong_Elem_Type(string *expected_type);

	char * what();

	~LG_Parse_Exception_Wrong_Elem_Type();
};



class LG_Parse_Exception_Missing_Attribute :public LG_Parse_Exception{
private:
	string* missingAttribute;

public:
	LG_Parse_Exception_Missing_Attribute(string *elementName, string * missingAtt);
	LG_Parse_Exception_Missing_Attribute(char *elementName, char * missingAtt);

	char * what();

	~LG_Parse_Exception_Missing_Attribute();


};



class LG_Parse_Exception_Wrong_Element_Name :public LG_Parse_Exception{

public:
	LG_Parse_Exception_Wrong_Element_Name(string * expectedElementName, string * actualElementName);

	~LG_Parse_Exception_Wrong_Element_Name();

	char * what();

private:
	string *expectedElementName;

};


class LG_Parse_Exception_Missing_Element :public LG_Parse_Exception{



	LG_Parse_Exception_Missing_Element(string *elem);

};


class LG_Parsable_Node : public LG_Node{

public:
	/**


	 Simple Constructor, that simply calls the superclass constructor with the same parameters

	 */

	LG_Parsable_Node(LG_Node_Map *map, string identif);


public:

	/**

	 A method that extracts the int value from an attribute. If the value isn't an int than

	 LG_INVALID_INT is returned.

	 */
	static inline int intValueForAttribute(TiXmlAttribute *att){

		int value;
		int result = att->QueryIntValue(&value);

		if (result == TIXML_SUCCESS)return value;

		return LG_INVALID_INT;




	}

	/**

	 A method that extracts the int value from an attribute. If the value isn't an int than

	 LG_INVALID_INT is returned.

	 */
	static inline int intValueForAttribute_(const char *att){

		TiXmlAttribute attribute("dummy", att);
		return intValueForAttribute(&attribute);




	}



	/**

	 A method that extracts the positive int value from an attribute. If the value isn't an int than

	 LG_INVALID_INT is returned.

	 */

	static inline unsigned int positiveIntValueForAttribute(TiXmlAttribute *att){

		int value;
		int result = att->QueryIntValue(&value);

		if (result == TIXML_SUCCESS){

			if (value > 0)return value;

		}

		return LG_INVALID_INT;




	}

	/**

	 A method that extracts the positive int value from an attribute. If the value isn't an int than

	 LG_INVALID_INT is returned.

	 */

	static inline unsigned int positiveIntValueForAttribute_(const char *att){

		TiXmlAttribute attribute("dummy", att);

		return positiveIntValueForAttribute(&attribute);




	}



	/**

	 A method that extracts the bool value from an attribute. If the bool is true LG_True is returned, if false LG_False is returned. In case an invalid bool is present LG_Invalid_Bool is returned.
	 */

	static inline LG_BOOL boolValueForAttribute(TiXmlAttribute *att){


		return boolValueForAttribute_(att->Value());
	}


	/**

	 A method that extracts the bool value from an attribute. If the bool is true LG_True is returned, if false LG_False is returned. In case an invalid bool is present LG_Invalid_Bool is returned.
	 */

	static inline LG_BOOL boolValueForAttribute_(const char *value){


		int compareResult = strcmp(value, LG_BOOL_STRING_TRUE);
		if (compareResult == 0) return LG_True;
		compareResult = strcmp(value, LG_BOOL_STRING_FALSE);
		if (compareResult == 0)return LG_False;
		return LG_Invalid_Bool;

	}


	/**


	 A method that extracts the double value from an attribute. In case an invalid double is present, LG_INVALID_DOUBLE is returned.

	 */

	static inline double doubleValueForAttribute(TiXmlAttribute *att){



		double value;
		int result = att->QueryDoubleValue(&value);
		if (result == TIXML_SUCCESS)return value;
		return LG_INVALID_DOUBLE;


	}

	/**


	 A method that extracts the double value from an attribute. In case an invalid double is present, LG_INVALID_DOUBLE is returned.

	 */

	static inline double doubleValueForAttribute_(const char *att){


		TiXmlAttribute attribute("dummy", att);
		return doubleValueForAttribute(&attribute);


	}



	static inline void doubleValueForMandatoryAtts(TiXmlElement *element, vector<const char *> &att_names, vector<double *> &atts){
		string element_name(element->Value());
		unsigned int size = att_names.size();
		//TODO if size == 0 throw new Exception....
		unsigned int i = 0;
		int ti_xml_return;
		for (; i < size; i++)
			if ((ti_xml_return = element->QueryDoubleAttribute(att_names[i], atts[i])) != TIXML_SUCCESS)
				break;

		if (i != size){ //means not every att was set
			string faulty_att(att_names[i]);
			if (ti_xml_return == TIXML_NO_ATTRIBUTE)
				throw new LG_Parse_Exception_Missing_Attribute(&element_name, &faulty_att);
			else{
				vector<string> expected;
				expected.push_back("double");
				string value("TIXML_WRONG_TYPE"); // see this too
				throw new LG_Parse_Exception_Wrong_Attribute_Value(&element_name, &faulty_att, &value, &expected);
			}
		}
	}



	/**


	 A method that extracts the double value from an attribute. In case an invalid double is present, LG_INVALID_DOUBLE is returned.

	 */

	static inline double positiveDoubleValueForAttribute(TiXmlAttribute *att){



		double value;
		int result = att->QueryDoubleValue(&value);
		if (result == TIXML_SUCCESS){

			if (value > 0)return value;
		}
		return LG_INVALID_DOUBLE;


	}

	/**


	 A method that extracts the double value from an attribute. In case an invalid double is present, LG_INVALID_DOUBLE is returned.

	 */

	static inline double positiveDoubleValueForAttribute_(const char *att){

		TiXmlAttribute attribute("dummy", att);
		return positiveDoubleValueForAttribute(&attribute);

	}



	/**

	 A method that says wich of the allowed values is found in the attribute. If none is found then -1 is returned

	 */


	static inline int stringValue(TiXmlAttribute *att, char ** allowedValues, int nrAllowedValues){

		return stringValue_(att->Value(), allowedValues, nrAllowedValues);




	}

	/**

	 A method that says wich of the allowed values is found in the attribute. If none is found then -1 is returned

	 */

	static inline int stringValue_(const char * att, char ** allowedValues, int nrAllowedValues){

		for (int i = 0; i < nrAllowedValues; i++) {

			if (strcmp(att, allowedValues[i]) == 0){
				return i;
			}
		}

		return -1;




	}




	/**

	 A method that tries to initialize a lightArray with the elements coming from an attribute.
	 In case some error occurs false is returned and the array is filled with the value LG_LightValue_Not_Set
	 */

	static inline bool lightArrayValue(TiXmlAttribute *att, LG_LightArray& lightArrayToFill){


		return lightArrayValue_(att->Value(), lightArrayToFill);


	}

	/**

	 A method that tries to initialize a lightArray with the elements coming from an attribute.
	 In case some error occurs false is returned and the array is filled with the value LG_LightValue_Not_Set
	 */

	static inline bool lightArrayValue_(const char  *att, LG_LightArray& lightArrayToFill){

		double dummy;

		int nrFound = sscanf(att, "%lf %lf %lf %lf %lf", &(lightArrayToFill[0]), &(lightArrayToFill[1]), &(lightArrayToFill[2]), &(lightArrayToFill[3]), &dummy);//try to match one more... if it's matched then some error happened....

		if (nrFound != 4){

			for (int i = 0; i < LG_LightArray_Lenght; i++)
				lightArrayToFill[i] = LG_LightValue_Not_Set;
			return false;

		}


		return true;
	};

	/**

	 A method that tries to initialize a LG_Point3D with the values coming from an attribute.

	 In case some error occurs false is teturned and the array is filled with the value LG_INVALID_DOUBLE

	 */

	static inline bool point3DValue(TiXmlAttribute *att, LG_Point3D & pointToFill){


		double dummy;

		int nrFound = sscanf(att->Value(), "%lf %lf %lf  %lf", &(pointToFill[0]), &(pointToFill[1]), &(pointToFill[2]), &dummy);//try to match four... last one is supposed to never be filled in... if it is parsing didn't occur well, only 3D vectors allowed

		if (nrFound != LG_Point3D_Length){

			for (int i = 0; i < LG_Point3D_Length; i++)
				pointToFill[i] = LG_INVALID_DOUBLE;

			return false;

		}
		return true;

	}


	static inline bool point3DValue(const char  *att, LG_Point3D & pointToFill){

		double dummy;

		int nrFound = sscanf(att, "%lf %lf %lf %lf", &(pointToFill[0]), &(pointToFill[1]), &(pointToFill[2]), &dummy);//try to match one more... if it's matched then some error happened....

		if (nrFound != 3){

			for (int i = 0; i < LG_Point3D_Length; i++)
				pointToFill[i] = LG_INVALID_DOUBLE;
			return false;

		}


		return true;
	};


	static inline void point3DMandatoryDblArray(TiXmlElement *element, char * att_name, double *values){
		string elem_name = element->Value();
		string str_att_name(att_name);

		char *att_value = (char *)element->Attribute(att_name);

		double dummy;

		if (!att_value)
			throw  new LG_Parse_Exception_Missing_Attribute(&elem_name, &str_att_name);

		int nrFound = sscanf(att_value, "%lf %lf %lf %lf", values[0], values[1], values[2], &dummy);//try to match one more... if it's matched then some error happened....
		if (nrFound != 3){
			vector<string> expected;
			expected.push_back("3 floats");
			string value(att_value);
			throw new LG_Parse_Exception_Wrong_Attribute_Value(&elem_name, &str_att_name, &value, &expected);
		}
	
	
	}
			


	/**

	 A method that tries to initialize a LG_Point3D with the values coming from an attribute.

	 In case some error occurs false is teturned and the array is filled with the value LG_INVALID_DOUBLE

	 */


	/**


	 Similar to point3DValue but last coordinate is set to zero, and a 2D point is expected.

	 */

	static inline bool point3DValueFromPoint2D(TiXmlAttribute *att, LG_Point3D & pointToFill){


		double dummy;

		int nrFound = sscanf(att->Value(), "%lf %lf %lf", &(pointToFill[0]), &(pointToFill[1]), &dummy);//try to match four... last one is supposed to never be filled in... if it is parsing didn't occur well, only 3D vectors allowed


		pointToFill[2] = 0.0;

		if (nrFound != LG_Point2D_Length){

			for (int i = 0; i < LG_Point3D_Length; i++)
				pointToFill[i] = LG_INVALID_DOUBLE;

			return false;

		}




		return true;


	}

	/**


	 Similar to point3DValue but last coordinate is set to zero, and a 2D point is expected.

	 */

	static inline bool point3DValueFromPoint2D_(const char *att, LG_Point3D & pointToFill){


		TiXmlAttribute attribute("dummy", att);

		return point3DValueFromPoint2D(&attribute, pointToFill);

	}


	static inline void isValidString(TiXmlElement *element, char *att_name, string &save){
		string elem_str_name(element->Value());
		string att_str_name(att_name);

		char *att_val = (char *)element->Attribute(att_name);
		if (!att_val)
			throw new LG_Parse_Exception_Missing_Attribute(&elem_str_name, &att_str_name);

		if (strcmp(att_val, "") == 0){
			string att_str_val(att_val);
			vector<string> expected;
			expected.push_back("not empty string");
			throw new LG_Parse_Exception_Wrong_Attribute_Value(&elem_str_name, &att_str_name, &att_str_val, &expected);
		}
		save.empty();
		save.append(att_val);
	}




};


#endif /* defined(__LAIG_Proj1__LG_Parsable_Node__) */
