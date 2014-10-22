


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
#include <GL/glu.h>

#include <limits.h>
#include <math.h>
#include <cfloat>
#include <vector>

using std::exception;

/*
#define autoIdentifier (string(_LG_Primitive_Name+std::to_string(_LG_classIDNr++)))
*/

#define LG_INVALID_INT INT_MAX
#define LG_INVALID_DOUBLE DBL_MAX //didn't use NaN because checking nan==nan always returns false
#define LG_INVALID_FLOAT FLT_MAX


typedef enum{

	LG_False,
	LG_True,
	LG_Invalid_Bool

} LG_BOOL;



static string autoIdentifier(string primitiveName,int &classIDNr){
	
    
    char temp[100];
    sprintf(temp,"%s%d",primitiveName.c_str(),classIDNr++);
    
    return string(temp);
}

#define LG_BOOL_STRING_TRUE "true"
#define LG_BOOL_STRING_FALSE "false"


class LG_Parse_Exception : exception{


protected:
	string* element;

public:
	LG_Parse_Exception(string* elem);
	LG_Parse_Exception();
	virtual const char* what() = 0;
	virtual ~LG_Parse_Exception();
    
    


};

class LG_Parse_Exception_Wrong_Attribute_Value :public LG_Parse_Exception{

private:
	string* attribute;
	string* actualValue;
	vector<string> *expectedValues;

public:


	//LG_Parse_Exception_Wrong_Attribute_Value(const char *elem,const char * att,const char *value,vector<string> *expected):LG_Parse_Exception_Wrong_Attribute_Value(new string(elem),new string(att),new string(value),expected){}
	LG_Parse_Exception_Wrong_Attribute_Value(string *elem, string* attrib, string* value, vector<string> *expected);
	/**


	 This method expects the caller to manage char *.

	 */
	LG_Parse_Exception_Wrong_Attribute_Value(const char *elem, const char * att, const char *value, vector<string> *expected);


	LG_Parse_Exception_Wrong_Attribute_Value(string *elem, string* attrib, string* value);
	/**


	 This method expects the caller to manage char *.

	 */
	LG_Parse_Exception_Wrong_Attribute_Value(const char *elem, const char* attrib, const char* value);
	~LG_Parse_Exception_Wrong_Attribute_Value();
	const char* what();




};






class LG_Parse_Exception_Missing_Attribute :public LG_Parse_Exception{
private:
	string* missingAttribute;

public:
	LG_Parse_Exception_Missing_Attribute(string *elementName, string * missingAtt);
	LG_Parse_Exception_Missing_Attribute(char *elementName, char * missingAtt);

	const char * what();

	~LG_Parse_Exception_Missing_Attribute();


};



class LG_Parse_Exception_Wrong_Element_Name :public LG_Parse_Exception{

public:
	LG_Parse_Exception_Wrong_Element_Name(string * expectedElementName, string * actualElementName);

	/**


	 This method expects the caller to manage char *.

	 */
	LG_Parse_Exception_Wrong_Element_Name(const char * expectedElementName, const char * actualElementName);

	~LG_Parse_Exception_Wrong_Element_Name();

	const char * what();

private:
	string *expectedElementName;

};


class LG_Parse_Exception_Missing_Element :public LG_Parse_Exception{


public:
	LG_Parse_Exception_Missing_Element(string *elem);

	/**

	 Method not responsible for managing the recieved parameter memory

	 */
	LG_Parse_Exception_Missing_Element(const char *elem);

	const char * what();

};


class LG_Parse_Exception_Broken_Reference :public LG_Parse_Exception{

private:
	string *reference;
	string *refered_Type;




public:

	const char * what();
	LG_Parse_Exception_Broken_Reference(string * elementWhereErrorOccured, string * reference, string *referedElementName);
	LG_Parse_Exception_Broken_Reference(const char * elementWhereErrorOccured, const char * reference, const char *referedElementName);
	~LG_Parse_Exception_Broken_Reference();

};

class LG_Parse_Exception_Redundant_Reference :public LG_Parse_Exception{


public:

