
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "LG_Flag.h"
#include "CGFapplication.h"

#define LG_Flag_ID_Prefix "_LG_Flag_"
#define LG_Plane_Parts_Default 50
#define LG_Flag_Frequency_default 1



int LG_Flag::classIDNr = 0;
int LG_Flag::wind = 1;



LG_Flag::LG_Flag(LG_Node_Map *map, TiXmlElement *elem) : LG_Plane(map, autoIdentifier(LG_Flag_ID_Prefix, classIDNr))
{

	has_sec_text = false;			//used to sign if there are more than 1texture assigned
	string texture1_path, texture2_path;	//textures path

    
    
    evalElemName(LG_Flag_XML_Tag_Name, elem->Value());
	//------------------------------------- Set Parts --------------------------------//
	
    try{
		//extra attribute
		positiveInt_tryToAttributeVariable(LG_Plane_parts_XML_Att_Name, elem, LG_Patch::partsV);
	}
	catch (LG_Parse_Exception *e){
		LG_Patch::partsV = LG_Plane_Parts_Default;
	}

	LG_Patch::partsU = LG_Patch::partsV;

	//------------------------------------- Set texture(s) --------------------------------//

	//base texture
	try{
		string_tryToAttributeVariable(LG_Flag_Att_Texture, elem, texture1_path);
	}
	catch (LG_Parse_Exception *e){
		texture1_path = "../data/terrainmap2.jpg";	//default texture if missing
	}

	//extra texture
	try{
		string_tryToAttributeVariable(LG_Flag_Att_Texture2, elem, texture2_path);
		has_sec_text = true;
	}
	catch (LG_Parse_Exception *e){}

	baseTexture = new CGFtexture(texture1_path.c_str());
	
	if (has_sec_text)
		secTexture = new CGFtexture(texture2_path.c_str());

	//------------------------------------ set shader files ------------------------------//

	//vertex shader file
	try{
		string_tryToAttributeVariable(LG_Flag_Att_VertexShader, elem, vsfile_path);
	}
	catch (LG_Parse_Exception *e){
		if (has_sec_text)
		{	//has a second texture
#ifdef _WIN32
			vsfile_path = "../data/fiftyfifty.vrs";
#else
			vsfile_path = "testFiles/fiftyfifty.vrs";
#endif 
		}
		else{//only one texture
#ifdef _WIN32
			vsfile_path = "../data/one_text.vrs";
#else
			vsfile_path = "testFiles/one_text.vrs";
#endif 
		}
	}



	//fragment shader file
	try{
		string_tryToAttributeVariable(LG_Flag_Att_FragmentShader, elem, fsfile_path);
	}
	catch (LG_Parse_Exception *e){
		if (has_sec_text)
		{
			//has a second texture
#ifdef _WIN32
			fsfile_path = "../data/fiftyfifty.frs";
#else
			fsfile_path = "testFiles/fiftyfifty.frs";
#endif 
		}
		else{
			//only has 1 texture
#ifdef _WIN32
			fsfile_path = "../data/one_text.frs";
#else
			fsfile_path = "testFiles/one_text.frs";
#endif 
		}
	}


	//------------------------------------ initialize shader ------------------------------//
	init(vsfile_path.c_str(), fsfile_path.c_str());


	CGFshader::bind();

	// Initialize parameter in memory
	normScale = 0.0;

	// Store Id for the uniform "normScale", new value will be stored on bind()
	scaleLoc = glGetUniformLocation(id(), "normScale");


	// get the uniform location for the sampler
	baseImageLoc = glGetUniformLocation(id(), "baseImage");

	// set the texture id for that sampler to match the GL_TEXTUREn that you 
	// will use later e.g. if using GL_TEXTURE0, set the uniform to 0
	glUniform1i(baseImageLoc, 0);

	if (has_sec_text)
	{

		// repeat if you use more textures in your shader(s)
		secImageLoc = glGetUniformLocation(id(), "secondImage");
		glUniform1i(secImageLoc, 1);

	}

	windLoc = glGetUniformLocation(id(), "wind");
	glUniform1i(windLoc, wind);

	CGFshader::unbind();
}


LG_Flag::~LG_Flag()
{
	LG_Plane::~LG_Plane();
}


#pragma mark - Configuration
void LG_Flag::config(){

}


#pragma mark - Inherited Methods


void LG_Flag::draw(){


	bind();

	LG_Patch::draw();

	unbind();

	if (LG_Appearance::currentTexture)
	{
		LG_Appearance::currentTexture->apply();
	}
}

void LG_Flag::calculateTextureCoordinates(){


}

void LG_Flag::bind()
{
	//std::cout << "Ticks" << CGFapplication::getTime() << endl;
	CGFshader::bind();
	// update uniforms
	CGFshader::update(my_time);

	glUniform1i(windLoc, wind);

	glUniform1f(scaleLoc, normScale);
	// make sure the correct texture unit is active
	glActiveTexture(GL_TEXTURE0);
	// apply/activate the texture you want, so that it is bound to GL_TEXTURE0
	baseTexture->apply();

	// do the same for other textures
	if (has_sec_text)
	{
		glActiveTexture(GL_TEXTURE1);

		secTexture->apply();

		glActiveTexture(GL_TEXTURE0);
	}

}

void LG_Flag::unbind(){
	CGFshader::unbind();
	if (LG_Appearance::currentTexture)
		LG_Appearance::currentTexture->apply();
}


void LG_Flag::update(unsigned long time){

	static unsigned long start = time;
	my_time = (float)((time - start) / 1000.0);
	//std::cout << d_time << std::endl;
}

int * LG_Flag::getWind(){
	return &wind;
}