#include "LG_Lights_Container.h"



LG_Lights_Container::LG_Lights_Container(LG_Node_Map *map, TiXmlElement *element) : LG_Parsable_Node(map, LG_LIGHTS_CONTAINER_ID)
{

	if (element == NULL)
		throw new LG_Parse_Exception_Missing_Element(LG_LIGHT_XML_TAG_NAME);

		if (!str_eq(LG_LIGHTS_XML_TAG_NAME, element->Value()))
			throw new LG_Parse_Exception_Wrong_Element_Name(new string(LG_LIGHT_XML_TAG_NAME), new string(element->Value()));

	TiXmlElement *sub_elem = element->FirstChildElement(LG_LIGHT_XML_TAG_NAME);
	while (sub_elem != NULL)
	{

		LG_LIGHT_TYPE my_type = LG_Light::myLightType(sub_elem);
        LG_Light *light;

		switch (my_type){
		
		case LG_LIGHT_OMNI:
			light = new LG_Light_Omni(map, sub_elem);
			break;

		case LG_LIGHT_SPOT:
			light = new LG_Light_Spot(map, sub_elem);
			break;
		}
        
        this->addChild(light);

		sub_elem = sub_elem->NextSiblingElement(LG_LIGHT_XML_TAG_NAME);
	}

}




LG_Lights_Container::~LG_Lights_Container()
{
}
