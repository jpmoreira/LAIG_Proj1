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


class LG_Primitive: public LG_Parsable_Node{

public:

    LG_Primitive(LG_Node_Map *map,string identifier);
    static bool equalPoints(LG_Point& pt1,LG_Point& pt2);


protected:
    void initializePoint(LG_Point& point);
    
};
#endif /* defined(__LAIG_Proj1__LG_Primitive__) */
