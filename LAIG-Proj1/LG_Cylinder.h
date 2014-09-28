//
//  LG_Cylinder.h
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 28/09/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#ifndef __LAIG_Proj1__LG_Cylinder__
#define __LAIG_Proj1__LG_Cylinder__

#include <stdio.h>

#include "LG_Primitive.h"

class LG_Cylinder:public LG_Primitive{
    
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
    
    /**
     
     See LG_Parsable_Node for details
     
     */
    
    virtual void verifyElementName(TiXmlElement *element);
    
    /**
     
     
     See LG_Parsable_Node for details.
     
     */
    virtual void verifyElementAttributesAndValues(TiXmlElement *element);
    
    
public:
    
    /**
     
     Simple construnctor that recieves the map and the TiXmlElement to initialize itself
     
     */
    
    LG_Cylinder(LG_Node_Map *map,TiXmlElement *elem);
    
    /**
     
     Constructor with explicit parameter initialization.
     
     */
    LG_Cylinder(LG_Node_Map *map,double base,double top,double h,int stacks,int slices);
    
    
    
    
    
    
};

#endif /* defined(__LAIG_Proj1__LG_Cylinder__) */
