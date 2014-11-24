//
//  LG_Waterline.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 20/11/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "LG_Waterline.h"

#include <stdlib.h>
#include "CGFapplication.h"
#include <chrono>


#define LG_Waterline_ID_Prefix "_LG_Waterline_"
#define LG_Waterline_XML_Tag_Name "waterline"
#define LG_Waterline_HeightText_XML_Att_Name "heightmap"
#define LG_Waterline_MascText_XML_Att_Name "maskmap"
#define LG_Waterline_MainText_XML_Att_Name "texturemap"
#define LG_Waterline_FS_XML_Att_Name "fragmentshader"
#define LG_Waterline_VS_XML_Att_Name "vertexshader"
#define LG_Plane_Parts_Default 50



int LG_Waterline::classIDNr=0;


LG_Waterline::LG_Waterline(LG_Node_Map *map, TiXmlElement *elem) : LG_Plane(map, autoIdentifier(LG_Waterline_ID_Prefix, classIDNr))
{
    
    string maskPath, mainTexturePath,heightTextPath;	//textures path
    
    
    
    evalElemName(LG_Waterline_XML_Tag_Name, elem->Value());
    //------------------------------------- Set Parts --------------------------------//
    

    LG_Patch::partsV = LG_Plane_Parts_Default;
    
    LG_Patch::partsU = LG_Patch::partsV;
    
    //------------------------------------- Set texture(s) --------------------------------//
    
    //base texture
    string_tryToAttributeVariable(LG_Waterline_MainText_XML_Att_Name, elem, mainTexturePath);

    
    //height texture
    string_tryToAttributeVariable(LG_Waterline_HeightText_XML_Att_Name, elem, heightTextPath);

    
    //mask texture

    string_tryToAttributeVariable(LG_Waterline_MascText_XML_Att_Name, elem, maskPath);

    
    mainText = new CGFtexture(mainTexturePath.c_str());
    heightText =new CGFtexture(heightTextPath.c_str());
    maskText=new CGFtexture(maskPath.c_str());
    
    //------------------------------------ set shader files ------------------------------//
    
    
    string_tryToAttributeVariable(LG_Waterline_VS_XML_Att_Name, elem, vsfile_path);
    string_tryToAttributeVariable(LG_Waterline_FS_XML_Att_Name, elem, fsfile_path);
    
    
    
    //------------------------------------ initialize shader ------------------------------//
    init(vsfile_path.c_str(), fsfile_path.c_str());
    
    
    CGFshader::bind();
    
    
    /*baseTexture = new CGFtexture("../data/terrainmap2.jpg");
     secTexture = new CGFtexture("../data/feup.jpg");*/
    
    // get the uniform location for the sampler
    mainImageLoc = glGetUniformLocation(id(), "mainImage");
    heightImageLoc=glGetUniformLocation(id(), "heightImage");
    maskImageLoc=glGetUniformLocation(id(),"maskImage");
    
    // set the texture id for that sampler to match the GL_TEXTUREn that you
    // will use later e.g. if using GL_TEXTURE0, set the uniform to 0
    glUniform1i(mainImageLoc, 0);
    glUniform1i(heightImageLoc,1);
    glUniform1i(maskImageLoc,2);
    
    
    /*
    windLoc = glGetUniformLocation(id(), "wind");
    glUniform1i(windLoc, wind);
    
     */
    CGFshader::unbind();
}


LG_Waterline::~LG_Waterline()
{
    LG_Plane::~LG_Plane();
}


#pragma mark - Configuration
void LG_Waterline::config(){
    
}


#pragma mark - Inherited Methods


void LG_Waterline::draw(){
    
    
    bind();
    
    LG_Patch::draw();
    
    unbind();
    
    if (LG_Appearance::currentTexture)
    {
        LG_Appearance::currentTexture->apply();
    }
}

void LG_Waterline::calculateTextureCoordinates(){
    
    
}

void LG_Waterline::bind()
{
    //std::cout << "Ticks" << CGFapplication::getTime() << endl;
    CGFshader::bind();
    // update uniforms
    CGFshader::update(my_time);
    
    //glUniform1i(windLoc, wind);
    
    //glUniform1f(scaleLoc, normScale);
    // make sure the correct texture unit is active
    glActiveTexture(GL_TEXTURE0);
    // apply/activate the texture you want, so that it is bound to GL_TEXTURE0
    mainText->apply();
    
    glActiveTexture(GL_TEXTURE1);
    
    heightText->apply();
    
    glActiveTexture(GL_TEXTURE2);
    
    maskText->apply();
    
    glActiveTexture(GL_TEXTURE0);
}

void LG_Waterline::unbind(){
    CGFshader::unbind();
    if (LG_Appearance::currentTexture)
        LG_Appearance::currentTexture->apply();
}


void LG_Waterline::update(unsigned long time){
    
    static unsigned long start = time;
    my_time = (float)((time - start) / 1000.0);
    //std::cout << d_time << std::endl;
}
