//
//  LG_Config.h
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 10/10/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#ifndef __LAIG_Proj1__LG_Config__
#define __LAIG_Proj1__LG_Config__


#include <stdio.h>

#include "LG_Parsable_Node.h"
#include "LG_Cameras_Container.h"
#include "LG_Lights_Container.h"
#include "LG_Texture_Container.h"
#include "LG_Appearance_Container.h"
#include "LG_Lighting.h"
#include "LG_Culling.h"
#include "LG_Drawing.h"

class LG_Config: public LG_Parsable_Node {
    
private:
    
    
    LG_Lighting *lightingConfig;
    LG_Culling *cullingConfig;
    LG_Drawing *drawingConfig;
    
    LG_Cameras_Container *cameras;
    LG_Lights_Container *lights;
    LG_Texture_Container *textures;
    LG_Appearance_Container *apperances;
    
    
public:
    
    
    LG_Config(TiXmlElement *elem);
    
    
    
};

#endif /* defined(__LAIG_Proj1__LG_Config__) */
