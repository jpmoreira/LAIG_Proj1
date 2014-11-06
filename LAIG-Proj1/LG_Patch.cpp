#include "LG_Patch.h"


#define LG_Patch_ID_Prefix "_LG_Patch"


int LG_Patch::classIDNr = 0;

LG_Patch::LG_Patch(LG_Node_Map *map, string LG_Primitive_Identifier) : LG_Primitive(map, LG_Primitive_Identifier){

}


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

	//experimental
	/*
	matrix = (float *)malloc(control_point_nr * sizeof(LG_Point3D_F));
	*/
	control_point_nr *= control_point_nr;
	points = new float[control_point_nr*LG_Point3D_Length];
	textCoords = new float[8];

		textCoords[0] = 0;
		textCoords[1] = 0;

		textCoords[2] = 1;
		textCoords[3] = 0;

		textCoords[4] = 0;
		textCoords[5] = 1;

		textCoords[6] = 1;
		textCoords[7] = 1;
	
	TiXmlElement *sub_elem;
	sub_elem = elem->FirstChildElement(LG_Patch_Elem_Controlpoint);

	unsigned int index = 0;
	while (sub_elem && index < control_point_nr)
	{
		fillControlpoint(sub_elem, index);

		sub_elem = sub_elem->NextSiblingElement();
	}

	if (index != control_point_nr)
		throw new LG_Parse_Exception_Wrong_Attribute_Value(new string(LG_Patch_Elem_Controlpoint), new string("Control Point"), 
		new string("Not enough control points"));

	if (order == 3)
		vstride = ORDER3_VSTRIDE;
	else if (order == 2)
		vstride = ORDER2_VSTRIDE;
	else vstride = ORDER1_VSTRIDE;
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

	points[index*LG_Point3D_Length + X_INDEX] = x;
	points[index*LG_Point3D_Length + Y_INDEX] = y;
	points[index*LG_Point3D_Length + Z_INDEX] = z;

	index++;
}


#pragma mark - Configuration
void LG_Patch::config(){



}


#pragma mark - Inherited Methods


void LG_Patch::draw(){

	glMap2f(GL_MAP2_VERTEX_3,
		0.0,//u start
		1.0,//u finish
		3,//ustride
		order + 1,
		0.0,//v start
		1.0,//v end
		vstride,//vstride
		order + 1,//
		(GLfloat *)points);

	if (LG_Appearance::currentTexture)
		glMap2f(GL_MAP2_TEXTURE_COORD_2,
			0.0,//u start
			LG_Appearance::currentTexture->getLength_s(),//u finish
			4,//ustride
			2, //texture order
			0.0,//v start
			LG_Appearance::currentTexture->getLength_t(),//v end
			2,//vstride
			2,//texture order
			(GLfloat *)textCoords);

	glEnable(GL_MAP2_VERTEX_3);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_MAP2_TEXTURE_COORD_2);

	glMapGrid2f(partsU, 0, 1, partsV, 0, 1);
	glEvalMesh2(drawMode, 0, partsU, 0, partsV);

	glDisable(GL_MAP2_TEXTURE_COORD_2);
	glDisable(GL_MAP2_VERTEX_3);
	glDisable(GL_AUTO_NORMAL);
}

void LG_Patch::calculateTextureCoordinates(){


}
