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

#include "LG_Patch.h"


#define LG_Plane_XML_Tag_Name "plane"
#define LG_Plane_parts_XML_Att_Name "parts"

class LG_Plane: public LG_Patch {
    
private:    
    static int classIDNr;
    
public:
    LG_Plane(LG_Node_Map *map,TiXmlElement *elem);
	LG_Plane(LG_Node_Map *map, string LG_Primitive_Identifier);
    void draw(bool selectMode);
    void config();
    void calculateTextureCoordinates();
	void setPatch();
};

#endif /* defined(__LAIG_Proj1__LG_Plane__) */
