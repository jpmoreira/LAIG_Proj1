#include "LG_Camera_Perspective.h"
#include "coordinateSystems.h"

#include <GL/glut.h>

//passing LG_Camera_Perspective_Node_ID won't work, ID must be unique and there may be more than one perspective
LG_Camera_Perspective::LG_Camera_Perspective(LG_Node_Map *map, TiXmlElement *element) :LG_Camera(map, element, identifierForSuper(element))
{
	verifyElementName(element);
	verifyAttributesAndValues(element);
    
    
    position[0]=0;
    position[1]=0;
    position[2]=0;
    
    
    
    
    
    

}


LG_Camera_Perspective::~LG_Camera_Perspective()
{
}



void LG_Camera_Perspective::verifyElementName(TiXmlElement *element){

	if (!str_eq(element->Value(), LG_Camera_Perspective_XML_TAG_NAME)){
		throw new LG_Parse_Exception_Wrong_Element_Name(new string(LG_Camera_Perspective_XML_TAG_NAME), new string(element->Value()));
	}
}

void LG_Camera_Perspective::verifyAttributesAndValues(TiXmlElement *element){

	positiveDouble_tryToAttributeVariable(LG_Camera_Perspective_XML_ATT_ANGLE, element, angle);
	point3D_tryToAttributeVariable(LG_Camera_Perspective_XML_ATT_POS, element, pos);
	point3D_tryToAttributeVariable(LG_Camera_Perspective_XML_ATT_TARGET, element, target);
}


double LG_Camera_Perspective::getAngle()
{
	return this->angle;
}

const LG_Point3D *LG_Camera_Perspective::getPos()
{
	return &this->pos;
}

const LG_Point3D *LG_Camera_Perspective::getTarget()
{
	return &this->target;
}


#pragma mark - Inherited methods


void LG_Camera_Perspective::updateProjectionMatrix(int width, int height){

    
    float aspect= (float)width / (float)height;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluPerspective(angle, aspect, _near, _far);
    
}


void LG_Camera_Perspective::applyView(){


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    

    
    glRotatef(rotation[0], 1.f, 0.f, 0.f);
    glRotatef(rotation[1], 0.f, 1.f, 0.f);
    glRotatef(rotation[2], 0.f, 0.f, 1.f);
    
    gluLookAt(pos[0], pos[1], pos[2], target[0], target[1], target[2], 0, 1, 0);

    
    
    glTranslated(position[0], position[1], position[2]);
}



bool LG_Camera_Perspective::moveTo(int axis, float value, float increment)
{
    if (axis!=CG_CGFcamera_AXIS_X && axis!=CG_CGFcamera_AXIS_Y && axis!=CG_CGFcamera_AXIS_Z) return false;
    
    if(position[axis] < value)
    {
        position[axis] += increment;
        //target[axis]+=increment;
        return false;
    }
    return true;
}

bool LG_Camera_Perspective::translate(int axis, float value)
{
    if (axis!=CG_CGFcamera_AXIS_X && axis!=CG_CGFcamera_AXIS_Y && axis!=CG_CGFcamera_AXIS_Z) return false;
    
    position[axis] += value;
    
    
    
    return true;
}



