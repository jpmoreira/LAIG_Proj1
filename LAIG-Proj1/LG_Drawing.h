//
//  LG_Drawing.h
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 26/09/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#ifndef __LAIG_Proj1__LG_Drawing__
#define __LAIG_Proj1__LG_Drawing__

#include <stdio.h>
#include "LG_Parsable_Node.h"

#define LG_Drawing_XML_Tag_Name "drawing"

#define _LG_Drawing_NodeID "_LG_Drawing"



typedef enum {
    
    LG_Drawing_Fill,
    LG_Drawing_Line,
    LG_Drawing_Point,
    LG_Drawing_Not_Set
    
    
}LG_Drawing_Mode;

typedef enum {
    
    LG_Flat,
    LG_Gouraud,
    LG_Shading_Not_Set
    
    
}LG_Shading_Mode;

class LG_Drawing : public LG_Parsable_Node{


    friend class LG_ANF;
private:
    LG_Drawing_Mode mode;
    
    LG_Shading_Mode shading;
    
    LG_LightArray background;

    
    
    
public:
    
    LG_Drawing(LG_Node_Map *map,TiXmlElement *element);
    
    LG_Drawing(LG_Node_Map *map,LG_Drawing_Mode md,LG_Shading_Mode shading,LG_LightArray background);
    
    void verifyElementName(TiXmlElement *element);
    void verifyElementAttributesAndValues(TiXmlElement *element);
    
    void draw();

    
    
};

#endif /* defined(__LAIG_Proj1__LG_Drawing__) */
