//
//  LG_Texture_Container.h
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 09/10/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#ifndef __LAIG_Proj1__LG_Texture_Container__
#define __LAIG_Proj1__LG_Texture_Container__

#include <stdio.h>
#include "LG_Texture.h"

#define LG_Texture_Container_XML_Tag_Name "textures"

class LG_Texture_Container:public LG_Parsable_Node {
    
    
public:
    LG_Texture_Container(TiXmlElement *element);
    
    ~LG_Texture_Container();
    
};

#endif /* defined(__LAIG_Proj1__LG_Texture_Container__) */
