
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "LG_Flag.h"
#include "CGFapplication.h"
#include <chrono>
#define LG_Flag_ID_Prefix "_LG_Flag_"
#define LG_Plane_Parts_Default 50
#define LG_Flag_Frequency_default 1



/*
1. Create a shader object.
2. Compile your shader source into the object.
3. Verify that your shader successfully compiled.

Then, to link multiple shader objects into a shader program, you’ll:
1. Create a shader program.
2. Attach the appropriate shader objects to the shader program.
3. Link the shader program.
4. Verify that the shader link phase completed successfully.
5. Use the shader for vertex or fragment processing.
*/


int LG_Flag::classIDNr = 0;
int LG_Flag::wind = 1;



LG_Flag::LG_Flag(LG_Node_Map *map, TiXmlElement *elem) : LG_Plane(map, autoIdentifier(LG_Flag_ID_Prefix, classIDNr))
{

	if (!str_eq(elem->Value(), LG_Flag_XML_Tag_Name)) {

		throw LG_Parse_Exception_Wrong_Element_Name(LG_Flag_XML_Tag_Name, elem->Value());
	}

	try{
		positiveInt_tryToAttributeVariable(LG_Plane_parts_XML_Att_Name, elem, LG_Patch::partsV);
	}
	catch (LG_Parse_Exception *e){
		LG_Patch::partsV = LG_Plane_Parts_Default;
	}

	LG_Patch::partsU = LG_Patch::partsV;


	try{
		string_tryToAttributeVariable(LG_Flag_Att_VertexShader, elem, vsfile_path);
	}
	catch (LG_Parse_Exception *e){
#ifdef _WIN32
		vsfile_path = "../data/textureDemo2.vs";
#else
        vsfile_path= "testFiles/textureDemo2.vs";
#endif
	}

	try{
		string_tryToAttributeVariable(LG_Flag_Att_FragmentShader, elem, fsfile_path);
	}
	catch (LG_Parse_Exception *e){
        
		
#ifdef _WIN32
        fsfile_path = "../data/textureDemo2.fs";
#else
        fsfile_path = "testFiles/textureDemo2.fs";
#endif
	}

	//todo shader is still expecting wind as float, get him that

	/************************************************************
	The shader things
	************************************************************/
    
    
#ifdef _WIN32
	init("../data/textureDemo2.vrs", "../data/textureDemo2.frs");
#else
    printf("Initialize glew with status: %s\n",glewGetErrorString(glewInit()));
    //if (!GLEW_VERSION_2_1) printf("Version not supported");
    init("testFiles/textureDemo2.vrs", "testFiles/textureDemo2.frs");
#endif
    
	//init("../data/textureDemo2.vert", "../data/textureDemo2.frag");

	

	CGFshader::bind();

	// Initialize parameter in memory
	normScale = 0.0;

	// Store Id for the uniform "normScale", new value will be stored on bind()
	scaleLoc = glGetUniformLocation(id(), "normScale");

#ifdef _WIN32
	baseTexture = new CGFtexture("../data/terrainmap2.jpg");
	secTexture = new CGFtexture("../data/feup.jpg");
#else
    baseTexture = new CGFtexture("testFiles/terrainmap2.jpg");
    secTexture = new CGFtexture("testFiles/feup.jpg");
#endif
	// get the uniform location for the sampler
	baseImageLoc = glGetUniformLocation(id(), "baseImage");

	// set the texture id for that sampler to match the GL_TEXTUREn that you 
	// will use later e.g. if using GL_TEXTURE0, set the uniform to 0
	glUniform1i(baseImageLoc, 0);

	// repeat if you use more textures in your shader(s)
	secImageLoc = glGetUniformLocation(id(), "secondImage");
	glUniform1i(secImageLoc, 1);

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
	glActiveTexture(GL_TEXTURE1);

	secTexture->apply();

	glActiveTexture(GL_TEXTURE0);

}

void LG_Flag::unbind(){
	CGFshader::unbind();
	if (LG_Appearance::currentTexture)
		LG_Appearance::currentTexture->apply();
}


void LG_Flag::update(unsigned long time){

	static unsigned long start = time;
	my_time = (float)((time - start)/1000.0);
	//std::cout << d_time << std::endl;
}

int * LG_Flag::getWind(){
	return &wind;
}