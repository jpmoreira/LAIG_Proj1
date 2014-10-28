//
//  LG_Plane.h
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 23/10/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#ifndef __LAIG_Proj1__LG_Plane__
#define __LAIG_Proj1__LG_Plane__

#include <stdio.h>

#include "LG_Primitive.h"


#define LG_Plane_XML_Tag_Name "plane"

class LG_Plane: public LG_Primitive {
    
private:
    int parts;
    
    static int classIDNr;
    
public:

    
    LG_Point3D points[4];
    
    
    LG_Plane(LG_Node_Map *map,TiXmlElement *elem);
    void draw();
    void config();
    void calculateTextureCoordinates();
};

#endif /* defined(__LAIG_Proj1__LG_Plane__) */
