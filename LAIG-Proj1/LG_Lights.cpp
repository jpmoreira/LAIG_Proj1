#include "LG_Lights.h"

LG_Lights::LG_Lights(LG_Node_Map *map, TiXmlElement *element):LG_Parsable_Node(map, _LG_LIGHTS_NODE_ID){
	if (!str_eq(LG_LIGHTS_XML_TAG_NAME, element->Value()))
		throw new LG_Parse_Exception_Wrong_Element_Name(new string(LG_LIGHTS_XML_TAG_NAME), new string(element->Value()));

	int count = 0;
	TiXmlElement *sub_elem = element->FirstChildElement(LG_LIGHT_XML_TAG_NAME);
	string type;

	while (sub_elem){
		try
		{
			string_tryToAttributeVariable(LG_LIGHT_ATT_TYPE, sub_elem, type);
			if (str_eq(type.c_str(), LG_LIGHT_TYPE_OMNI)){
				//LG_Light_Omni omni = new LG_Light_Omni(...);
				count++;
			}
			else if (str_eq(type.c_str(), LG_LIGHT_TYPE_SPOT)){
				//LG_Light_Spot omni = new LG_Light_Spot(...);
				count++;
			}
			else throw new LG_Parse_Exception_Wrong_Attribute_Value(new string(sub_elem->Value()), new string(LG_LIGHT_ATT_TYPE), new string(type));

		}
		catch (LG_Parse_Exception_Missing_Element *mE){}
		catch (LG_Parse_Exception_Missing_Attribute *mA){}
		catch (LG_Parse_Exception_Wrong_Attribute_Value *wAV){}

		sub_elem = sub_elem->NextSiblingElement(LG_LIGHT_XML_TAG_NAME);
	}

	if (count == 0)
		count = 0; //remove this, missing element throw exception is's working. Uncomment line below. 
		//throw new LG_Parse_Exception_Missing_Element(new string(LG_LIGHT_XML_TAG_NAME));

}


LG_Lights::~LG_Lights()
{
}
