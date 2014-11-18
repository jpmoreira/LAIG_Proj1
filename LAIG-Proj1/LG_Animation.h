//
//  LG_Animation.h
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 28/10/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#ifndef __LAIG_Proj1__LG_Animation__
#define __LAIG_Proj1__LG_Animation__

#include <stdio.h>

#include "LG_Parsable_Node.h"


#define LG_Animation_XML_Tag_Name "animation"
#define LG_Animation_ID_XML_Att_Name "id"

class LG_AnimationState;

class LG_Animation: public LG_Parsable_Node {
    
    
    friend class LG_AnimationState;
    
    
private:
    

    string extractIDForSuper(TiXmlElement *elem);
    

    
public:
    
    
    virtual void update(unsigned long timeNow,LG_AnimationState *state)=0;
    
    LG_Animation(LG_Node_Map *map,string identifier,double duration);
    LG_Animation(LG_Node_Map *map,TiXmlElement *elem);
    
    static LG_Animation * animationForElement(LG_Node_Map *map,TiXmlElement *elem);
    
    /**
     
     Configures the parameters for the animation based on the control points
     
     */
    virtual void configureInitialParameters(LG_AnimationState *state)=0;
    
    
    
    
protected:
    double span;

    
    
};

#endif /* defined(__LAIG_Proj1__LG_Animation__) */


