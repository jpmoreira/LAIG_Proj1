#include "LG_Camera.h"


LG_Camera::LG_Camera(LG_Node_Map *map, TiXmlElement *element, string identifier) : LG_Parsable_Node(map, identifier)
{
	double_tryToAttributeVariable(LG_Camera_XML_ATT_NEAR, element, _near);
	double_tryToAttributeVariable(LG_Camera_XML_ATT_NEAR, element, _far);
	string_tryToAttributeVariable(LG_Camera_XML_ATT_ID, element, id);

}




LG_Camera::~LG_Camera()
{
}

double LG_Camera::getFar(){
	return _far;
}

double LG_Camera::getNear(){
	return _near;
}

string LG_Camera::getId(){
	return id;
}


string LG_Camera::identifierForSuper(TiXmlElement *element){
	string identifier;
	string_tryToAttributeVariable(LG_Camera_XML_ATT_ID, element, identifier);

	return identifier;
}