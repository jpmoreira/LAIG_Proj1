//
//  LG_Primitive.h
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 28/09/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#ifndef __LAIG_Proj1__LG_Primitive__
#define __LAIG_Proj1__LG_Primitive__

#include <stdio.h>
#include "LG_Parsable_Node.h"


/**
 
 define that suposes the class using it implements a data member to hold the current instance called _LG_classIDNr and a char * with the name _LG_Primitive_Name that indicates the name of the class.
 Then, this define generates the code to create an auto-increment unique identifier for that class
 
 */

#define autoIdentifier (string(_LG_Primitive_Name+std::to_string(_LG_classIDNr++)))


class LG_Primitive: public LG_Parsable_Node{

public:

    LG_Primitive(LG_Node_Map *map,string identifier);
    static bool equalPoints(LG_Point3D& pt1,LG_Point3D& pt2);


protected:
    void initializePoint3D(LG_Point3D& point);
    
    
    
};
#endif /* defined(__LAIG_Proj1__LG_Primitive__) */