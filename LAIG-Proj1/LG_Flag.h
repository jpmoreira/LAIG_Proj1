#pragma once
#include "LG_Plane.h"

#define LG_Flag_XML_Tag_Name "flag"

class LG_Flag :
	public LG_Plane
{
public:
	LG_Flag(LG_Node_Map *map, TiXmlElement *elem);
	~LG_Flag();
	void draw();
	void config();
	void calculateTextureCoordinates();
private: 
	static int classIDNr;
};

