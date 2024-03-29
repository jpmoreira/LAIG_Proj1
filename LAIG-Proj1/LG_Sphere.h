//
//  LG_Sphere.h
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 28/09/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#ifndef __LAIG_Proj1__LG_Sphere__
#define __LAIG_Proj1__LG_Sphere__

#include <stdio.h>

#include "LG_Glu_Primitive.h"

#define LG_Sphere_XML_Tag_Name "sphere"

class LG_Sphere:public LG_Glu_Primitive{
    
private:
    
    double radius;
    int slices;
    int stacks;
    
    
    static int _LG_classIDNr;
    

    
public:
    
    
    LG_Sphere(LG_Node_Map *map,TiXmlElement *elem);
    LG_Sphere(LG_Node_Map *map,TiXmlElement *elem,LG_Appearance *app);
    LG_Sphere(LG_Node_Map *map,double r,int st,int sl);
    
    /**
     
     Method for drawing this object
     
     
     
     */
    void draw(bool selectMode);
    
    
    void calculateTextureCoordinates();
    
    
};

#endif /* defined(__LAIG_Proj1__LG_Sphere__) */
