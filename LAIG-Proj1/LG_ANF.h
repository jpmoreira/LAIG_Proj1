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
#include "LG_Animations_Container.h"

#include <CGFapplication.h>

class LG_Tzaar;
class LG_ANF: public LG_Node {
    
	    friend class LG_Scene;
    friend class LG_Tzaar;
    
private:
    
    
    LG_Lighting *lightingConfig;
    LG_Culling *cullingConfig;
    LG_Drawing *drawingConfig;
    
    LG_Cameras_Container *cameras;
    LG_Lights_Container *lights;
    LG_Texture_Container *textures;
    LG_Appearance_Container *apperances;
    LG_Animation_Container *animations;
    
    
    
    TiXmlElement *graphElement;
    
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
    
    
    LG_Graph * graph;
    
    
    void draw(bool selectMode=false);
    

    void config();
    
    
    /**
     
     A method for getting the current ANF object.
     
     */
    static LG_ANF * currentANF();
    
    /**
     
     A method for parsing a TiXmlDocument
     
     */
    
    static LG_ANF *anfForXML(TiXmlDocument *xml);
    
    LG_Camera * currentCamera();
    
    
    /**
    
     A method for returning the drawing mode currently applied
     
     */
    static LG_Drawing_Mode currentDrawingMode();
    



	/**

	A method that returns a pointer to its lights_container

	*/

	LG_Lights_Container *getLightsContainer();


	/**

	A method that returns a pointer to its cameras_container

	*/
    
	LG_Cameras_Container *getCamerasContainer();


	/**

	A method that returns its Drawing element
	
	*/

	LG_Drawing *getDrawing();
    
    
    /*
     
     A method that returns its AnimationsContainer element
     
     */
    
    LG_Animation_Container *getAnimations();
    
    
    LG_Node * nodeWithPickingID(unsigned int selectID);
    
    LG_Node * nodeWithID(string identif);

    void selective_config();
    
    void replaceGraph();
    
    ~LG_ANF();
 
};

#endif /* defined(__LAIG_Proj1__LG_Config__) */
