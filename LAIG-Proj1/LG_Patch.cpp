#include "LG_Patch.h"


#define LG_Patch_ID_Prefix "_LG_Patch"


int LG_Patch::classIDNr = 0;

//Used by subclasses to get through unnecessary validations and attributes
LG_Patch::LG_Patch(LG_Node_Map *map, string LG_Primitive_Identifier) : LG_Primitive(map, LG_Primitive_Identifier){
	setTextCoords();
}


LG_Patch::LG_Patch(LG_Node_Map *map, TiXmlElement *elem) : LG_Primitive(map, autoIdentifier(LG_Patch_ID_Prefix, classIDNr)),
partsU(LG_INVALID_INT), partsV(LG_INVALID_INT), control_point_nr(0)
{

	string compute;
    
    
    evalElemName(LG_Patch_XML_Tag_Name, elem->Value());
    
    
    try {
        positiveInt_tryToAttributeVariable(LG_Patch_Att_Order, elem, orderU);
        orderV=orderU;
        
    } catch (LG_Parse_Exception_Missing_Attribute *ex) {
        
        positiveInt_tryToAttributeVariable(LG_Patch_Att_OrderU, elem, orderU);
        positiveInt_tryToAttributeVariable(LG_Patch_Att_OrderV, elem, orderV);
        
        
    }

	
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

	control_point_nr = (orderU + 1)*(orderV+1);
	points = new float[control_point_nr*LG_Point3D_Length];
	
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

    vstride=3*(orderU+1);
    
    
	setTextCoords();
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

	//glGet

	GLint frontface;
	glGetIntegerv(GL_FRONT_FACE, &frontface);

	glFrontFace(GL_CW);
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);


	glMap2f(GL_MAP2_VERTEX_3,
		0.0,//u start
		1.0,//u finish
		3,//ustride
		orderU + 1,
		0.0,//v start
		1.0,//v end
		vstride,//vstride
		orderV + 1,//
		(GLfloat *)points);

	
    glMap2f(GL_MAP2_TEXTURE_COORD_2,
		0.0,//u start
		1.0,//u finish
		2,//ustride
		2, //texture order
		0.0,//v start
		1.0,//v end
		4,//vstride
		2,//texture order
		(GLfloat *)textCoords);
	
    glEnable(GL_MAP2_TEXTURE_COORD_2);
	

	glMapGrid2f(partsU, 0, 1, partsV, 0, 1);
	glEvalMesh2(drawMode, 0, partsU, 0, partsV);

	glDisable(GL_MAP2_TEXTURE_COORD_2);
	glDisable(GL_MAP2_VERTEX_3);
	glDisable(GL_AUTO_NORMAL);
	glFrontFace(frontface);
}

void LG_Patch::calculateTextureCoordinates(){


}


void LG_Patch::setTextCoords(){
	textCoords = new float[8];

	//ustride 2 x coord
	//vstride 4 z coord
	textCoords[0] = 0;//1
	textCoords[1] = 1;//0

	textCoords[2] = 0;//1
	textCoords[3] = 0;//1

	textCoords[4] = 1;//0
	textCoords[5] = 1;//0

	textCoords[6] = 1;//0
	textCoords[7] = 0;//1
	//1,0
	//1,1
	//0,0
	//0,1
}