	LG_Parse_Exception_Redundant_Reference(string *element);
	LG_Parse_Exception_Redundant_Reference(const char *element);


	const char * what();


};

class LG_Parsable_Node : public LG_Node{

public:
	/**


	 Simple Constructor, that simply calls the superclass constructor with the same parameters

	 */

	LG_Parsable_Node(LG_Node_Map *map, string identif);


public:






	static void inline copyLightArrays(LG_LightArray source, LG_LightArray dest){

		for (int i = 0; i < LG_LightArray_Lenght; i++) {
			dest[i] = source[i];
		}

	}

	static void inline copyLightArrays_f(LG_LightArray_f source, LG_LightArray_f dest){

		for (int i = 0; i < LG_LightArray_Lenght; i++) {
			dest[i] = source[i];
		}

	}

	/**

	 A method that tries to attribute a particular attribute to an int variable.
	 Throws the appropriate exception in case something wrong happens.
	 @param attName the name of the attribute to be set. To be used in the thrown exception.
	 @param elem the element whose attribute is to be used
	 @param parameter the variable to be set.



	 */

	static void inline positiveInt_tryToAttributeVariable(const char * attName, TiXmlElement* elem, int&parameter){

		const char *source = elem->Attribute(attName);
		const char *elemName = elem->Value();

		if (source == NULL){
			throw new LG_Parse_Exception_Missing_Attribute(new string(elemName), new string(attName));
		}

		parameter = positiveIntValueForAttribute_(source);

		if (parameter == LG_INVALID_INT)
			throw new LG_Parse_Exception_Wrong_Attribute_Value(new string(elemName), new string(attName), new string(source));

	}



	/**

	 A method that tries to attribute a particular attribute to a double variable.
	 The double value must not be negative.




	 */
	static void inline nonNegativeDouble_tryToAttributeVariable(const char * attName, TiXmlElement *elem, double &parameter){


		const char * source = elem->Attribute(attName);
		const char * elemName = elem->Value();

		if (source == NULL){
			throw new LG_Parse_Exception_Missing_Attribute(new string(elemName), new string(attName));
		}

		parameter = doubleValueForAttribute_(source);


		if (parameter < 0.0)parameter = LG_INVALID_DOUBLE;//dont allow negative values but allow zero

		if (parameter == LG_INVALID_DOUBLE)
			throw new LG_Parse_Exception_Wrong_Attribute_Value(new string(elemName), new string(attName), new string(source));




	}

	/**

	 A method that tries to attribute a particular attribute to a double variable.
	 Throws the appropriate exception in case something wrong happens.
	 @param attName the name of the attribute to be set. To be used in the thrown exception.
	 @param elem the element whose whose attribute is to be used
	 @param parameter the variable to be set.



	 */

	static void inline positiveDouble_tryToAttributeVariable(const char * attName, TiXmlElement* elem, double&parameter){


		const char * source = elem->Attribute(attName);
		const char * elemName = elem->Value();

		if (source == NULL){
			throw new LG_Parse_Exception_Missing_Attribute(new string(elemName), new string(attName));
		}

		parameter = positiveDoubleValueForAttribute_(source);

		if (parameter == LG_INVALID_DOUBLE)
			throw new LG_Parse_Exception_Wrong_Attribute_Value(new string(elemName), new string(attName), new string(source));


	}


	/**

	 A method that tries to attribute a particular attribute to a double variable.
	 Throws the appropriate exception in case something wrong happens.
	 @param attName the name of the attribute to be set. To be used in the thrown exception.
	 @param elem the element whose whose attribute is to be used
	 @param parameter the variable to be set.



	 */

	static void inline positiveFloat_tryToAttributeVariable(const char * attName, TiXmlElement* elem, float&parameter){


		const char * source = elem->Attribute(attName);
		const char * elemName = elem->Value();

		double temp;

		if (source == NULL){
			throw new LG_Parse_Exception_Missing_Attribute(new string(elemName), new string(attName));
		}

		temp = positiveDoubleValueForAttribute_(source);
		parameter = (float)temp;

		if (temp == LG_INVALID_DOUBLE){
			parameter = LG_INVALID_FLOAT;
			throw new LG_Parse_Exception_Wrong_Attribute_Value(new string(elemName), new string(attName), new string(source));
		}



	}

