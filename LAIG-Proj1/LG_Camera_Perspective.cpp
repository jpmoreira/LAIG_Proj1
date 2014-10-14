#include "LG_Camera_Perspective.h"
//#include "coordinateSystems.h"

#include <GL/glut.h>

#ifdef _WIN32
//#define _USE_MATH_DEFINES // ->project settings-> c++ -> command line --> /D_USE_MATH_DEFINES 
#include <math.h>
#endif

//passing LG_Camera_Perspective_Node_ID won't work, ID must be unique and there may be more than one perspective
LG_Camera_Perspective::LG_Camera_Perspective(LG_Node_Map *map, TiXmlElement *element) :LG_Camera(map, element, identifierForSuper(element))
{
	verifyElementName(element);
	verifyAttributesAndValues(element);


	position[0] = -pos[0];
	position[1] = -pos[1];
	position[2] = -pos[2];


	LG_Point3D pt;

	pt[0] = target[0] - pos[0];
	pt[1] = target[1] - pos[1];
	pt[2] = target[2] - pos[2];

	double angleY = atan(pt[0] / pt[2])*180. / M_PI;
	if (pt[2] == 0 && pt[0] > 0) {
		angleY = -90;
	}
	else if (pt[2] == 0){
		angleY = 90;
	}

	double h = sqrt(pt[0] * pt[0] + pt[2] * pt[2]);

	double angleX = atan(pt[1] / h)*180. / M_PI;





	rotation[1] = -angleY;
	rotation[0] = -angleX;
	rotation[2] = 0;







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


	float aspect = (float)width / (float)height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(angle, aspect, _near, _far);

}



