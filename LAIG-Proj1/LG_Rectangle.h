//
//  LG_Rectangle.h
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 28/09/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#ifndef __LAIG_Proj1__LG_Rectangle__
#define __LAIG_Proj1__LG_Rectangle__

#include <stdio.h>
#include "LG_Primitive.h"



class LG_Rectangle: public LG_Primitive{

    
    
private:
    
    LG_Point3D pt1;
    LG_Point3D pt2;
    
    /**
     Number that holds the current id for the newly created primitive instance. Used in the autoIdentifier macro
     
     */
    
    static int _LG_classIDNr;
    
    
    
    /**
     
     
     See LG_Parsable_Node class for more info.
     
     */
    void verifyElementName(TiXmlElement *element);
    
    /**
     
     
     See LG_Parsable_Node class for more info
     
     */
    void verifyElementAttributesAndValues(TiXmlElement *element);
    
    /**
     
     Copies all the points to the object data members that are supposed to hold them
     
     */
    void copyPoints(LG_Point3D point1,LG_Point3D point2);
    
public:

    
    LG_Rectangle(LG_Node_Map *map,LG_Point3D point1,LG_Point3D point2);
    LG_Rectangle(LG_Node_Map *map,TiXmlElement *elem);
    
    
    
    
    
    
};

#endif /* defined(__LAIG_Proj1__LG_Rectangle__) */