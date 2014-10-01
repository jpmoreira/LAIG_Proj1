#include "LG_Light_Omni.h"


#define _LG_Primitive_Name LG_Light_Omni_ID
#define LG_Light_Omni_ID "_LG_Light_Omni_"

int LG_Light_Omni::_LG_classIDNr = 0;


LG_Light_Omni::LG_Light_Omni(LG_Node_Map *map, TiXmlElement *element) :LG_Parsable_Node(map, autoIdentifier){
	
	string_tryToAttributeVariable(LG_OMNI_ATT_ID, element, id);
	bool_tryToAttributeVariable(LG_OMNI_ATT_ENABLED, element, enabled);
	bool_tryToAttributeVariable(LG_OMNI_ATT_MARKER, element, marker);
	point3D_tryToAttributeVariable(LG_OMNI_ATT_POS, element, pos);
	fillLightComponents(element);
}


LG_Light_Omni::~LG_Light_Omni()
{
}



void LG_Light_Omni::fillLightComponents(TiXmlElement *element){


	TiXmlElement *sub_elem;

	sub_elem = element->FirstChildElement(LG_OMNI_COMPONNENT_XML_TAG_NAME);

	//no access to LG_Parse_Exception_Missing_Element() ???
	/*if (!sub_elem)
		throw new LG_Parse_Exception_Missing_Element(new string(LG_COMPONNENT_XML_TAG_NAME));*/

	while (sub_elem)
	{
		char *comp_type = (char *)sub_elem->Attribute(LG_OMNI_COMPONNENT_ATT_TYPE);

		if (comp_type)
		{
			if (str_eq(LG_OMNI_COMPONNENT_AMBIENT_STR, comp_type))
				lightArray_tryToAttributeVariable(LG_OMNI_COMPONNENT_ATT_VALUE, sub_elem, componnents[LG_OMNI_COMPONNENT_AMBIENT]);
			
			else if (str_eq(LG_OMNI_COMPONNENT_DIFFUSE_STR, comp_type))
				lightArray_tryToAttributeVariable(LG_OMNI_COMPONNENT_ATT_VALUE, sub_elem, componnents[LG_OMNI_COMPONNENT_DIFFUSE]);
		
			else if (str_eq(LG_OMNI_COMPONNENT_SPECULAR_STR, comp_type))
				lightArray_tryToAttributeVariable(LG_OMNI_COMPONNENT_ATT_VALUE, sub_elem, componnents[LG_OMNI_COMPONNENT_SPECULAR]);
		}

		sub_elem = sub_elem->NextSiblingElement(LG_OMNI_COMPONNENT_XML_TAG_NAME);
	}
}