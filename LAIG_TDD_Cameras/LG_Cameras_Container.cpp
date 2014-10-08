#include "LG_Cameras_Container.h"

//nr of childs > 1, and initial cam must exist
LG_Cameras_Container::LG_Cameras_Container(LG_Node_Map *map, TiXmlElement *element) : LG_Parsable_Node(map, LG_CAMERAS_TAG_ID)
{

	string_tryToAttributeVariable(LG_CAMERAS_ATT_INITIAL, element, initial);
	bool is_set_initial;

	LG_Camera_Ortho *tmp_ortho;
	LG_Camera_Perspective *tmp_perspective;


	TiXmlElement *sub_elem = element->FirstChildElement(LG_Camera_Perspective_XML_TAG_NAME);

	while (sub_elem)
	{
		try
		{
			tmp_perspective = new LG_Camera_Perspective(map, sub_elem);
			this->addChild(tmp_perspective->getId());
		}
		catch (LG_Parse_Exception e)
		{
		}
		sub_elem->NextSiblingElement(LG_Camera_Perspective_XML_TAG_NAME);		
	}

	sub_elem = element->FirstChildElement(LG_Camera_Ortho_XML_TAG_NAME);
	
	while (sub_elem)
	{
		try
		{
			tmp_ortho = new LG_Camera_Ortho(map, sub_elem);
			this->addChild(tmp_ortho->getId());
		}
		catch (LG_Parse_Exception e)
		{
		}
		sub_elem->NextSiblingElement(LG_Camera_Ortho_XML_TAG_NAME);
	}
}


LG_Cameras_Container::~LG_Cameras_Container()
{
}
