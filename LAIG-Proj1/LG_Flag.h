#pragma once
#include "LG_Plane.h"
#include <iostream>
#include "CGFshader.h"



#define LG_Flag_XML_Tag_Name "flag"
#define LG_Flag_Att_VertexShader "vsfile"
#define LG_Flag_Att_FragmentShader "fsfile"

using namespace std;


class LG_Flag :
	public LG_Plane, CGFshader
{
public:
	LG_Flag(LG_Node_Map *map, TiXmlElement *elem);
	~LG_Flag();
	void draw();
	void config();
	void calculateTextureCoordinates();
	
	virtual void bind(void);
	virtual void unbind(void);
	void setScale(float s);
	float normScale;

	/*exemplo*/
	CGFtexture * baseTexture;
	CGFtexture * secTexture;

	GLint baseImageLoc;
	GLint secImageLoc;

	GLint scaleLoc;




protected: 
	string vsfile_path, fsfile_path;
	bool verified;



private:
	static int classIDNr;
	double phase;
};

