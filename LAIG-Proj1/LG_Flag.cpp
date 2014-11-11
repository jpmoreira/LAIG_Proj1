
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "LG_Flag.h"
#include "CGFapplication.h"
#include <chrono>
#define LG_Flag_ID_Prefix "_LG_Flag_"
#define LG_Plane_Parts_Default 50


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

	verified = false;


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

	/********************************************************************
	Hardcoded test
	*********************************************************************/

	//float hardcodedpoints[16 * 3];
	//hardcodedpoints[0] = 0;		hardcodedpoints[1] = 0;		hardcodedpoints[2] = 0;
	//hardcodedpoints[3] = 1;		hardcodedpoints[4] = 0;		hardcodedpoints[5] = 0;
	//hardcodedpoints[6] = 2;		hardcodedpoints[7] = 0;		hardcodedpoints[8] = 0;
	//hardcodedpoints[9] = 3;		hardcodedpoints[10] = 0;	hardcodedpoints[11] = 0;
	//hardcodedpoints[12] = 0;	hardcodedpoints[13] = 0;	hardcodedpoints[14] = 1;
	//hardcodedpoints[15] = 1;	hardcodedpoints[16] = 0;	hardcodedpoints[17] = 1;
	//hardcodedpoints[18] = 2;	hardcodedpoints[19] = 0;	hardcodedpoints[20] = 1;
	//hardcodedpoints[21] = 3;	hardcodedpoints[22] = 0;	hardcodedpoints[23] = 1;
	//hardcodedpoints[24] = 0;	hardcodedpoints[25] = 0;	hardcodedpoints[26] = 2;
	//hardcodedpoints[27] = 1;	hardcodedpoints[28] = 0;	hardcodedpoints[29] = 2;
	//hardcodedpoints[30] = 2;	hardcodedpoints[31] = 0;	hardcodedpoints[32] = 2;
	//hardcodedpoints[33] = 3;	hardcodedpoints[34] = 0;	hardcodedpoints[35] = 2;
	//hardcodedpoints[36] = 0;	hardcodedpoints[37] = 0;	hardcodedpoints[38] = 3;
	//hardcodedpoints[39] = 1;	hardcodedpoints[40] = 0;	hardcodedpoints[41] = 3;
	//hardcodedpoints[42] = 2;	hardcodedpoints[43] = 0;	hardcodedpoints[44] = 3;
	//hardcodedpoints[45] = 3;	hardcodedpoints[46] = 0;	hardcodedpoints[47] = 3;

	//glEnable(GL_MAP2_VERTEX_3);
	//glEnable(GL_AUTO_NORMAL);


	//glMap2f(GL_MAP2_VERTEX_3,
	//	0.0,//u start
	//	1.0,//u finish
	//	3,//ustride
	//	ORDER3_CURVE + 1,
	//	0.0,//v start
	//	1.0,//v end
	//	ORDER3_VSTRIDE,//vstride
	//	ORDER3_CURVE + 1,//
	//	(GLfloat *)hardcodedpoints);

	//if (LG_Appearance::currentTexture)
	//{
	//	glMap2f(GL_MAP2_TEXTURE_COORD_2,
	//		0.0,//u start
	//		1.0,//u finish
	//		4,//ustride
	//		2, //texture order
	//		0.0,//v start
	//		1.0,//v end
	//		2,//vstride
	//		2,//texture order
	//		(GLfloat *)textCoords);

	//	glEnable(GL_MAP2_TEXTURE_COORD_2);
	//}

	//glMapGrid2f(partsU, 0, 1, partsV, 0, 1);
	//glEvalMesh2(drawMode, 0, partsU, 0, partsV);

	/********************************************************************
	End of hardcoded test
	*********************************************************************/
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
	glUniform1f(scaleLoc, normScale);
	// make sure the correct texture unit is active
	glActiveTexture(GL_TEXTURE0);
	CGFshader::update();
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

    
    CGFshader::update((float)(time/1000));
    
}