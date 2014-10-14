#include "LG_Cameras_Container.h"

//nr of childs > 1, and initial cam must exist
LG_Cameras_Container::LG_Cameras_Container( TiXmlElement *element) : LG_Parsable_Node(NULL, LG_CAMERAS_TAG_ID)
{

    map=new LG_Node_Map();
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
    
    string initialID;
	string_tryToAttributeVariable(LG_CAMERAS_ATT_INITIAL, element, initialID);

	bool initial_found_persp = setPerspectiveCams(element,initialID);
	bool initial_found_ortho = setOrthoCams(element,initialID);

    if (!initial_found_ortho && !initial_found_persp){
    
         throw new LG_Parse_Exception_Broken_Reference(new string(LG_CAMERAS_XML_TAG_NAME), new string(initialID), new string(string(LG_Camera_Ortho_XML_TAG_NAME)+" or "+string(LG_Camera_Perspective_XML_TAG_NAME)));
    }	//sets cameras
    

    for (int i=0; i<childsIDs.size(); i++) {
        if (str_eq(childsIDs[i].c_str(),initialID.c_str())) {
            current=(LG_Camera *)child(i);
            break;
        }
    }

}

bool LG_Cameras_Container::setPerspectiveCams(TiXmlElement *element,string & initialID)
{
	bool is_set_initial = false;

	LG_Camera_Perspective *tmp_perspective;


	TiXmlElement *sub_elem = element->FirstChildElement(LG_Camera_Perspective_XML_TAG_NAME);

	while (sub_elem)
	{
		tmp_perspective = new LG_Camera_Perspective(map, sub_elem);
		this->addChild(tmp_perspective);

		if (str_eq(tmp_perspective->identifier.c_str(), initialID.c_str()))
			is_set_initial = true;

		sub_elem = sub_elem->NextSiblingElement(LG_Camera_Perspective_XML_TAG_NAME);
	}

	return is_set_initial;
}


bool LG_Cameras_Container::setOrthoCams(TiXmlElement *element,string & initialID)
{
	bool is_set_initial = false;

	LG_Camera_Ortho *tmp_ortho;
	TiXmlElement *sub_elem = element->FirstChildElement(LG_Camera_Ortho_XML_TAG_NAME);

	while (sub_elem)
	{

		tmp_ortho = new LG_Camera_Ortho(map, sub_elem);
		this->addChild(tmp_ortho);

		if (str_eq(tmp_ortho->identifier.c_str(), initialID.c_str()))
			is_set_initial = true;

		sub_elem = sub_elem->NextSiblingElement(LG_Camera_Ortho_XML_TAG_NAME);
	}

	return is_set_initial;
}

LG_Camera* LG_Cameras_Container::getCurrentCamera()
{
	return current;
}


LG_Cameras_Container::~LG_Cameras_Container()
{
}

