#pragma once
#include "LG_Plane.h"
#include <iostream>
#include "CGFshader.h"



#define LG_Flag_XML_Tag_Name "flag"
#define LG_Flag_Att_VertexShader "vsfile"
#define LG_Flag_Att_FragmentShader "fsfile"
#define LG_Flag_Att_Texture "texture"
#define LG_Flag_Att_Texture2 "texture2"

using namespace std;


class LG_Flag :
	public LG_Plane, CGFshader
{
public:
	LG_Flag(LG_Node_Map *map, TiXmlElement *elem);
	~LG_Flag();
	void draw(bool selectMode);
	void config();
	void calculateTextureCoordinates();
	
	virtual void bind(void);
	virtual void unbind(void);
	void setScale(float s);
	static int * getWind();

	float normScale;


	CGFtexture * baseTexture;
	CGFtexture * secTexture;

	GLint baseImageLoc;
	GLint secImageLoc;
	GLint scaleLoc; //normalScale
	GLint windLoc;

    void update(unsigned long time);



protected: 
	string vsfile_path, fsfile_path;




private:
	static int classIDNr, wind;
	float my_time;
	bool has_sec_text;
};

