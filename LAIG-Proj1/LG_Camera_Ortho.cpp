#ifdef _WIN32
#include <Windows.h>
#endif

#include "LG_Camera_Ortho.h"




//string LG_Camera_Ortho::getIdentifier(){
//	return this->id;
//}

#ifdef _WIN32
//#define _USE_MATH_DEFINES // ->project settings-> c++ -> command line --> /D_USE_MATH_DEFINES 
#include <math.h>
#endif

LG_Camera_Ortho::LG_Camera_Ortho(LG_Node_Map *map, TiXmlElement *element) :LG_Camera(map, element, identifierForSuper(element))
{

	verifyElementName(element);
	verifyAttributesAndValues(element);




	position[0] = 0;
	position[1] = 0;
	position[2] = 0;


	LG_Point3D pt;
	pt[0] = 0;
	pt[1] = 0;
	pt[2] = 0;

	if (direction == LG_AXIS_X) pt[0] = 1;
	else if (direction == LG_AXIS_Y)pt[1] = 1;
	else if (direction == LG_AXIS_Z)pt[2] = 1;


	double angleY = atan(pt[0] / pt[2])*180. / M_PI;
	if (pt[2] == 0 && pt[0] > 0) {
		angleY = -90;
	}
	else if (pt[2] == 0 && pt[0] < 0){
		angleY = 90;
	}

	else if (pt[0] == 0 && pt[2] > 0){

		angleY = 180;
	}

	else if (pt[0] == 0){

		angleY = 0;
	}

	double h = sqrt(pt[0] * pt[0] + pt[2] * pt[2]);

	double angleX = atan(pt[1] / h)*180. / M_PI;





	rotation[1] = -angleY;
	rotation[0] = -angleX;
	rotation[2] = 0;




}


LG_Camera_Ortho::~LG_Camera_Ortho()
{
}

void LG_Camera_Ortho::verifyElementName(TiXmlElement *element){
	if (!str_eq(element->Value(), LG_Camera_Ortho_XML_TAG_NAME))
		throw LG_Parse_Exception_Wrong_Element_Name(new string(LG_Camera_Ortho_XML_TAG_NAME), new string(element->Value()));
}

void LG_Camera_Ortho::verifyAttributesAndValues(TiXmlElement *element){

	double_tryToAttributeVariable(LG_Camera_Ortho_XML_ATT_TOP, element, top);
	double_tryToAttributeVariable(LG_Camera_Ortho_XML_ATT_BOTTOM, element, bottom);
	double_tryToAttributeVariable(LG_Camera_Ortho_XML_ATT_LEFT, element, left);
	double_tryToAttributeVariable(LG_Camera_Ortho_XML_ATT_RIGHT, element, right);


	vector<string> options;
	options.push_back(LG_AXIS_X_STR);
	options.push_back(LG_AXIS_Y_STR);
	options.push_back(LG_AXIS_Z_STR);

	int tmp;
	enum_tryToAttribute(LG_Camera_Ortho_XML_ATT_DIRECTION, element, tmp, &options);

	direction = (LG_AXIS)tmp;

}


double LG_Camera_Ortho::getLeft()
{
	return this->left;
}

double LG_Camera_Ortho::getRight()
{
	return this->right;
}

double LG_Camera_Ortho::getTop()
{
	return this->top;
}

double LG_Camera_Ortho::getBottom()
{
	return this->bottom;
}

LG_AXIS LG_Camera_Ortho::getDirection()
{
	return this->direction;
}

#pragma mark - Inherited Methods


void LG_Camera_Ortho::applyView(){
        
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    if(direction == LG_AXIS_X)
    {
        gluLookAt(0.0, 0.0, 0.0, -1.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    }
    else if(direction == LG_AXIS_Y)
    {
        gluLookAt(0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 0.0, 0.0, 1.0);
    }
    else if(direction == LG_AXIS_Z)
    {
        gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);
    }
    
}


void LG_Camera_Ortho::updateProjectionMatrix(int width, int height)
{
	//float aspect= (float)width / (float)height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(left, right, bottom, top, _near, _far);
}