#include "LG_Flag.h"

#define LG_Flag_ID_Prefix "_LG_Flag_"
#define LG_Plane_Parts_Default 5

int LG_Flag::classIDNr = 0;

LG_Flag::LG_Flag(LG_Node_Map *map, TiXmlElement *elem) : LG_Plane(map, autoIdentifier(LG_Flag_ID_Prefix, classIDNr))
{

	try{
		positiveInt_tryToAttributeVariable(LG_Plane_parts_XML_Att_Name, elem, parts);
	}
	catch (LG_Parse_Exception *e){
		parts = LG_Plane_Parts_Default;
	}

	if (!str_eq(elem->Value(), LG_Flag_XML_Tag_Name)) {

		throw LG_Parse_Exception_Wrong_Element_Name(LG_Flag_XML_Tag_Name, elem->Value());
	}

	textCoords = new float[8];

	textCoords[0] = 0;
	textCoords[1] = 0;

	textCoords[2] = 1;
	textCoords[3] = 0;

	textCoords[4] = 0;
	textCoords[5] = 1;

	textCoords[6] = 1;
	textCoords[7] = 1;

}


LG_Flag::~LG_Flag()
{
}


#pragma mark - Configuration
void LG_Flag::config(){



}


#pragma mark - Inherited Methods


void LG_Flag::draw(){


	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);

	glMap2f(GL_MAP2_VERTEX_3,
		0,//u start
		1.0,//u finish
		3,//ustride
		2,//1st degree curve
		0,//v start
		1.0,//v end
		6,//vstride
		2,//1st degree curve
		(GLfloat *)LG_Plane::points);


	if (LG_Appearance::currentTexture){
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

		glEnable(GL_MAP2_TEXTURE_COORD_2);
	}





	GLint drawMode[2];
	glGetIntegerv(GL_POLYGON_MODE, drawMode);

	glMapGrid2f(parts, 0, 1, parts, 0, 1);
	glEvalMesh2(drawMode[0], 0, parts, 0, parts);

	glDisable(GL_MAP2_TEXTURE_COORD_2);
	glDisable(GL_MAP2_VERTEX_3);
	glDisable(GL_AUTO_NORMAL);
}

void LG_Flag::calculateTextureCoordinates(){


}
