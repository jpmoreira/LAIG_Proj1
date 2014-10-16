#include "LG_Camera.h"
#include "LG_Cameras_Container.h"

#include <GL/glut.h>

LG_Camera::LG_Camera(LG_Node_Map *map, TiXmlElement *element, string identifier) : LG_Parsable_Node(map, identifier)
{
	double_tryToAttributeVariable(LG_Camera_XML_ATT_NEAR, element, _near);
	double_tryToAttributeVariable(LG_Camera_XML_ATT_FAR, element, _far);
    

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




string LG_Camera::identifierForSuper(TiXmlElement *element){
	string identifier;
	string_tryToAttributeVariable(LG_Camera_XML_ATT_ID, element, identifier);

	return identifier;
}

/*

void LG_Camera::applyView(){
    
    glLoadIdentity();
    
    gluLookAt(0, 0, 0, 0, 0, -1, 0, 1, 0);
    
    
    
    
    // glTranslatef(0, 0, position[2]); // or this, if we ignore panning
    
    glRotatef(rotation[0], 1.f, 0.f, 0.f);
    glRotatef(rotation[1], 0.f, 1.f, 0.f);
    glRotatef(rotation[2], 0.f, 0.f, 1.f);
    
    
    glTranslatef(position[0],position[1], position[2]);
    //gluLookAt(0, 0, 0, 0, 0, 1, 0, 1, 0);
    //CGFcamera::applyView();
    
 
 
}

*/