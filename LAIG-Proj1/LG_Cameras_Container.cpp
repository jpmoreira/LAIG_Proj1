#include "LG_Cameras_Container.h"

//nr of childs > 1, and initial cam must exist
LG_Cameras_Container::LG_Cameras_Container(LG_Node_Map *map, TiXmlElement *element) : LG_Parsable_Node(map, LG_CAMERAS_TAG_ID)
{

	string_tryToAttributeVariable(LG_CAMERAS_ATT_INITIAL, element, initial);
	bool is_set_initial = false;

	LG_Camera_Ortho *tmp_ortho;
	LG_Camera_Perspective *tmp_perspective;


	TiXmlElement *sub_elem = element->FirstChildElement(LG_Camera_Perspective_XML_TAG_NAME);

	while (sub_elem)
	{
			tmp_perspective = new LG_Camera_Perspective(map, sub_elem);
			this->addChild(tmp_perspective->getId());

			if (str_eq(tmp_perspective->getId().c_str(), this->initial.c_str()))
				is_set_initial = true;
		
		sub_elem = sub_elem->NextSiblingElement(LG_Camera_Perspective_XML_TAG_NAME);
	}


	sub_elem = element->FirstChildElement(LG_Camera_Ortho_XML_TAG_NAME);

	while (sub_elem)
	{

		tmp_ortho = new LG_Camera_Ortho(map, sub_elem);
		this->addChild(tmp_ortho->getId());

		if (str_eq(tmp_ortho->getId().c_str(), this->initial.c_str()))
			is_set_initial = true;

		sub_elem = sub_elem->NextSiblingElement(LG_Camera_Ortho_XML_TAG_NAME);
	}

	if (!is_set_initial)
		throw new LG_Parse_Exception_Missing_Element("Initial Camera not found!");
}


string LG_Cameras_Container::getInitial()
{
	return this->initial;
}


LG_Cameras_Container::~LG_Cameras_Container()
{
}
