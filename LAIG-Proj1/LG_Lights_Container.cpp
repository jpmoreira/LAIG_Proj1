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
		LG_Light_Omni *my_light_omni;
		LG_Light_Spot *my_light_spot;

		switch (my_type){
		
		case LG_LIGHT_OMNI:
			my_light_omni = new LG_Light_Omni(map, sub_elem);
			this->addChild(my_light_omni);
			break;

		case LG_LIGHT_SPOT:
			my_light_spot = new LG_Light_Spot(map, sub_elem);
			this->addChild(my_light_spot);
			break;
		}

		sub_elem = sub_elem->NextSiblingElement(LG_LIGHT_XML_TAG_NAME);
	}

}




LG_Lights_Container::~LG_Lights_Container()
{
}


void LG_Lights_Container::draw(){
	
	for (int i = 0; i < this->childsIDs.size(); i++)
	{
		string spot_id("spot1");
		auto it = map->find(spot_id);
		LG_Light_Spot *myspot = (LG_Light_Spot *)(it->second);
		myspot->draw();

	}
}