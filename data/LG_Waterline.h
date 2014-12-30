//
//  LG_Waterline.h
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 20/11/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#ifndef __LAIG_Proj1__LG_Waterline__
#define __LAIG_Proj1__LG_Waterline__

#include <stdio.h>

#include "CGFshader.h"
#include "LG_Plane.h"


class LG_Waterline: public CGFshader, public LG_Plane {
    
    LG_Waterline(LG_Node_Map *map, TiXmlElement *elem);
    ~LG_Waterline();
    void draw(bool selectMode);
    void config();
    void calculateTextureCoordinates();
    
    virtual void bind(void);
    virtual void unbind(void);
    void setScale(float s);
    
    float normScale;
    
    
    CGFtexture * maskText;
    CGFtexture * mainText;
    CGFtexture * heightText;
    
    GLint maskImageLoc;
    GLint mainImageLoc;
    GLint heightImageLoc;
    
    void update(unsigned long time);
    
    
    
protected:
    string vsfile_path, fsfile_path;
    
    
    
    
private:
    static int classIDNr, wind;
    float my_time;
    
    
};

#endif /* defined(__LAIG_Proj1__LG_Waterline__) */