	/**

	 A method that tries to attribute a particular attribute to a double variable.
	 Throws the appropriate exception in case something wrong happens.
	 @param attName the name of the attribute to be set. To be used in the thrown exception.
	 @param elem the element whose whose attribute is to be used
	 @param parameter the variable to be set.



	 */

	static void inline double_tryToAttributeVariable(const char * attName, TiXmlElement* elem, double&parameter){


		const char * source = elem->Attribute(attName);
		const char * elemName = elem->Value();

		if (source == NULL){
			throw new LG_Parse_Exception_Missing_Attribute(new string(elemName), new string(attName));
		}

		parameter = doubleValueForAttribute_(source);

		if (parameter == LG_INVALID_DOUBLE)
			throw new LG_Parse_Exception_Wrong_Attribute_Value(new string(elemName), new string(attName), new string(source));


	}




	static void inline float_tryToAttributeVariable(const char * attName, TiXmlElement* elem, float&parameter){


		const char * source = elem->Attribute(attName);
		const char * elemName = elem->Value();

		if (source == NULL){
			throw new LG_Parse_Exception_Missing_Attribute(new string(elemName), new string(attName));
		}

		parameter = (float)doubleValueForAttribute_(source);

		if (parameter == LG_INVALID_DOUBLE)
			throw new LG_Parse_Exception_Wrong_Attribute_Value(new string(elemName), new string(attName), new string(source));


	}



	/**

	 A method that tries to attribute a particular attribute to a bool variable.
	 Throws the appropriate exception in case something wrong happens.
	 @param attName the name of the attribute to be set. To be used in the thrown exception.
	 @param elem the element whose variable is to be set
	 @param parameter the variable to be set.



	 */

	static void inline bool_tryToAttributeVariable(const char * attName, TiXmlElement* elem, bool&parameter){


		const char * elemName = elem->Value();
		const char * source = elem->Attribute(attName);

		LG_BOOL tmp;
		if (source == NULL){
			throw new LG_Parse_Exception_Missing_Attribute(new string(elemName), new string(attName));
		}

		tmp = boolValueForAttribute_(source);

		if (tmp == LG_Invalid_Bool)
			throw new LG_Parse_Exception_Wrong_Attribute_Value(new string(elemName), new string(attName), new string(source));


		if (tmp == LG_True)
			parameter = true;
		else
			parameter = false;

	}




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

	 A method that tries to initialize a LG_Point3D with the values coming from an attribute.

	 In case some error occurs false is teturned and the array is filled with the value LG_INVALID_DOUBLE

	 */


	static inline bool point3DValue_(const char *att, LG_Point3D & pointToFill){


		TiXmlAttribute attribute("dummy", att);

		return point3DValue(&attribute, pointToFill);


	}


	static inline bool point3D_FValue_(const char *att, LG_Point3D_F & pointToFill){


		TiXmlAttribute attribute("dummy", att);

		return point3D_FValue(&attribute, pointToFill);


	}


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

	 A method that tries to initialize a lightArray with the elements coming from an attribute.
	 In case some error occurs false is returned and the array is filled with the value LG_LightValue_Not_Set
	 */

