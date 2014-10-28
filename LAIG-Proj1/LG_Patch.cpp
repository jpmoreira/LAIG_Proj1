#include "LG_Patch.h"


#define LG_Patch_ID_Prefix "_LG_Patch"


int LG_Patch::classIDNr = 0;
LG_Patch::LG_Patch(LG_Node_Map *map, TiXmlElement *elem) : LG_Primitive(map, autoIdentifier(LG_Patch_ID_Prefix, classIDNr)),
partsU(LG_INVALID_INT), partsV(LG_INVALID_INT), control_point_nr(0)
{

	string compute;

	if (!str_eq(elem->Value(), LG_Patch_XML_Tag_Name))
		throw new LG_Parse_Exception_Wrong_Element_Name(LG_Patch_XML_Tag_Name, elem->Value());
	
	
	positiveInt_tryToAttributeVariable(LG_Patch_Att_Order, elem, order);

	if (order <= 0 || order > 3)
		throw new LG_Parse_Exception_Wrong_Attribute_Value(elem->Value(), LG_Patch_Att_Order, "Invalid number");


	positiveInt_tryToAttributeVariable(LG_Patch_Att_PartsU, elem, partsU);
	positiveInt_tryToAttributeVariable(LG_Patch_Att_PartsV, elem, partsV);

	
	string_tryToAttributeVariable(LG_Patch_Att_Compute, elem, compute);
	if (str_eq(LG_Patch_Compute_Fill, compute))
		drawMode = GL_FILL;
	else if (str_eq(LG_Patch_Compute_Line, compute))
		drawMode = GL_LINE;
	else if (str_eq(LG_Patch_Compute_Point, compute))
		drawMode = GL_POINT;
	else
		throw new LG_Parse_Exception_Wrong_Attribute_Value(elem->Value(), LG_Patch_Att_Compute, compute.c_str());

	control_point_nr = order + 1;
	control_point_nr *= control_point_nr;

	TiXmlElement *sub_elem;
	sub_elem= elem->FirstChildElement(LG_Patch_Elem_Controlpoint);

	unsigned int index = 0;
	while (sub_elem)
	{
		fillControlpoint(sub_elem, index);

		sub_elem = sub_elem->NextSiblingElement();
	}

	
}


LG_Patch::~LG_Patch()
{
}


void LG_Patch::fillControlpoint(TiXmlElement *elem, unsigned int &index){
	
	if (!str_eq(elem->Value(), LG_Patch_Elem_Controlpoint))
		throw new LG_Parse_Exception_Wrong_Element_Name(LG_Patch_Elem_Controlpoint, elem->Value());
	float x, y, z;
	float_tryToAttributeVariable(LG_Controlpoint_Att_X, elem, x);
	float_tryToAttributeVariable(LG_Controlpoint_Att_Y, elem, y);
	float_tryToAttributeVariable(LG_Controlpoint_Att_Z, elem, z);

	points[index][X_INDEX] = x;
	points[index][Y_INDEX] = y;
	points[index][Z_INDEX] = z;
	index++;
}


#pragma mark - Configuration
void LG_Patch::config(){



}


#pragma mark - Inherited Methods


void LG_Patch::draw(){

	int vstride;
	if (order == 3)
		vstride = ORDER3_VSTRIDE;
	else if (order == 2)
		vstride = ORDER2_VSTRIDE;
	else vstride = ORDER1_VSTRIDE;



	glMap2d(GL_MAP2_VERTEX_3,
		0.0,//u start
		1.0,//u finish
		3,//ustride
		order,
		0.0,//v start
		1.0,//v end
		vstride,//vstride
		order,//1st degree curve
		(GLdouble *)points);

	glEnable(GL_MAP2_VERTEX_3);


	glMapGrid2d(partsU, 0, 1, partsV, 0, 1);

	
	glEvalMesh2(drawMode, 0, partsU, 0, partsV);

}

void LG_Patch::calculateTextureCoordinates(){


}
