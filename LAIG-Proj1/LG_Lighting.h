//
//  LG_Lighting.h
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 24/09/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#ifndef __LAIG_Proj1__LG_Lighting__
#define __LAIG_Proj1__LG_Lighting__

#include <stdio.h>
#include "LG_Parsable_Node.h"

#define LG_Lighting_Node_ID "_LG_Lighting"
#define LG_LIGHTING_XML_TAG_NAME "lighting"
#define LG_LIGHTING_XML_ATT_AMBIENT "ambient"
#define LG_LIGHTING_XML_ATT_ENABLED "enabled"
#define LG_LIGHTING_XML_ATT_DOUBLESIDED "doublesided"
#define LG_LIGHTING_XML_ATT_LOCAL "local"


class LG_Lighting : public LG_Parsable_Node{
    
    
    
private:
    
    
    /**
     
     To control if openGL is to use ilumination in both faces
     
     */
    bool doublesided;
    
    /**
     
     To control if openGL is  to use local ilumination
     
     */
    bool local;
    
    /**
     
     To control if openGL should enable light or compute only ampient light component instead.
     
     */
    
    bool enabled;
    
    /**
     
     To control the ambient light color. Tipically white or brown.
     
     */
	LG_LightArray_f ambient;
    
    
    
public:
    
    
    LG_Lighting(LG_Node_Map *map,TiXmlElement *element);
      
    void verifyElementName(TiXmlElement *element);
    
    void verifyAttributesAndValues(TiXmlElement* element);
    
    void draw();
    
    
};




#endif /* defined(__LAIG_Proj1__LG_Lighting__) */