	static inline bool lightArrayValue_f_(const char  *att, LG_LightArray_f& lightArrayToFill){

		float dummy;

		int nrFound = sscanf(att, "%f %f %f %f %f", &(lightArrayToFill[0]), &(lightArrayToFill[1]), &(lightArrayToFill[2]), &(lightArrayToFill[3]), &dummy);//try to match one more... if it's matched then some error happened....

		if (nrFound != 4){

			for (int i = 0; i < LG_LightArray_Lenght; i++)
				lightArrayToFill[i] = LG_LightValue_f_Not_Set;
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




	static inline bool point3D_FValue(TiXmlAttribute *att, LG_Point3D_F & pointToFill){


		double dummy;

		int nrFound = sscanf(att->Value(), "%f %f %f  %f", &(pointToFill[0]), &(pointToFill[1]), &(pointToFill[2]), &dummy);//try to match four... last one is supposed to never be filled in... if it is parsing didn't occur well, only 3D vectors allowed

		if (nrFound != LG_Point3D_Length){

			for (int i = 0; i < LG_Point3D_Length; i++)
				pointToFill[i] = LG_INVALID_FLOAT;

			return false;

		}
		return true;

	}
	/**

	 A method that tries to initialize a LG_Point3D with the values coming from an attribute.

	 In case some error occurs false is teturned and the array is filled with the value LG_INVALID_DOUBLE

	 */

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


	/**

	 A method that tries to attribute a particular attribute to a LG_LightArray variable.
	 Throws the appropriate exception in case something wrong happens.
	 In case of an
	 @param att_name the name of the attribute to be set. To be used in the thrown exception.
	 @param element element to whom the attribute belongs to.
	 @param values the variable to be set.

	 */


	static inline void point3D_tryToAttributeVariable(const char * att_name, TiXmlElement *element, LG_Point3D & values){


		char *att_value = (char *)element->Attribute(att_name);

		if (!att_value)
			throw  new LG_Parse_Exception_Missing_Attribute(new string(element->Value()), new string(att_name));


		bool ok = point3DValue_(att_value, values);

		if (!ok){
			throw new LG_Parse_Exception_Wrong_Attribute_Value(new string(element->Value()), new string(att_name), new string(att_value));
		}


	}




	static inline void point3D_F_tryToAttributeVariable(const char * att_name, TiXmlElement *element, LG_Point3D_F & values){


		char *att_value = (char *)element->Attribute(att_name);

		if (!att_value)
			throw  new LG_Parse_Exception_Missing_Attribute(new string(element->Value()), new string(att_name));


		bool ok = point3D_FValue_(att_value, values);

		if (!ok){
			throw new LG_Parse_Exception_Wrong_Attribute_Value(new string(element->Value()), new string(att_name), new string(att_value));
		}


	}



	/**

	 A method that tries to attribute a particular attribute to a LG_point3D variable, when the attribute only defines a 2D point. The point is set to z=0
	 Throws the appropriate exception in case something wrong happens.
	 In case of an
	 @param att_name the name of the attribute to be set. To be used in the thrown exception.
	 @param element element to whom the attribute belongs to.
	 @param values the variable to be set.

	 */

	static inline void point3DFrom2D_tryToAttributeVariable(const char * att_name, TiXmlElement *element, LG_Point3D & values){


		char *att_value = (char *)element->Attribute(att_name);

		if (!att_value)
			throw  new LG_Parse_Exception_Missing_Attribute(new string(element->Value()), new string(att_name));


		bool ok = point3DValueFromPoint2D_(att_value, values);

		if (!ok){
			throw new LG_Parse_Exception_Wrong_Attribute_Value(new string(element->Value()), new string(att_name), new string(att_value));
		}


	}

	/**

	 A method that tries to attribute a particular attribute to a LG_LightArray variable.
	 Throws the appropriate exception in case something wrong happens.
	 In case of an
	 @param att_name the name of the attribute to be set. To be used in the thrown exception.
	 @param element element to whom the attribute belongs to.
	 @param values the variable to be set.

	 */

	static inline void lightArray_tryToAttributeVariable(const char * att_name, TiXmlElement *element, LG_LightArray & values){


		char *att_value = (char *)element->Attribute(att_name);

		if (!att_value)
			throw  new LG_Parse_Exception_Missing_Attribute(new string(element->Value()), new string(att_name));


		bool ok = lightArrayValue_(att_value, values);

		if (!ok){
			throw new LG_Parse_Exception_Wrong_Attribute_Value(new string(element->Value()), new string(att_name), new string(att_value));
		}


	}

	/**

	 A method that tries to attribute a particular attribute to a LG_LightArray variable.
	 Throws the appropriate exception in case something wrong happens.
	 In case of an
	 @param att_name the name of the attribute to be set. To be used in the thrown exception.
	 @param element element to whom the attribute belongs to.
	 @param values the variable to be set.

	 */

	static inline void lightArray_f_tryToAttributeVariable(const char * att_name, TiXmlElement *element, LG_LightArray_f & values){


		char *att_value = (char *)element->Attribute(att_name);

		if (!att_value)
			throw  new LG_Parse_Exception_Missing_Attribute(new string(element->Value()), new string(att_name));


		bool ok = lightArrayValue_f_(att_value, values);

		if (!ok){
			throw new LG_Parse_Exception_Wrong_Attribute_Value(new string(element->Value()), new string(att_name), new string(att_value));
		}


	}

	/**

	 A method that tries to attribute a particular attribute to a string variable.
	 Throws the appropriate exception in case something wrong happens.
	 In case of an
	 @param att_name the name of the attribute to be set. To be used in the thrown exception.
	 @param element element to whom the attribute belongs to.
	 @param save the variable to be set.

	 */

	static inline void string_tryToAttributeVariable(const char *att_name, TiXmlElement *element, string &save){
		string att_str_name(att_name);

		char *att_val = (char *)element->Attribute(att_name);
		if (!att_val)
			throw new LG_Parse_Exception_Missing_Attribute(new string(element->Value()), new string(att_name));

		if (strcmp(att_val, "") == 0){
			throw new LG_Parse_Exception_Wrong_Attribute_Value(new string(element->Value()), new string(att_val), new string(att_val));
		}
		save.clear();
		save.append(att_val);
	}



	/**

	A method that tries to attribute a particular attribute to a string variable.
	Throws the appropriate exception in case something wrong happens.
	In case of an
	@param att_name the name of the attribute to be set. To be used in the thrown exception.
	@param element element to whom the attribute belongs to.
	@param save the variable to be set.

	*/
	static inline void char_tryToAttributeVariable(char *att_name, TiXmlElement *element, char &save){


		double dummy;
		char *att = (char *)element->Attribute(att_name);
		if (!att)
			throw new LG_Parse_Exception_Missing_Attribute(new string(element->Value()), new string(att_name));
		int nrFound = sscanf(att, "%c %lf", &save, &dummy);//try to match one more... if it's matched then some error happened....

		if (nrFound != 1)
			throw new LG_Parse_Exception_Wrong_Attribute_Value(new string(element->Value()), new string(att_name), new string(att));

	}

	/**

	 A method that tries to attribute a particular attribute to a string variable.
	 Throws the appropriate exception in case something wrong happens.
	 In case of an
	 @param att_name the name of the attribute to be set. To be used in the thrown exception.
	 @param element element to whom the attribute belongs to.
	 @param save the variable to be set.
	 @param possibleValues all the possible values accepted as a valid value for the string

	 */
	static inline void enum_tryToAttribute(const char *att_name, TiXmlElement *element, int &save, vector<string> *possibleValues){


		string att_str_name(att_name);

		char *att_val = (char *)element->Attribute(att_name);
		if (!att_val)
			throw new LG_Parse_Exception_Missing_Attribute(new string(element->Value()), new string(att_name));

		if (strcmp(att_val, "") == 0){
			throw new LG_Parse_Exception_Wrong_Attribute_Value(new string(element->Value()), new string(att_val), new string(att_val), possibleValues);
		}


		bool isEqualToOnePossibility = false;

		for (unsigned int i = 0; i < possibleValues->size(); i++) {

			if (str_eq(att_val, possibleValues->at(i).c_str())){

				save = i;
				isEqualToOnePossibility = true;
				break;
			}

		}


		if (!isEqualToOnePossibility)throw new LG_Parse_Exception_Wrong_Attribute_Value(new string(element->Value()), new string(att_str_name), new string(att_val), possibleValues);



	}





};


#endif /* defined(__LAIG_Proj1__LG_Parsable_Node__) */
