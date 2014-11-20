//
//  LG_Cylinder.h
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 28/09/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#ifndef __LAIG_Proj1__LG_Cylinder__
#define __LAIG_Proj1__LG_Cylinder__

#ifdef _WIN32
#include <Windows.h>
#endif

#include <stdio.h>


#include "LG_Glu_Primitive.h"
#define LG_Cylinder_XML_Tag_Name "cylinder"

class LG_Cylinder:public LG_Glu_Primitive{
    
private:
    
    double baseRadius;
    double topRadius;
    double height;
    int slices;
    int stacks;
    
    /**
     Number that holds the current id for the newly created primitive instance. Used in the autoIdentifier macro
     
     */
     
    static int _LG_classIDNr;


    
    
public:
    
    /**
     
     Simple construnctor that recieves the map and the TiXmlElement to initialize itself
     
     */
    
    LG_Cylinder(LG_Node_Map *map,TiXmlElement *elem);
    
    
    LG_Cylinder(LG_Node_Map *map,TiXmlElement *elem,LG_Appearance *app);
    
    /**
     
     Constructor with explicit parameter initialization.
     
     */
    LG_Cylinder(LG_Node_Map *map,double base,double top,double h,int stacks,int slices);
    
    
    
    
    /**
     
     A function for drawing this object
     
     
     
     */
    void draw ();
    
    
    
    void calculateTextureCoordinates();
    
    
};

#endif /* defined(__LAIG_Proj1__LG_Cylinder__) */
