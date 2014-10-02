#include "LG_Light_Spot.h"


#define _LG_Primitive_Name LG_Light_Spot_ID
#define LG_Light_Spot_ID "_LG_Light_Spot_"

int LG_Light_Spot::_LG_classIDNr = 0;

LG_Light_Spot::LG_Light_Spot(LG_Node_Map *map, TiXmlElement *element) :LG_Parsable_Node(map, autoIdentifier)
{
	string_tryToAttributeVariable(LG_SPOT_ATT_ID, element, id);
	bool_tryToAttributeVariable(LG_SPOT_ATT_ENABLED, element, enabled);
	bool_tryToAttributeVariable(LG_SPOT_ATT_MARKER, element, marker);
	point3D_tryToAttributeVariable(LG_SPOT_ATT_POS, element, pos);
	fillLightComponents(element);

	point3D_tryToAttributeVariable(LG_SPOT_ATT_TARGET, element, target);
	double_tryToAttributeVariable(LG_SPOT_ATT_ANGLE, element, angle);
	double_tryToAttributeVariable(LG_SPOT_ATT_EXPONENT, element, exponent);
}


LG_Light_Spot::~LG_Light_Spot()
{
}



void LG_Light_Spot::fillLightComponents(TiXmlElement *element){


	TiXmlElement *sub_elem;

	sub_elem = element->FirstChildElement(LG_SPOT_COMPONNENT_XML_TAG_NAME);

	//no access to LG_Parse_Exception_Missing_Element() ???
	/*if (!sub_elem)
	throw new LG_Parse_Exception_Missing_Element(new string(LG_COMPONNENT_XML_TAG_NAME));*/

	while (sub_elem)
	{
		char *comp_type = (char *)sub_elem->Attribute(LG_SPOT_COMPONNENT_ATT_TYPE);

		if (comp_type)
		{
			if (str_eq(LG_SPOT_COMPONNENT_AMBIENT_STR, comp_type))
				lightArray_tryToAttributeVariable(LG_SPOT_COMPONNENT_ATT_VALUE, sub_elem, componnents[LG_SPOT_COMPONNENT_AMBIENT]);

			else if (str_eq(LG_SPOT_COMPONNENT_DIFFUSE_STR, comp_type))
				lightArray_tryToAttributeVariable(LG_SPOT_COMPONNENT_ATT_VALUE, sub_elem, componnents[LG_SPOT_COMPONNENT_DIFFUSE]);

			else if (str_eq(LG_SPOT_COMPONNENT_SPECULAR_STR, comp_type))
				lightArray_tryToAttributeVariable(LG_SPOT_COMPONNENT_ATT_VALUE, sub_elem, componnents[LG_SPOT_COMPONNENT_SPECULAR]);
		}

		sub_elem = sub_elem->NextSiblingElement(LG_SPOT_COMPONNENT_XML_TAG_NAME);
	}
}