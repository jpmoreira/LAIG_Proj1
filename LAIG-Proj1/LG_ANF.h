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
#include "LG_Graph.h"

#include <CGFapplication.h>

class LG_ANF: public LG_Node {
    
private:
    
    
    LG_Lighting *lightingConfig;
    LG_Culling *cullingConfig;
    LG_Drawing *drawingConfig;
    
    LG_Cameras_Container *cameras;
    LG_Lights_Container *lights;
    LG_Texture_Container *textures;
    LG_Appearance_Container *apperances;
    
    LG_Graph * graph;
    
    static LG_ANF * current_anf;
    
    
    
    /**
     
     A method for handling the globals sub element
     
     */
    void handleGlobals(TiXmlElement *elem);
    
    
    /**
     
     A method that checks if there is anything missing in the definition of the data members from the ANF file
     
     
     
     */
    void verifyDataMembersValues();
    
    LG_ANF(TiXmlElement *elem);
    
    
    
public:
    
    
    
    
    
    void draw();
    
    
    /**
     
     A method for configuring openGL with all defenitions previously loaded from the xml
     
     
     
     */
    void config(CGFapplication *app);
    
    
    /**
     
     A method for getting the current ANF object.
     
     */
    static LG_ANF * currentANF();
    
    /**
     
     A method for parsing a TiXmlDocument
     
     */
    
    static LG_ANF *anfForXML(TiXmlDocument *xml);
    
    LG_Camera * currentCamera();
    
    
};

#endif /* defined(__LAIG_Proj1__LG_Config__) */
