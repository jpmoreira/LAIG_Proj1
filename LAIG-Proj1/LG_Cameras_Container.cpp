#include "LG_Cameras_Container.h"

//nr of childs > 1, and initial cam must exist
LG_Cameras_Container::LG_Cameras_Container(LG_Node_Map *map, TiXmlElement *element) : LG_Parsable_Node(map, LG_CAMERAS_TAG_ID)
{

	verifyElementName(element);
	verifyAttributesAndValues(element);
			
}


void LG_Cameras_Container::verifyElementName(TiXmlElement *element)
{
	if (!str_eq(LG_CAMERAS_XML_TAG_NAME, element->Value()))
		throw new LG_Parse_Exception_Wrong_Element_Name(LG_CAMERAS_XML_TAG_NAME, element->Value());
}


void LG_Cameras_Container::verifyAttributesAndValues(TiXmlElement *element)
{
	string_tryToAttributeVariable(LG_CAMERAS_ATT_INITIAL, element, initial);

	bool initial_found_persp = setPerspectiveCams(element);
	bool initial_found_ortho = setOrthoCams(element);

	if (!initial_found_ortho && !initial_found_persp)	//sets cameras
		throw new LG_Parse_Exception_Missing_Element("Initial Camera not found!"); //if initial cam not found

}

bool LG_Cameras_Container::setPerspectiveCams(TiXmlElement *element)
{
	bool is_set_initial = false;

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

	return is_set_initial;
}


bool LG_Cameras_Container::setOrthoCams(TiXmlElement *element)
{
	bool is_set_initial = false;

	LG_Camera_Ortho *tmp_ortho;
	TiXmlElement *sub_elem = element->FirstChildElement(LG_Camera_Ortho_XML_TAG_NAME);

	while (sub_elem)
	{

		tmp_ortho = new LG_Camera_Ortho(map, sub_elem);
		this->addChild(tmp_ortho->getId());

		if (str_eq(tmp_ortho->getId().c_str(), this->initial.c_str()))
			is_set_initial = true;

		sub_elem = sub_elem->NextSiblingElement(LG_Camera_Ortho_XML_TAG_NAME);
	}

	return is_set_initial;
}

string LG_Cameras_Container::getInitial()
{
	return this->initial;
}


LG_Cameras_Container::~LG_Cameras_Container()
{
}


