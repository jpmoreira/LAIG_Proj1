#pragma once
#include "LG_Primitive.h"


#define LG_Patch_XML_Tag_Name "patch"
#define LG_Patch_Att_PartsU "partsU"
#define LG_Patch_Att_PartsV "partsV"
#define LG_Patch_Att_Order "order"
#define LG_Patch_Att_OrderU "orderU"
#define LG_Patch_Att_OrderV "orderV"
#define LG_Patch_Att_Compute "compute"
#define LG_Patch_Elem_Controlpoint "controlpoint"
#define LG_Controlpoint_Att_X "x"
#define LG_Controlpoint_Att_Y "y"
#define LG_Controlpoint_Att_Z "z"

#define LG_Patch_Compute_Fill "fill"
#define LG_Patch_Compute_Line "line"
#define LG_Patch_Compute_Point "point"

#define X_INDEX 0
#define Y_INDEX 1
#define Z_INDEX 2


#define ORDER3_VSTRIDE 12
#define ORDER2_VSTRIDE 9
#define ORDER1_VSTRIDE 6

#define ORDER1_CURVE 1
#define ORDER2_CURVE 2
#define ORDER3_CURVE 3

class LG_Patch :
	public LG_Primitive
{
public:
	LG_Patch(LG_Node_Map *map, TiXmlElement *elem);
	LG_Patch(LG_Node_Map * map, string LG__Primitive_Identifier);
	~LG_Patch();
	void draw(bool selectMode);
	void config();
	void calculateTextureCoordinates();
	void setTextCoords();

protected:
	static int classIDNr;
	int orderU,orderV, partsU, partsV;
	float *points;
	float *textCoords;
	int control_point_nr, vstride;
	GLenum drawMode;
	void fillControlpoint(TiXmlElement *elem, unsigned int &index);
};

